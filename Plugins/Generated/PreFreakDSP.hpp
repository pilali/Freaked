/* ------------------------------------------------------------
name: "PreFreak"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -cn PreFreakDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __PreFreakDSP_H__
#define  __PreFreakDSP_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS PreFreakDSP
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


class PreFreakDSP : public dsp {
	
 private:
	
	float fVec0[2];
	int IOTA0;
	float fVec1[65536];
	FAUSTFLOAT fHslider0;
	float fRec2[2];
	float fVec2[65536];
	float fVec3[65536];
	float fVec4[65536];
	float fVec5[65536];
	float fVec6[65536];
	float fVec7[65536];
	float fVec8[65536];
	float fVec9[65536];
	float fVec10[65536];
	float fVec11[65536];
	float fVec12[65536];
	float fVec13[65536];
	float fVec14[65536];
	float fVec15[65536];
	float fVec16[65536];
	float fVec17[65536];
	float fVec18[65536];
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	float fVec19[2];
	float fRec0[2];
	float fRec4[2];
	float fVec20[2];
	float fRec3[2];
	int fSampleRate;
	
 public:
	PreFreakDSP() {}

	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -ct 1 -cn PreFreakDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "PreFreak.dsp");
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
		m->declare("name", "PreFreak");
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
		fHslider0 = FAUSTFLOAT(0.6f);
		fHslider1 = FAUSTFLOAT(0.2f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		IOTA0 = 0;
		for (int l1 = 0; l1 < 65536; l1 = l1 + 1) {
			fVec1[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec2[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 65536; l3 = l3 + 1) {
			fVec2[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 65536; l4 = l4 + 1) {
			fVec3[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 65536; l5 = l5 + 1) {
			fVec4[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 65536; l6 = l6 + 1) {
			fVec5[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 65536; l7 = l7 + 1) {
			fVec6[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 65536; l8 = l8 + 1) {
			fVec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 65536; l9 = l9 + 1) {
			fVec8[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 65536; l10 = l10 + 1) {
			fVec9[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 65536; l11 = l11 + 1) {
			fVec10[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 65536; l12 = l12 + 1) {
			fVec11[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 65536; l13 = l13 + 1) {
			fVec12[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 65536; l14 = l14 + 1) {
			fVec13[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 65536; l15 = l15 + 1) {
			fVec14[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 65536; l16 = l16 + 1) {
			fVec15[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 65536; l17 = l17 + 1) {
			fVec16[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 65536; l18 = l18 + 1) {
			fVec17[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 65536; l19 = l19 + 1) {
			fVec18[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			fRec1[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			fVec19[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec0[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec4[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fVec20[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec3[l25] = 0.0f;
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
	
	virtual PreFreakDSP* clone() {
		return new PreFreakDSP();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("PreFreak");
		ui_interface->addHorizontalSlider("Blur", &fHslider0, FAUSTFLOAT(0.6f), FAUSTFLOAT(0.0f), FAUSTFLOAT(15.0f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("Level", &fHslider1, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.5f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.001f * std::min<float>(3e+01f, std::max<float>(0.0f, float(fHslider0)));
		float fSlow1 = 0.001f * std::min<float>(1.5f, std::max<float>(0.0f, float(fHslider1)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input1[i0]);
			float fTemp1 = float(input0[i0]);
			fVec0[0] = fTemp1 - fTemp0;
			float fTemp2 = fTemp1 + fTemp0;
			float fTemp3 = fTemp2 + fVec0[1];
			fVec1[IOTA0 & 65535] = fVec0[1] - fTemp2;
			fRec2[0] = fSlow0 + 0.999f * fRec2[1];
			float fTemp4 = fVec1[(IOTA0 - (std::max<int>(1, int(fRec2[0])) & 65535)) & 65535];
			float fTemp5 = fTemp4 + fTemp3;
			fVec2[IOTA0 & 65535] = fTemp4 - fTemp3;
			float fTemp6 = fVec2[(IOTA0 - (std::max<int>(1, int(2.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp7 = fTemp6 + fTemp5;
			fVec3[IOTA0 & 65535] = fTemp6 - fTemp5;
			float fTemp8 = fVec3[(IOTA0 - (std::max<int>(1, int(5.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp9 = fTemp8 + fTemp7;
			fVec4[IOTA0 & 65535] = fTemp8 - fTemp7;
			float fTemp10 = fVec4[(IOTA0 - (std::max<int>(1, int(7.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp11 = fTemp10 + fTemp9;
			fVec5[IOTA0 & 65535] = fTemp10 - fTemp9;
			float fTemp12 = fVec5[(IOTA0 - (std::max<int>(1, int(23.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp13 = fTemp12 + fTemp11;
			fVec6[IOTA0 & 65535] = fTemp12 - fTemp11;
			float fTemp14 = fVec6[(IOTA0 - (std::max<int>(1, int(54.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp15 = fTemp14 + fTemp13;
			fVec7[IOTA0 & 65535] = fTemp14 - fTemp13;
			float fTemp16 = fVec7[(IOTA0 - (std::max<int>(1, int(79.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp17 = fTemp16 + fTemp15;
			fVec8[IOTA0 & 65535] = fTemp16 - fTemp15;
			float fTemp18 = fVec8[(IOTA0 - (std::max<int>(1, int(2.2e+02f * fRec2[0])) & 65535)) & 65535];
			float fTemp19 = fTemp18 + fTemp17;
			fVec9[IOTA0 & 65535] = fTemp18 - fTemp17;
			float fTemp20 = fVec9[(IOTA0 - (std::max<int>(1, int(3.4e+02f * fRec2[0])) & 65535)) & 65535];
			float fTemp21 = fTemp20 + fTemp19;
			fVec10[IOTA0 & 65535] = fTemp20 - fTemp19;
			float fTemp22 = fVec10[(IOTA0 - (std::max<int>(1, int(454.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp23 = fTemp22 + fTemp21;
			fVec11[IOTA0 & 65535] = fTemp22 - fTemp21;
			float fTemp24 = fVec11[(IOTA0 - (std::max<int>(1, int(623.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp25 = fTemp24 + fTemp23;
			fVec12[IOTA0 & 65535] = fTemp24 - fTemp23;
			float fTemp26 = fVec12[(IOTA0 - (std::max<int>(1, int(845.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp27 = fTemp26 + fTemp25;
			fVec13[IOTA0 & 65535] = fTemp26 - fTemp25;
			float fTemp28 = fVec13[(IOTA0 - (std::max<int>(1, int(1304.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp29 = fTemp28 + fTemp27;
			fVec14[IOTA0 & 65535] = fTemp28 - fTemp27;
			float fTemp30 = fVec14[(IOTA0 - (std::max<int>(1, int(1532.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp31 = fTemp30 + fTemp29;
			fVec15[IOTA0 & 65535] = fTemp30 - fTemp29;
			float fTemp32 = fVec15[(IOTA0 - (std::max<int>(1, int(2204.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp33 = fTemp32 + fTemp31;
			fVec16[IOTA0 & 65535] = fTemp32 - fTemp31;
			float fTemp34 = fVec16[(IOTA0 - (std::max<int>(1, int(3137.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp35 = fTemp34 + fTemp33;
			fVec17[IOTA0 & 65535] = fTemp34 - fTemp33;
			float fTemp36 = fVec17[(IOTA0 - (std::max<int>(1, int(3567.0f * fRec2[0])) & 65535)) & 65535];
			fVec18[IOTA0 & 65535] = fTemp36 - fTemp35;
			fRec1[0] = 0.999f * fRec1[1] + fSlow1 * fVec18[(IOTA0 - (std::max<int>(1, int(4218.0f * fRec2[0])) & 65535)) & 65535];
			float fTemp37 = std::min<float>(1.0f, std::max<float>(-1.0f, fRec1[0]));
			fVec19[0] = fTemp37;
			fRec0[0] = fTemp37 + 0.995f * fRec0[1] - fVec19[1];
			output0[i0] = FAUSTFLOAT(fRec0[0]);
			fRec4[0] = 0.999f * fRec4[1] + fSlow1 * (fTemp36 + fTemp35);
			float fTemp38 = std::min<float>(1.0f, std::max<float>(-1.0f, fRec4[0]));
			fVec20[0] = fTemp38;
			fRec3[0] = fTemp38 + 0.995f * fRec3[1] - fVec20[1];
			output1[i0] = FAUSTFLOAT(fRec3[0]);
			fVec0[1] = fVec0[0];
			IOTA0 = IOTA0 + 1;
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fVec19[1] = fVec19[0];
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fVec20[1] = fVec20[0];
			fRec3[1] = fRec3[0];
		}
	}

};

#endif
