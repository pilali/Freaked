// GENERATED FILE -- DO NOT EDIT.
//
// The Granulator DSP class from the LV2 build in
// CppSrc/Granulator_linux_lv2-32bits.cpp, which was produced by Faust 2.0.a40
// in 2016 and is the build running on the MOD. It is extracted verbatim by
// Plugins/tools/extract-lv2-reference.sh and used as the reference the current
// Faust output is compared against, so that regenerating the DSP with a newer
// compiler cannot silently change how the plugin sounds.
//
// Everything outside the `oldgran` namespace body below is shim: the original
// architecture file supplied these declarations.

#pragma once

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace oldgran {

inline int   max (int a, int b)     { return a > b ? a : b; }
inline int   min (int a, int b)     { return a < b ? a : b; }
inline float max (float a, float b) { return a > b ? a : b; }
inline float min (float a, float b) { return a < b ? a : b; }

struct Meta { virtual ~Meta() {} virtual void declare (const char*, const char*) {} };

struct UI
{
    virtual ~UI() {}
    virtual void openVerticalBox (const char*) {}
    virtual void openHorizontalBox (const char*) {}
    virtual void closeBox() {}
    virtual void declare (float*, const char*, const char*) {}
    virtual void addHorizontalSlider (const char*, float* zone, float init, float, float, float) { *zone = init; }
    virtual void addVerticalSlider (const char*, float* zone, float init, float, float, float) { *zone = init; }
    virtual void addNumEntry (const char*, float* zone, float init, float, float, float) { *zone = init; }
};

class dsp
{
 protected:
    int fSamplingFreq;
 public:
    dsp() {}
    virtual ~dsp() {}
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual void buildUserInterface (UI* interface) = 0;
    virtual void init (int samplingRate) = 0;
    virtual void compute (int len, float** inputs, float** outputs) = 0;
};

class GranulatorSIG0 {

  public:


  public:

	int getNumInputsGranulatorSIG0() {
		return 0;

	}
	int getNumOutputsGranulatorSIG0() {
		return 1;

	}
	int getInputRateGranulatorSIG0(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}

		}
		return rate;

	}
	int getOutputRateGranulatorSIG0(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}

		}
		return rate;

	}

	void instanceInitGranulatorSIG0(int samplingFreq) {

	}

	void fillGranulatorSIG0(int count, float* output) {
		for (int i = 0; (i < count); i = (i + 1)) {
			output[i] = 0.f;

		}

	}
};

GranulatorSIG0* newGranulatorSIG0() {return (GranulatorSIG0*) new GranulatorSIG0(); }
void deleteGranulatorSIG0(GranulatorSIG0* dsp) {delete dsp; }


#ifndef FAUSTCLASS
#define FAUSTCLASS Granulator
#endif

class Granulator : public dsp {

  public:

	float ftbl0[480000];
	float ftbl1[480000];
	int iVec0[2];
	float fRec0[2];
	float fRec2[2];
	int iRec1[2];
	float fRec4[2];
	int iRec3[2];
	int iRec6[2];
	int iRec5[2];
	int iRec22[2];
	int iRec23[2];
	int iRec24[2];
	int iRec25[2];
	int iRec26[2];
	int iRec27[2];
	int iRec28[2];
	int iRec29[2];
	int iRec30[2];
	int iRec31[2];
	int iRec32[2];
	int iRec33[2];
	int iRec34[2];
	int iRec35[2];
	int iRec36[2];
	int iRec37[2];
	int iRec38[2];
	int iRec39[2];
	int iRec40[2];
	int iRec41[2];
	int iRec42[2];
	int iRec43[2];
	int iRec44[2];
	int iRec45[2];
	int iRec46[2];
	int iRec47[2];
	int iRec48[2];
	int iRec49[2];
	int iRec50[2];
	int iRec51[2];
	int iRec52[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSamplingFreq;
	int iConst0;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;

  public:

	void static metadata(Meta* m) {
		m->declare("author", "Mayank Sanganeria");
		m->declare("compilation_options", "-single -vec -vs 128 -mcd 64");
		m->declare("filter_lib_author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter_lib_copyright", "Julius O. Smith III");
		m->declare("filter_lib_license", "STK-4.3");
		m->declare("filter_lib_name", "Faust Filter Library");
		m->declare("filter_lib_reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter_lib_version", "1.29");
		m->declare("library_path", "granulator");
		m->declare("maintainer", "Pjotr Lasschuit");
		m->declare("math_lib_author", "GRAME");
		m->declare("math_lib_copyright", "GRAME");
		m->declare("math_lib_license", "LGPL with exception");
		m->declare("math_lib_name", "Math Library");
		m->declare("math_lib_version", "1.0");
		m->declare("music_lib_author", "GRAME");
		m->declare("music_lib_copyright", "GRAME");
		m->declare("music_lib_license", "LGPL with exception");
		m->declare("music_lib_name", "Music Library");
		m->declare("music_lib_version", "1.0");
		m->declare("name", "Granulator");
		m->declare("version", "1.2");
	}

	virtual int getNumInputs() {
		return 2;

	}
	virtual int getNumOutputs() {
		return 2;

	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}

		}
		return rate;

	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}

		}
		return rate;

	}

	static void classInit(int samplingFreq) {

	}

	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			iVec0[i0] = 0;

		}
		fHslider0 = FAUSTFLOAT(0.5);
		for (int i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			fRec0[i1] = 0.f;

		}
		fHslider1 = FAUSTFLOAT(2.);
		GranulatorSIG0* sig0 = newGranulatorSIG0();
		sig0->instanceInitGranulatorSIG0(samplingFreq);
		sig0->fillGranulatorSIG0(480000, ftbl0);
		iConst0 = min(192000, max(1, fSamplingFreq));
		fHslider2 = FAUSTFLOAT(10.);
		for (int i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			fRec2[i2] = 0.f;

		}
		for (int i3 = 0; (i3 < 2); i3 = (i3 + 1)) {
			iRec1[i3] = 0;

		}
		fHslider3 = FAUSTFLOAT(0.1);
		for (int i4 = 0; (i4 < 2); i4 = (i4 + 1)) {
			fRec4[i4] = 0.f;

		}
		for (int i5 = 0; (i5 < 2); i5 = (i5 + 1)) {
			iRec3[i5] = 0;

		}
		for (int i6 = 0; (i6 < 2); i6 = (i6 + 1)) {
			iRec6[i6] = 0;

		}
		for (int i7 = 0; (i7 < 2); i7 = (i7 + 1)) {
			iRec5[i7] = 0;

		}
		for (int i8 = 0; (i8 < 2); i8 = (i8 + 1)) {
			iRec22[i8] = 0;

		}
		for (int i9 = 0; (i9 < 2); i9 = (i9 + 1)) {
			iRec23[i9] = 0;

		}
		for (int i10 = 0; (i10 < 2); i10 = (i10 + 1)) {
			iRec24[i10] = 0;

		}
		for (int i11 = 0; (i11 < 2); i11 = (i11 + 1)) {
			iRec25[i11] = 0;

		}
		for (int i12 = 0; (i12 < 2); i12 = (i12 + 1)) {
			iRec26[i12] = 0;

		}
		for (int i13 = 0; (i13 < 2); i13 = (i13 + 1)) {
			iRec27[i13] = 0;

		}
		for (int i14 = 0; (i14 < 2); i14 = (i14 + 1)) {
			iRec28[i14] = 0;

		}
		for (int i15 = 0; (i15 < 2); i15 = (i15 + 1)) {
			iRec29[i15] = 0;

		}
		for (int i16 = 0; (i16 < 2); i16 = (i16 + 1)) {
			iRec30[i16] = 0;

		}
		for (int i17 = 0; (i17 < 2); i17 = (i17 + 1)) {
			iRec31[i17] = 0;

		}
		for (int i18 = 0; (i18 < 2); i18 = (i18 + 1)) {
			iRec32[i18] = 0;

		}
		for (int i19 = 0; (i19 < 2); i19 = (i19 + 1)) {
			iRec33[i19] = 0;

		}
		for (int i20 = 0; (i20 < 2); i20 = (i20 + 1)) {
			iRec34[i20] = 0;

		}
		for (int i21 = 0; (i21 < 2); i21 = (i21 + 1)) {
			iRec35[i21] = 0;

		}
		for (int i22 = 0; (i22 < 2); i22 = (i22 + 1)) {
			iRec36[i22] = 0;

		}
		sig0->instanceInitGranulatorSIG0(samplingFreq);
		sig0->fillGranulatorSIG0(480000, ftbl1);
		for (int i23 = 0; (i23 < 2); i23 = (i23 + 1)) {
			iRec37[i23] = 0;

		}
		for (int i24 = 0; (i24 < 2); i24 = (i24 + 1)) {
			iRec38[i24] = 0;

		}
		for (int i25 = 0; (i25 < 2); i25 = (i25 + 1)) {
			iRec39[i25] = 0;

		}
		for (int i26 = 0; (i26 < 2); i26 = (i26 + 1)) {
			iRec40[i26] = 0;

		}
		for (int i27 = 0; (i27 < 2); i27 = (i27 + 1)) {
			iRec41[i27] = 0;

		}
		for (int i28 = 0; (i28 < 2); i28 = (i28 + 1)) {
			iRec42[i28] = 0;

		}
		for (int i29 = 0; (i29 < 2); i29 = (i29 + 1)) {
			iRec43[i29] = 0;

		}
		for (int i30 = 0; (i30 < 2); i30 = (i30 + 1)) {
			iRec44[i30] = 0;

		}
		for (int i31 = 0; (i31 < 2); i31 = (i31 + 1)) {
			iRec45[i31] = 0;

		}
		for (int i32 = 0; (i32 < 2); i32 = (i32 + 1)) {
			iRec46[i32] = 0;

		}
		for (int i33 = 0; (i33 < 2); i33 = (i33 + 1)) {
			iRec47[i33] = 0;

		}
		for (int i34 = 0; (i34 < 2); i34 = (i34 + 1)) {
			iRec48[i34] = 0;

		}
		for (int i35 = 0; (i35 < 2); i35 = (i35 + 1)) {
			iRec49[i35] = 0;

		}
		for (int i36 = 0; (i36 < 2); i36 = (i36 + 1)) {
			iRec50[i36] = 0;

		}
		for (int i37 = 0; (i37 < 2); i37 = (i37 + 1)) {
			iRec51[i37] = 0;

		}
		for (int i38 = 0; (i38 < 2); i38 = (i38 + 1)) {
			iRec52[i38] = 0;

		}
		deleteGranulatorSIG0(sig0);

	}

	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}

	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("0x00");
		interface->addHorizontalSlider("delay length", &fHslider2, 10.f, 0.5f, 10.f, 0.1f);
		interface->addHorizontalSlider("grain density", &fHslider1, 2.f, 2.f, 16.f, 1.f);
		interface->addHorizontalSlider("grain length", &fHslider3, 0.1f, 0.01f, 0.5f, 0.01f);
		interface->addHorizontalSlider("mix", &fHslider0, 0.5f, 0.f, 1.f, 0.01f);
		interface->closeBox();

	}

	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.001f * float(fHslider0));
		float fSlow1 = float(fHslider1);
		int iSlow2 = (0.f < fSlow1);
		float fSlow3 = (0.001f * float(fHslider2));
		float fSlow4 = (0.001f * float(fHslider3));
		int iSlow5 = (2.f < fSlow1);
		int iSlow6 = (4.f < fSlow1);
		int iSlow7 = (6.f < fSlow1);
		int iSlow8 = (8.f < fSlow1);
		int iSlow9 = (10.f < fSlow1);
		int iSlow10 = (12.f < fSlow1);
		int iSlow11 = (14.f < fSlow1);
		int iSlow12 = (1.f < fSlow1);
		int iSlow13 = (3.f < fSlow1);
		int iSlow14 = (5.f < fSlow1);
		int iSlow15 = (7.f < fSlow1);
		int iSlow16 = (9.f < fSlow1);
		int iSlow17 = (11.f < fSlow1);
		int iSlow18 = (13.f < fSlow1);
		int iSlow19 = (15.f < fSlow1);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = ((0.999f * fRec0[1]) + fSlow0);
			float fTemp0 = (1.f - fRec0[0]);
			float fTemp1 = float(input0[i]);
			fRec2[0] = ((0.999f * fRec2[1]) + fSlow3);
			int iTemp2 = int((float(iConst0) * fRec2[0]));
			iRec1[0] = ((1 % iTemp2) + iRec1[1]);
			int iTemp3 = (iRec1[0] % iTemp2);
			ftbl0[iTemp3] = fTemp1;
			fRec4[0] = ((0.999f * fRec4[1]) + fSlow4);
			int iTemp4 = int((float(iConst0) * fRec4[0]));
			iRec3[0] = ((1 + iRec3[1]) % iTemp4);
			int iTemp5 = (1 - iVec0[1]);
			int iTemp6 = (1103515245 * (12345 + iRec6[1]));
			int iTemp7 = (1103515245 * (12345 + iTemp6));
			int iTemp8 = (1103515245 * (12345 + iTemp7));
			int iTemp9 = (1103515245 * (12345 + iTemp8));
			int iTemp10 = (1103515245 * (12345 + iTemp9));
			int iTemp11 = (1103515245 * (12345 + iTemp10));
			int iTemp12 = (1103515245 * (12345 + iTemp11));
			int iTemp13 = (1103515245 * (12345 + iTemp12));
			int iTemp14 = (1103515245 * (12345 + iTemp13));
			int iTemp15 = (1103515245 * (12345 + iTemp14));
			int iTemp16 = (1103515245 * (12345 + iTemp15));
			int iTemp17 = (1103515245 * (12345 + iTemp16));
			int iTemp18 = (1103515245 * (12345 + iTemp17));
			int iTemp19 = (1103515245 * (12345 + iTemp18));
			int iTemp20 = (1103515245 * (12345 + iTemp19));
			int iTemp21 = (1103515245 * (12345 + iTemp20));
			iRec6[0] = (1103515245 * (12345 + iTemp21));
			int iRec7 = iTemp21;
			int iRec8 = iTemp20;
			int iRec9 = iTemp19;
			int iRec10 = iTemp18;
			int iRec11 = iTemp17;
			int iRec12 = iTemp16;
			int iRec13 = iTemp15;
			int iRec14 = iTemp14;
			int iRec15 = iTemp13;
			int iRec16 = iTemp12;
			int iRec17 = iTemp11;
			int iRec18 = iTemp10;
			int iRec19 = iTemp9;
			int iRec20 = iTemp8;
			int iRec21 = iTemp7;
			int iTemp22 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec6[0]))))));
			iRec5[0] = ((iRec5[1] * iVec0[1]) + (iTemp5 * iTemp22));
			int iTemp23 = ((iRec3[0] + iRec5[0]) % iTemp4);
			int iTemp24 = (iTemp4 - 1);
			float fTemp25 = (float(iTemp23) / float(iTemp24));
			int iTemp26 = int(fTemp25);
			iRec22[0] = (((1 - iTemp26) * iRec22[1]) + (iTemp26 * iTemp22));
			int iTemp27 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec8))))));
			iRec23[0] = ((iVec0[1] * iRec23[1]) + (iTemp5 * iTemp27));
			int iTemp28 = ((iRec3[0] + iRec23[0]) % iTemp4);
			float fTemp29 = (float(iTemp28) / float(iTemp24));
			int iTemp30 = int(fTemp29);
			iRec24[0] = (((1 - iTemp30) * iRec24[1]) + (iTemp30 * iTemp27));
			int iTemp31 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec10))))));
			iRec25[0] = ((iVec0[1] * iRec25[1]) + (iTemp5 * iTemp31));
			int iTemp32 = ((iRec3[0] + iRec25[0]) % iTemp4);
			float fTemp33 = (float(iTemp32) / float(iTemp24));
			int iTemp34 = int(fTemp33);
			iRec26[0] = (((1 - iTemp34) * iRec26[1]) + (iTemp34 * iTemp31));
			int iTemp35 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec12))))));
			iRec27[0] = ((iVec0[1] * iRec27[1]) + (iTemp5 * iTemp35));
			int iTemp36 = ((iRec3[0] + iRec27[0]) % iTemp4);
			float fTemp37 = (float(iTemp36) / float(iTemp24));
			int iTemp38 = int(fTemp37);
			iRec28[0] = (((1 - iTemp38) * iRec28[1]) + (iTemp38 * iTemp35));
			int iTemp39 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec14))))));
			iRec29[0] = ((iVec0[1] * iRec29[1]) + (iTemp5 * iTemp39));
			int iTemp40 = ((iRec3[0] + iRec29[0]) % iTemp4);
			float fTemp41 = (float(iTemp40) / float(iTemp24));
			int iTemp42 = int(fTemp41);
			iRec30[0] = (((1 - iTemp42) * iRec30[1]) + (iTemp42 * iTemp39));
			int iTemp43 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec16))))));
			iRec31[0] = ((iVec0[1] * iRec31[1]) + (iTemp5 * iTemp43));
			int iTemp44 = ((iRec3[0] + iRec31[0]) % iTemp4);
			float fTemp45 = (float(iTemp44) / float(iTemp24));
			int iTemp46 = int(fTemp45);
			iRec32[0] = (((1 - iTemp46) * iRec32[1]) + (iTemp46 * iTemp43));
			int iTemp47 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec18))))));
			iRec33[0] = ((iVec0[1] * iRec33[1]) + (iTemp5 * iTemp47));
			int iTemp48 = ((iRec3[0] + iRec33[0]) % iTemp4);
			float fTemp49 = (float(iTemp48) / float(iTemp24));
			int iTemp50 = int(fTemp49);
			iRec34[0] = (((1 - iTemp50) * iRec34[1]) + (iTemp50 * iTemp47));
			int iTemp51 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec20))))));
			iRec35[0] = ((iVec0[1] * iRec35[1]) + (iTemp5 * iTemp51));
			int iTemp52 = ((iRec3[0] + iRec35[0]) % iTemp4);
			float fTemp53 = (float(iTemp52) / float(iTemp24));
			int iTemp54 = int(fTemp53);
			iRec36[0] = (((1 - iTemp54) * iRec36[1]) + (iTemp54 * iTemp51));
			output0[i] = FAUSTFLOAT(((fTemp0 * fTemp1) + (2.f * (fRec0[0] * ((((((((float(iSlow2) * (ftbl0[((iTemp23 + iRec22[0]) % iTemp2)] * sinf((6.28318f * fTemp25)))) + (float(iSlow5) * (ftbl0[((iTemp28 + iRec24[0]) % iTemp2)] * sinf((6.28318f * fTemp29))))) + (float(iSlow6) * (ftbl0[((iTemp32 + iRec26[0]) % iTemp2)] * sinf((6.28318f * fTemp33))))) + (float(iSlow7) * (ftbl0[((iTemp36 + iRec28[0]) % iTemp2)] * sinf((6.28318f * fTemp37))))) + (float(iSlow8) * (ftbl0[((iTemp40 + iRec30[0]) % iTemp2)] * sinf((6.28318f * fTemp41))))) + (float(iSlow9) * (ftbl0[((iTemp44 + iRec32[0]) % iTemp2)] * sinf((6.28318f * fTemp45))))) + (float(iSlow10) * (ftbl0[((iTemp48 + iRec34[0]) % iTemp2)] * sinf((6.28318f * fTemp49))))) + (float(iSlow11) * (ftbl0[((iTemp52 + iRec36[0]) % iTemp2)] * sinf((6.28318f * fTemp53)))))))));
			float fTemp55 = float(input1[i]);
			ftbl1[iTemp3] = fTemp55;
			int iTemp56 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec7))))));
			iRec37[0] = ((iVec0[1] * iRec37[1]) + (iTemp5 * iTemp56));
			int iTemp57 = ((iRec3[0] + iRec37[0]) % iTemp4);
			float fTemp58 = (float(iTemp57) / float(iTemp24));
			int iTemp59 = int(fTemp58);
			iRec38[0] = (((1 - iTemp59) * iRec38[1]) + (iTemp59 * iTemp56));
			int iTemp60 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec9))))));
			iRec39[0] = ((iVec0[1] * iRec39[1]) + (iTemp5 * iTemp60));
			int iTemp61 = ((iRec3[0] + iRec39[0]) % iTemp4);
			float fTemp62 = (float(iTemp61) / float(iTemp24));
			int iTemp63 = int(fTemp62);
			iRec40[0] = (((1 - iTemp63) * iRec40[1]) + (iTemp63 * iTemp60));
			int iTemp64 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec11))))));
			iRec41[0] = ((iVec0[1] * iRec41[1]) + (iTemp5 * iTemp64));
			int iTemp65 = ((iRec3[0] + iRec41[0]) % iTemp4);
			float fTemp66 = (float(iTemp65) / float(iTemp24));
			int iTemp67 = int(fTemp66);
			iRec42[0] = (((1 - iTemp67) * iRec42[1]) + (iTemp67 * iTemp64));
			int iTemp68 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec13))))));
			iRec43[0] = ((iVec0[1] * iRec43[1]) + (iTemp5 * iTemp68));
			int iTemp69 = ((iRec3[0] + iRec43[0]) % iTemp4);
			float fTemp70 = (float(iTemp69) / float(iTemp24));
			int iTemp71 = int(fTemp70);
			iRec44[0] = (((1 - iTemp71) * iRec44[1]) + (iTemp71 * iTemp68));
			int iTemp72 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec15))))));
			iRec45[0] = ((iVec0[1] * iRec45[1]) + (iTemp5 * iTemp72));
			int iTemp73 = ((iRec3[0] + iRec45[0]) % iTemp4);
			float fTemp74 = (float(iTemp73) / float(iTemp24));
			int iTemp75 = int(fTemp74);
			iRec46[0] = (((1 - iTemp75) * iRec46[1]) + (iTemp75 * iTemp72));
			int iTemp76 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec17))))));
			iRec47[0] = ((iVec0[1] * iRec47[1]) + (iTemp5 * iTemp76));
			int iTemp77 = ((iRec3[0] + iRec47[0]) % iTemp4);
			float fTemp78 = (float(iTemp77) / float(iTemp24));
			int iTemp79 = int(fTemp78);
			iRec48[0] = (((1 - iTemp79) * iRec48[1]) + (iTemp79 * iTemp76));
			int iTemp80 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec19))))));
			iRec49[0] = ((iVec0[1] * iRec49[1]) + (iTemp5 * iTemp80));
			int iTemp81 = ((iRec3[0] + iRec49[0]) % iTemp4);
			float fTemp82 = (float(iTemp81) / float(iTemp24));
			int iTemp83 = int(fTemp82);
			iRec50[0] = (((1 - iTemp83) * iRec50[1]) + (iTemp83 * iTemp80));
			int iTemp84 = int((0.5f * (float(iTemp2) * (1.f + (2.32831e-10f * float(iRec21))))));
			iRec51[0] = ((iVec0[1] * iRec51[1]) + (iTemp5 * iTemp84));
			int iTemp85 = ((iRec3[0] + iRec51[0]) % iTemp4);
			float fTemp86 = (float(iTemp85) / float(iTemp24));
			int iTemp87 = int(fTemp86);
			iRec52[0] = (((1 - iTemp87) * iRec52[1]) + (iTemp87 * iTemp84));
			output1[i] = FAUSTFLOAT(((fTemp0 * fTemp55) + (2.f * (fRec0[0] * ((((((((float(iSlow12) * (ftbl1[((iTemp57 + iRec38[0]) % iTemp2)] * sinf((6.28318f * fTemp58)))) + (float(iSlow13) * (ftbl1[((iTemp61 + iRec40[0]) % iTemp2)] * sinf((6.28318f * fTemp62))))) + (float(iSlow14) * (ftbl1[((iTemp65 + iRec42[0]) % iTemp2)] * sinf((6.28318f * fTemp66))))) + (float(iSlow15) * (ftbl1[((iTemp69 + iRec44[0]) % iTemp2)] * sinf((6.28318f * fTemp70))))) + (float(iSlow16) * (ftbl1[((iTemp73 + iRec46[0]) % iTemp2)] * sinf((6.28318f * fTemp74))))) + (float(iSlow17) * (ftbl1[((iTemp77 + iRec48[0]) % iTemp2)] * sinf((6.28318f * fTemp78))))) + (float(iSlow18) * (ftbl1[((iTemp81 + iRec50[0]) % iTemp2)] * sinf((6.28318f * fTemp82))))) + (float(iSlow19) * (ftbl1[((iTemp85 + iRec52[0]) % iTemp2)] * sinf((6.28318f * fTemp86)))))))));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec2[1] = fRec2[0];
			iRec1[1] = iRec1[0];
			fRec4[1] = fRec4[0];
			iRec3[1] = iRec3[0];
			iRec6[1] = iRec6[0];
			iRec5[1] = iRec5[0];
			iRec22[1] = iRec22[0];
			iRec23[1] = iRec23[0];
			iRec24[1] = iRec24[0];
			iRec25[1] = iRec25[0];
			iRec26[1] = iRec26[0];
			iRec27[1] = iRec27[0];
			iRec28[1] = iRec28[0];
			iRec29[1] = iRec29[0];
			iRec30[1] = iRec30[0];
			iRec31[1] = iRec31[0];
			iRec32[1] = iRec32[0];
			iRec33[1] = iRec33[0];
			iRec34[1] = iRec34[0];
			iRec35[1] = iRec35[0];
			iRec36[1] = iRec36[0];
			iRec37[1] = iRec37[0];
			iRec38[1] = iRec38[0];
			iRec39[1] = iRec39[0];
			iRec40[1] = iRec40[0];
			iRec41[1] = iRec41[0];
			iRec42[1] = iRec42[0];
			iRec43[1] = iRec43[0];
			iRec44[1] = iRec44[0];
			iRec45[1] = iRec45[0];
			iRec46[1] = iRec46[0];
			iRec47[1] = iRec47[0];
			iRec48[1] = iRec48[0];
			iRec49[1] = iRec49[0];
			iRec50[1] = iRec50[0];
			iRec51[1] = iRec51[0];
			iRec52[1] = iRec52[0];

		}

	}


};

} // namespace oldgran
