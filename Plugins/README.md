# Freaked for desktop — Audio Unit and VST3

The Freaked effects were written in Faust and shipped as LV2 for the MOD. Faust
does not care what it is wrapped in, so the same DSP sources are reused here to
produce plugins that Logic Pro and any VST3 host can load.

| Plugin       | Channels | Controls                                          |
|--------------|----------|---------------------------------------------------|
| Freakclip    | mono     | Clip, Delay, Drive                                |
| Prefreak     | stereo   | Blur, Level                                       |
| Freaktail    | stereo   | Decay, Roomsize, Tail level                       |
| FreakVerb    | stereo   | Blur, Level, Decay, Roomsize, Tail level          |
| Granulator   | stereo   | delay length, grain density, grain length, mix    |

`FreakVerb` is `Prefreak` feeding `Freaktail`, which is the combination the
original README recommends. It exists as one plugin so it only needs one slot
in a channel strip.

## What gets built

- **Audio Unit** (`.component`) — macOS only, universal `arm64` + `x86_64`,
  deployment target 11.0, so it covers macOS 12 and later as required.
- **VST3** (`.vst3`) — universal on macOS, x64 on Windows.

Mono and stereo are both offered. `Freakclip` has a mono DSP, so on a stereo
track two copies run side by side sharing one set of controls. The stereo
effects also accept a mono input and widen it to stereo, which is what you want
when feeding a reverb from a mono source.

### Mono to stereo

Every plugin here declares a mono in / stereo out configuration, so on a mono
track in Logic the insert slot offers it directly — there is no separate mono
version to install. The Audio Unit reports its capabilities as `[1, 2] [2, 2]`,
which `auval` confirms; `[1, 1]` is only offered by `Freakclip`, whose DSP is
mono end to end.

The single input channel is fanned out to both DSP inputs, and the result is a
genuine stereo image rather than two copies of the same signal, because the two
halves of each DSP run their own state. Measured left/right correlation from a
mono source, where 1.0 would mean a dead centre mono result:

| Plugin | correlation from mono in |
|--------|--------------------------|
| Freakclip  | -0.37 |
| Prefreak   | -0.06 |
| Freaktail  |  0.23 |
| FreakVerb  |  0.02 |
| Granulator |  0.01 |

The smoke test asserts both output channels come alive in this configuration
and prints the correlation, so a regression that collapses the image to mono
shows up as a number rather than as a complaint months later.

## Building

CMake fetches JUCE itself, so a compiler and CMake 3.22+ are all that is needed:

```sh
cmake -S Plugins -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

On macOS, add the architectures for a universal build:

```sh
cmake -S Plugins -B build -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" -DCMAKE_OSX_DEPLOYMENT_TARGET=11.0
```

Add `-DFREAKED_COPY_AFTER_BUILD=ON` to have each build install itself into your
user plugin folders.

The results land in `build/<Plugin>_artefacts/Release/`.

### Installing by hand

| Format | macOS                                     | Windows                              |
|--------|-------------------------------------------|--------------------------------------|
| AU     | `~/Library/Audio/Plug-Ins/Components/`    | —                                    |
| VST3   | `~/Library/Audio/Plug-Ins/VST3/`          | `C:\Program Files\Common Files\VST3\` |

The CI signs the macOS bundles ad-hoc, which is enough to run them locally but
is not a Developer ID signature. After downloading a build artifact, clear the
quarantine flag or macOS will refuse to load it:

```sh
xattr -dr com.apple.quarantine ~/Library/Audio/Plug-Ins/Components/Freakclip.component
```

Logic caches its plugin list, so a newly installed Audio Unit shows up after
Logic is restarted. If it does not appear, run `auval -a | grep Frkd` to check
macOS sees it at all.

## Changing the DSP

Edit the `.dsp` files in `Faustsrc/`, then regenerate the C++:

```sh
Plugins/tools/generate-faust.sh      # needs the faust compiler on PATH
```

The generated C++ in `Plugins/Generated/` is committed on purpose: it means the
macOS and Windows builders need only a C++ toolchain. A CI job regenerates it
and fails if the result differs, so it cannot silently drift from the sources.

Nothing else needs updating. The wrapper reads the parameter list, ranges,
defaults and channel counts out of the compiled DSP at runtime, so a new
control in a `.dsp` file appears in the plugin by itself. Adding a whole new
plugin is one `freaked_add_plugin(...)` block in `Plugins/CMakeLists.txt`.

## Tests

`FreakedSmokeTest` loads the built VST3s through JUCE's own plugin host and, for
each one, negotiates every supported bus layout, runs audio at 44.1/48/96 kHz in
varying block sizes, checks the output is finite and non-silent, and round-trips
the state:

```sh
./build/FreakedSmokeTest_artefacts/Release/FreakedSmokeTest build/*_artefacts/Release/VST3/*.vst3
```

On macOS, CI additionally runs Apple's `auval` against each Audio Unit, which is
the same validation Logic requires before it will load one.

### The Granulator is pinned to the LV2 build

Structural tests cannot tell you the plugin still *sounds* right. Regenerating
the DSP with a Faust a decade newer than the one that produced the shipped LV2
is enough to change what an expression means, silently — `2^32 - 1` folded to
4294967295 in 2016 and folds to `-1` today, which quietly turned the
granulator's position randomiser into a negation.

So `Tests/LegacyGranulatorTest.cpp` runs the current build and the 2016 LV2 build
side by side on the same input and compares their output envelopes. The
reference is extracted mechanically from `CppSrc/` by
`Plugins/tools/extract-lv2-reference.sh` and committed; it is not to be edited.
Anything that changes the granulator's character by more than a factor of two
fails the build.

## Layout

```
Plugins/
  CMakeLists.txt          one freaked_add_plugin() block per plugin
  Source/                 the wrapper, shared by all five plugins
  Generated/              Faust output, regenerated by tools/generate-faust.sh
  faust-arch/             Faust's dsp.h / UI.h / meta.h, vendored unmodified
  Tests/                  the host-level smoke test
  tools/generate-faust.sh
```

## A note on licensing

Freaked is under the GPL, and this build uses JUCE under **GPLv3**. Two things
are worth knowing before publishing binaries:

- The repository's `LICENSE` is **GPL version 2**, and GPLv2-only is not
  compatible with GPLv3. Building for your own use is unaffected — the GPL's
  obligations attach to distribution, not to private use — but redistributing
  these binaries would mean settling the version first, either by confirming the
  sources are "v2 or later" or by moving the project to GPLv3.
- `Granulator` is by Mayank Sanganeria rather than the Freaked author, so it is
  a separate conversation.

If you would rather keep the option of a non-GPL release, the wrapper is small
and deliberately isolated: swapping JUCE for a permissively licensed framework
such as DPF (ISC) would touch only `Plugins/Source/`, not the DSP.

The files in `faust-arch/` are Faust architecture files, LGPL with the standard
exception that allows a larger work under any license provided those files are
unmodified. They are vendored verbatim for that reason — do not edit them.

## The LV2 build is untouched

The MOD/LV2 build still comes from the pre-generated C++ in `CppSrc/` via the
top-level `Makefile`, exactly as before. Nothing here changes the plugins on
your pedalboard.

One caveat worth acting on: `Faustsrc/granulator.dsp` has been fixed twice (see
the notes in the file), but `CppSrc/` was deliberately not regenerated, so the
LV2 binary carries neither fix. The second one matters on the device too:

> `grain length` is smoothed, and a Faust `smooth()` starts its state at zero
> and ramps up to the slider value. For the first samples after `init()` the
> value is therefore roughly the target divided by a thousand, and at the
> shortest grain length that rounds down to zero — which is then used as a
> modulo divisor. The result is an integer division by zero, which is a crash,
> not a glitch.

On the MOD it only bites when the plugin initialises with `grain length` already
at or near its minimum — loading a preset or pedalboard saved that way, rather
than the default. Regenerating `CppSrc/` means re-running Faust against the LV2
architecture and re-testing on the device, which is a separate job from this
one, so it has been left alone rather than pushed out untested.
