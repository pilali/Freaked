#!/usr/bin/env bash
#
# Regenerate the C++ DSP classes from the Faust sources in Faustsrc/.
#
# The generated headers are committed to the repository on purpose: it means
# the macOS and Windows CI builders only need a C++ toolchain, not a working
# Faust installation. Run this script whenever a .dsp file changes and commit
# the result. The CI has a job that runs it and fails if the tree is dirty
# afterwards, so the committed code can never silently drift from the sources.
#
# Usage: Plugins/tools/generate-faust.sh
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SRC="$ROOT/Faustsrc"
OUT="$ROOT/Plugins/Generated"

if ! command -v faust >/dev/null 2>&1; then
    echo "error: the 'faust' compiler is not on PATH." >&2
    echo "  Debian/Ubuntu: apt-get install faust" >&2
    echo "  macOS:         brew install faust" >&2
    echo "  or grab it from https://faust.grame.fr" >&2
    exit 1
fi

echo "Using $(faust --version | head -1)"
mkdir -p "$OUT"

# generate <dsp basename> <C++ class name>
generate() {
    local dsp="$1" cls="$2"
    echo "  $dsp.dsp -> Generated/$cls.hpp"
    # -I Faustsrc so that component()/import() resolve relative to the sources.
    # -ct 1 (the default) emits bounds-checked table access, which is what keeps
    # the granulator's delay line safe when the host runs at a high sample rate.
    faust -I "$SRC" -lang cpp -ct 1 -cn "$cls" "$SRC/$dsp.dsp" -o "$OUT/$cls.hpp"
}

generate FreakClip  FreakClipDSP
generate PreFreak   PreFreakDSP
generate Freaktail  FreaktailDSP
generate FreakVerb  FreakVerbDSP
generate granulator GranulatorDSP

echo "Done."
