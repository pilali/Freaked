/* ------------------------------------------------------------
name: "Freaktail"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -cn FreaktailDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __FreaktailDSP_H__
#define  __FreaktailDSP_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS FreaktailDSP
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif


class FreaktailDSP : public dsp {
	
 private:
	
	int IOTA0;
	FAUSTFLOAT fHslider0;
	float fRec2[2];
	float fVec0[2];
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	FAUSTFLOAT fHslider2;
	float fRec1[32768];
	float fRec4[32768];
	float fRec5[32768];
	float fRec6[16384];
	float fRec7[4096];
	float fVec1[2];
	float fRec0[2];
	float fRec9[32768];
	float fRec10[8192];
	float fRec11[32768];
	float fRec12[16384];
	float fRec13[8192];
	float fVec2[2];
	float fRec8[2];
	int fSampleRate;
	
 public:
	FreaktailDSP() {}

	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -ct 1 -cn FreaktailDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "Freaktail.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "Freaktail");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.8f);
		fHslider1 = FAUSTFLOAT(0.81f);
		fHslider2 = FAUSTFLOAT(0.81f);
	}
	
	virtual void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec2[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec3[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 32768; l3 = l3 + 1) {
			fRec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 32768; l4 = l4 + 1) {
			fRec4[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 32768; l5 = l5 + 1) {
			fRec5[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 16384; l6 = l6 + 1) {
			fRec6[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 4096; l7 = l7 + 1) {
			fRec7[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fVec1[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec0[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 32768; l10 = l10 + 1) {
			fRec9[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 8192; l11 = l11 + 1) {
			fRec10[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 32768; l12 = l12 + 1) {
			fRec11[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 16384; l13 = l13 + 1) {
			fRec12[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 8192; l14 = l14 + 1) {
			fRec13[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fVec2[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec8[l16] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual FreaktailDSP* clone() {
		return new FreaktailDSP();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Freaktail");
		ui_interface->addHorizontalSlider("Decay", &fHslider1, FAUSTFLOAT(0.81f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("Roomsize", &fHslider0, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.01f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("Tail level", &fHslider2, FAUSTFLOAT(0.81f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.001f * float(fHslider0);
		float fSlow1 = 0.001f * float(fHslider1);
		float fSlow2 = std::min<float>(1.0f, std::max<float>(0.0f, float(fHslider2)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec2[0] = fSlow0 + 0.999f * fRec2[1];
			float fTemp0 = std::min<float>(5.0f, std::max<float>(0.1f, fRec2[0]));
			fVec0[0] = fTemp0;
			float fTemp1 = fTemp0 + fVec0[1];
			fRec3[0] = fSlow1 + 0.999f * fRec3[1];
			float fTemp2 = std::min<float>(1.0f, std::max<float>(0.0f, fRec3[0]));
			float fTemp3 = fSlow2 * float(input0[i0]);
			fRec1[IOTA0 & 32767] = fTemp3 + fTemp2 * fRec1[(IOTA0 - (int(2.6e+03f * fTemp1) + 1)) & 32767];
			fRec4[IOTA0 & 32767] = fTemp3 + fTemp2 * fRec4[(IOTA0 - (int(2913.0f * fTemp1) + 1)) & 32767];
			fRec5[IOTA0 & 32767] = fTemp3 + fTemp2 * fRec5[(IOTA0 - (int(1723.0f * fTemp1) + 1)) & 32767];
			fRec6[IOTA0 & 16383] = fTemp3 + fTemp2 * fRec6[(IOTA0 - (int(1025.0f * fTemp1) + 1)) & 16383];
			fRec7[IOTA0 & 4095] = fTemp2 * fRec7[(IOTA0 - (int(301.0f * fTemp1) + 1)) & 4095] + fTemp3;
			float fTemp4 = fRec7[IOTA0 & 4095] + fRec6[IOTA0 & 16383] + fRec5[IOTA0 & 32767] + fRec4[IOTA0 & 32767] + fRec1[IOTA0 & 32767];
			fVec1[0] = fTemp4;
			fRec0[0] = fTemp4 + 0.995f * fRec0[1] - fVec1[1];
			output0[i0] = FAUSTFLOAT(std::min<float>(1.0f, std::max<float>(-1.0f, fRec0[0])));
			float fTemp5 = fSlow2 * float(input1[i0]);
			fRec9[IOTA0 & 32767] = fTemp5 + fTemp2 * fRec9[(IOTA0 - (int(3137.0f * fTemp1) + 1)) & 32767];
			fRec10[IOTA0 & 8191] = fTemp5 + fTemp2 * fRec10[(IOTA0 - (int(506.0f * fTemp1) + 1)) & 8191];
			fRec11[IOTA0 & 32767] = fTemp5 + fTemp2 * fRec11[(IOTA0 - (int(2317.0f * fTemp1) + 1)) & 32767];
			fRec12[IOTA0 & 16383] = fTemp5 + fTemp2 * fRec12[(IOTA0 - (int(1317.0f * fTemp1) + 1)) & 16383];
			fRec13[IOTA0 & 8191] = fTemp2 * fRec13[(IOTA0 - (int(461.0f * fTemp1) + 1)) & 8191] + fTemp5;
			float fTemp6 = fRec13[IOTA0 & 8191] + fRec12[IOTA0 & 16383] + fRec11[IOTA0 & 32767] + fRec10[IOTA0 & 8191] + fRec9[IOTA0 & 32767];
			fVec2[0] = fTemp6;
			fRec8[0] = fTemp6 + 0.995f * fRec8[1] - fVec2[1];
			output1[i0] = FAUSTFLOAT(std::min<float>(1.0f, std::max<float>(-1.0f, fRec8[0])));
			IOTA0 = IOTA0 + 1;
			fRec2[1] = fRec2[0];
			fVec0[1] = fVec0[0];
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			fRec0[1] = fRec0[0];
			fVec2[1] = fVec2[0];
			fRec8[1] = fRec8[0];
		}
	}

};

#endif
