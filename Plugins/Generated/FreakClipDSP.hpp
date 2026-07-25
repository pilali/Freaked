/* ------------------------------------------------------------
name: "FreakClip"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -cn FreakClipDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __FreakClipDSP_H__
#define  __FreakClipDSP_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS FreakClipDSP
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


class FreakClipDSP : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	float fRec1[2];
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	FAUSTFLOAT fHslider2;
	float fRec4[2];
	float fVec0[2];
	float fRec2[2];
	float fVec1[2];
	float fRec0[2];
	int fSampleRate;
	
 public:
	FreakClipDSP() {}

	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -ct 1 -cn FreakClipDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "FreakClip.dsp");
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
		m->declare("name", "FreakClip");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(0.996f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec3[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec4[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fVec0[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec2[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fVec1[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec0[l6] = 0.0f;
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
	
	virtual FreakClipDSP* clone() {
		return new FreakClipDSP();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FreakClip");
		ui_interface->addHorizontalSlider("Clip", &fHslider0, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Delay", &fHslider2, FAUSTFLOAT(0.996f), FAUSTFLOAT(0.0f), FAUSTFLOAT(0.999f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("Drive", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(9.9f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = 0.001f * float(fHslider0);
		float fSlow1 = 0.001f * (std::min<float>(9.9f, std::max<float>(1.0f, float(fHslider1))) + -1e+01f);
		float fSlow2 = 0.001f * float(fHslider2);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec1[0] = fSlow0 + 0.999f * fRec1[1];
			fRec3[0] = 0.999f * fRec3[1] - fSlow1;
			float fTemp0 = float(input0[i0]);
			fRec4[0] = fSlow2 + 0.999f * fRec4[1];
			fVec0[0] = fRec4[0] * fRec2[1];
			fRec2[0] = fVec0[1] - fTemp0 / fRec3[0];
			float fTemp1 = std::min<float>(fRec1[0], std::max<float>(-fRec1[0], fTemp0 + fRec2[0]));
			fVec1[0] = fTemp1;
			fRec0[0] = 0.995f * fRec0[1] + fTemp1 - fVec1[1];
			output0[i0] = FAUSTFLOAT(fRec0[0]);
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fVec0[1] = fVec0[0];
			fRec2[1] = fRec2[0];
			fVec1[1] = fVec1[0];
			fRec0[1] = fRec0[0];
		}
	}

};

#endif
