declare name "FreakVerb";
declare author "Pjotr Lasschuit";

// The complete reverb: the blurry pre-delay feeding the reverb tail.
// Paths are resolved through the Faust import path (-I Faustsrc), so this
// file is no longer tied to one particular machine.

process = component("PreFreak.dsp") : component("Freaktail.dsp");
