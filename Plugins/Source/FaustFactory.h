#pragma once

#include <faust/dsp/dsp.h>

#include <memory>

/** Creates one instance of the Faust DSP this plugin target was built around.

    The generated Faust headers are large and every plugin target compiles a
    different one, so they are kept out of the shared translation units and
    reached only through this factory.
*/
std::unique_ptr<dsp> createFreakedDsp();
