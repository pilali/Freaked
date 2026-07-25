#include "FaustFactory.h"
#include "FreakedPluginConfig.h"

#include <faust/gui/UI.h>
#include <faust/gui/meta.h>

// The Faust compiler emits a class deriving from `dsp`, so the base classes
// above have to be visible first. FREAKED_DSP_HEADER is filled in per target.
#include FREAKED_DSP_HEADER

std::unique_ptr<dsp> createFreakedDsp()
{
    return std::make_unique<FREAKED_DSP_CLASS>();
}
