cmake_minimum_required(VERSION 3.22)

# These have to be set before project() or CMake will have already probed the
# compiler with the wrong target.
if(APPLE)
    # 11.0 is the oldest release that can run arm64 code, so it is the floor for
    # a universal binary. This comfortably covers the macOS 12 requirement.
    set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum macOS version")
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "macOS architectures")
endif()

project(Freaked VERSION 1.2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

include(FetchContent)

FetchContent_Declare(JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        8.0.15
    GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(JUCE)

# AU only exists on Apple platforms; everywhere else VST3 is the only target.
set(FREAKED_FORMATS VST3)
if(APPLE)
    list(APPEND FREAKED_FORMATS AU)
endif()

message(STATUS "Freaked: building formats: ${FREAKED_FORMATS}")

#
# freaked_add_plugin(
#     TARGET       <cmake target name>
#     PRODUCT_NAME <name shown in the host>
#     DSP_CLASS    <generated C++ class>
#     DSP_HEADER   <generated header file name>
#     PLUGIN_CODE  <unique 4 character AU/VST3 code>
#     TAIL_SECONDS <how long the effect rings after silence>
#     DESCRIPTION  <one line summary>
# )
#
# All five plugins share the same wrapper sources; only the generated Faust DSP
# and the identity metadata differ.
#
function(freaked_add_plugin)
    cmake_parse_arguments(ARG ""
        "TARGET;PRODUCT_NAME;DSP_CLASS;DSP_HEADER;PLUGIN_CODE;TAIL_SECONDS;DESCRIPTION"
        "" ${ARGN})

    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Generated/${ARG_DSP_HEADER}")
        message(FATAL_ERROR
            "Missing Generated/${ARG_DSP_HEADER}. "
            "Run Plugins/tools/generate-faust.sh to regenerate the Faust DSP code.")
    endif()

    # Consumed by configure_file below.
    set(FREAKED_PRODUCT_NAME    "${ARG_PRODUCT_NAME}")
    set(FREAKED_DSP_CLASS_NAME  "${ARG_DSP_CLASS}")
    set(FREAKED_DSP_HEADER_NAME "${ARG_DSP_HEADER}")
    set(FREAKED_TAIL_SECONDS    "${ARG_TAIL_SECONDS}")

    set(config_dir "${CMAKE_CURRENT_BINARY_DIR}/${ARG_TARGET}_config")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Source/FreakedPluginConfig.h.in"
                   "${config_dir}/FreakedPluginConfig.h" @ONLY)

    string(TOLOWER "${ARG_TARGET}" target_lowercase)

    juce_add_plugin(${ARG_TARGET}
        COMPANY_NAME                "Freaked"
        COMPANY_WEBSITE             "https://github.com/pjotrompet/Freaked"
        BUNDLE_ID                   "com.freaked.${target_lowercase}"
        PLUGIN_MANUFACTURER_CODE    Frkd
        PLUGIN_CODE                 ${ARG_PLUGIN_CODE}
        FORMATS                     ${FREAKED_FORMATS}
        PRODUCT_NAME                "${ARG_PRODUCT_NAME}"
        DESCRIPTION                 "${ARG_DESCRIPTION}"
        IS_SYNTH                    FALSE
        NEEDS_MIDI_INPUT            FALSE
        NEEDS_MIDI_OUTPUT           FALSE
        IS_MIDI_EFFECT              FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD     ${FREAKED_COPY_AFTER_BUILD}
        AU_MAIN_TYPE                kAudioUnitType_Effect
        VST3_CATEGORIES             Fx)

    target_sources(${ARG_TARGET} PRIVATE
        Source/FreakedProcessor.cpp
        Source/FreakedEditor.cpp
        Source/FaustFactory.cpp)

    target_include_directories(${ARG_TARGET} PRIVATE
        "${config_dir}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source"
        "${CMAKE_CURRENT_SOURCE_DIR}/faust-arch"
        "${CMAKE_CURRENT_SOURCE_DIR}/Generated")

    target_compile_definitions(${ARG_TARGET} PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_REPORT_APP_USAGE=0
        JUCE_DISPLAY_SPLASH_SCREEN=0)

    target_link_libraries(${ARG_TARGET}
        PRIVATE
            juce::juce_audio_utils
        PUBLIC
            juce::juce_recommended_config_flags)

    if(FREAKED_ENABLE_LTO)
        target_link_libraries(${ARG_TARGET} PUBLIC juce::juce_recommended_lto_flags)
    endif()
endfunction()

# Install the built plugins into the user's plugin folders after each build.
# Off by default so that CI never writes outside the build tree.
option(FREAKED_COPY_AFTER_BUILD "Copy plugins to the user plugin folders after building" OFF)

# Off by default: linking ten plugin binaries with LTO -- twenty slices for a
# macOS universal build -- costs far more build time than it buys back in a DSP
# that is already compiled at -O3.
option(FREAKED_ENABLE_LTO "Build with link-time optimisation" OFF)

freaked_add_plugin(
    TARGET       Freakclip
    PRODUCT_NAME "Freakclip"
    DSP_CLASS    FreakClipDSP
    DSP_HEADER   FreakClipDSP.hpp
    PLUGIN_CODE  Fclp
    TAIL_SECONDS 0.1
    DESCRIPTION  "Filter based distortion with a clipping stage")

freaked_add_plugin(
    TARGET       Prefreak
    PRODUCT_NAME "Prefreak"
    DSP_CLASS    PreFreakDSP
    DSP_HEADER   PreFreakDSP.hpp
    PLUGIN_CODE  Fpre
    TAIL_SECONDS 2.0
    DESCRIPTION  "A long, blurry pre-delay of early reflections")

freaked_add_plugin(
    TARGET       Freaktail
    PRODUCT_NAME "Freaktail"
    DSP_CLASS    FreaktailDSP
    DSP_HEADER   FreaktailDSP.hpp
    PLUGIN_CODE  Ftal
    TAIL_SECONDS 10.0
    DESCRIPTION  "The reverb tail, can be made very long")

freaked_add_plugin(
    TARGET       FreakVerb
    PRODUCT_NAME "FreakVerb"
    DSP_CLASS    FreakVerbDSP
    DSP_HEADER   FreakVerbDSP.hpp
    PLUGIN_CODE  Fvrb
    TAIL_SECONDS 10.0
    DESCRIPTION  "Prefreak and Freaktail chained into a complete reverb")

freaked_add_plugin(
    TARGET       Granulator
    PRODUCT_NAME "Granulator"
    DSP_CLASS    GranulatorDSP
    DSP_HEADER   GranulatorDSP.hpp
    PLUGIN_CODE  Fgrn
    TAIL_SECONDS 10.0
    DESCRIPTION  "Realtime granulator playing chunks from a delay line")

add_custom_target(FreakedAll ALL)
add_dependencies(FreakedAll Freakclip Prefreak Freaktail FreakVerb Granulator)

# A host-level smoke test: loads a built plugin through JUCE's own plugin host
# and runs audio through it in each supported bus layout.
option(FREAKED_BUILD_TESTS "Build the plugin smoke test host" ON)

if(FREAKED_BUILD_TESTS)
    juce_add_console_app(FreakedSmokeTest PRODUCT_NAME "FreakedSmokeTest")

    # The test also links the wrapper directly so it can build and show the
    # editor without a second copy of JUCE in the process. FreakVerb is used
    # because it has the most controls, and so the busiest editor layout.
    set(FREAKED_PRODUCT_NAME    "FreakVerb")
    set(FREAKED_DSP_CLASS_NAME  FreakVerbDSP)
    set(FREAKED_DSP_HEADER_NAME FreakVerbDSP.hpp)
    set(FREAKED_TAIL_SECONDS    10.0)

    set(test_config_dir "${CMAKE_CURRENT_BINARY_DIR}/FreakedSmokeTest_config")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Source/FreakedPluginConfig.h.in"
                   "${test_config_dir}/FreakedPluginConfig.h" @ONLY)

    target_sources(FreakedSmokeTest PRIVATE
        Tests/PluginSmokeTest.cpp
        Tests/LegacyGranulatorTest.cpp
        Source/FreakedProcessor.cpp
        Source/FreakedEditor.cpp
        Source/FaustFactory.cpp)

    target_include_directories(FreakedSmokeTest PRIVATE
        "${test_config_dir}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Source"
        "${CMAKE_CURRENT_SOURCE_DIR}/faust-arch"
        "${CMAKE_CURRENT_SOURCE_DIR}/Generated")

    target_compile_definitions(FreakedSmokeTest PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_PLUGINHOST_VST3=1
        JUCE_PLUGINHOST_AU=$<IF:$<BOOL:${APPLE}>,1,0>
        JUCE_MODAL_LOOPS_PERMITTED=1)

    target_link_libraries(FreakedSmokeTest
        PRIVATE
            juce::juce_audio_utils
        PUBLIC
            juce::juce_recommended_config_flags)
endif()
