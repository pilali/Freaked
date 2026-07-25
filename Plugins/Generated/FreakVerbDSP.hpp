/* ------------------------------------------------------------
author: "Pjotr Lasschuit"
name: "FreakVerb"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -cn FreakVerbDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __FreakVerbDSP_H__
#define  __FreakVerbDSP_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS FreakVerbDSP
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


class FreakVerbDSP : public dsp {
	
 private:
	
	int IOTA0;
	FAUSTFLOAT fHslider0;
	float fRec2[2];
	float fVec0[2];
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	float fVec1[2];
	float fVec2[65536];
	FAUSTFLOAT fHslider2;
	float fRec6[2];
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
	float fVec19[65536];
	FAUSTFLOAT fHslider3;
	float fRec5[2];
	float fVec20[2];
	float fRec4[2];
	FAUSTFLOAT fHslider4;
	float fRec1[32768];
	float fRec7[32768];
	float fRec8[32768];
	float fRec9[16384];
	float fRec10[4096];
	float fVec21[2];
	float fRec0[2];
	float fRec14[2];
	float fVec22[2];
	float fRec13[2];
	float fRec12[32768];
	float fRec15[8192];
	float fRec16[32768];
	float fRec17[16384];
	float fRec18[8192];
	float fVec23[2];
	float fRec11[2];
	int fSampleRate;
	
 public:
	FreakVerbDSP() {}

	void metadata(Meta* m) { 
		m->declare("author", "Pjotr Lasschuit");
		m->declare("compile_options", "-lang cpp -ct 1 -cn FreakVerbDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "FreakVerb.dsp");
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
		m->declare("name", "FreakVerb");
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
		fHslider2 = FAUSTFLOAT(0.6f);
		fHslider3 = FAUSTFLOAT(0.2f);
		fHslider4 = FAUSTFLOAT(0.81f);
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
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fVec1[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 65536; l4 = l4 + 1) {
			fVec2[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 65536; l6 = l6 + 1) {
			fVec3[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 65536; l7 = l7 + 1) {
			fVec4[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 65536; l8 = l8 + 1) {
			fVec5[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 65536; l9 = l9 + 1) {
			fVec6[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 65536; l10 = l10 + 1) {
			fVec7[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 65536; l11 = l11 + 1) {
			fVec8[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 65536; l12 = l12 + 1) {
			fVec9[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 65536; l13 = l13 + 1) {
			fVec10[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 65536; l14 = l14 + 1) {
			fVec11[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 65536; l15 = l15 + 1) {
			fVec12[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 65536; l16 = l16 + 1) {
			fVec13[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 65536; l17 = l17 + 1) {
			fVec14[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 65536; l18 = l18 + 1) {
			fVec15[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 65536; l19 = l19 + 1) {
			fVec16[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 65536; l20 = l20 + 1) {
			fVec17[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 65536; l21 = l21 + 1) {
			fVec18[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 65536; l22 = l22 + 1) {
			fVec19[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec5[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			fVec20[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec4[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 32768; l26 = l26 + 1) {
			fRec1[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 32768; l27 = l27 + 1) {
			fRec7[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 32768; l28 = l28 + 1) {
			fRec8[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 16384; l29 = l29 + 1) {
			fRec9[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 4096; l30 = l30 + 1) {
			fRec10[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fVec21[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec0[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			fRec14[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fVec22[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec13[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 32768; l36 = l36 + 1) {
			fRec12[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 8192; l37 = l37 + 1) {
			fRec15[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 32768; l38 = l38 + 1) {
			fRec16[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 16384; l39 = l39 + 1) {
			fRec17[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 8192; l40 = l40 + 1) {
			fRec18[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fVec23[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 2; l42 = l42 + 1) {
			fRec11[l42] = 0.0f;
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
	
	virtual FreakVerbDSP* clone() {
		return new FreakVerbDSP();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("FreakVerb");
		ui_interface->addHorizontalSlider("Blur", &fHslider2, FAUSTFLOAT(0.6f), FAUSTFLOAT(0.0f), FAUSTFLOAT(15.0f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("Decay", &fHslider1, FAUSTFLOAT(0.81f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("Level", &fHslider3, FAUSTFLOAT(0.2f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.5f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Roomsize", &fHslider0, FAUSTFLOAT(0.8f), FAUSTFLOAT(0.01f), FAUSTFLOAT(5.0f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("Tail level", &fHslider4, FAUSTFLOAT(0.81f), FAUSTFLOAT(0.1f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.001f * float(fHslider0);
		float fSlow1 = 0.001f * float(fHslider1);
		float fSlow2 = 0.001f * std::min<float>(3e+01f, std::max<float>(0.0f, float(fHslider2)));
		float fSlow3 = 0.001f * std::min<float>(1.5f, std::max<float>(0.0f, float(fHslider3)));
		float fSlow4 = std::min<float>(1.0f, std::max<float>(0.0f, float(fHslider4)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec2[0] = fSlow0 + 0.999f * fRec2[1];
			float fTemp0 = std::min<float>(5.0f, std::max<float>(0.1f, fRec2[0]));
			fVec0[0] = fTemp0;
			float fTemp1 = fTemp0 + fVec0[1];
			fRec3[0] = fSlow1 + 0.999f * fRec3[1];
			float fTemp2 = std::min<float>(1.0f, std::max<float>(0.0f, fRec3[0]));
			float fTemp3 = float(input1[i0]);
			float fTemp4 = float(input0[i0]);
			fVec1[0] = fTemp4 - fTemp3;
			float fTemp5 = fTemp4 + fTemp3;
			float fTemp6 = fTemp5 + fVec1[1];
			fVec2[IOTA0 & 65535] = fVec1[1] - fTemp5;
			fRec6[0] = fSlow2 + 0.999f * fRec6[1];
			float fTemp7 = fVec2[(IOTA0 - (std::max<int>(1, int(fRec6[0])) & 65535)) & 65535];
			float fTemp8 = fTemp7 + fTemp6;
			fVec3[IOTA0 & 65535] = fTemp7 - fTemp6;
			float fTemp9 = fVec3[(IOTA0 - (std::max<int>(1, int(2.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp10 = fTemp9 + fTemp8;
			fVec4[IOTA0 & 65535] = fTemp9 - fTemp8;
			float fTemp11 = fVec4[(IOTA0 - (std::max<int>(1, int(5.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp12 = fTemp11 + fTemp10;
			fVec5[IOTA0 & 65535] = fTemp11 - fTemp10;
			float fTemp13 = fVec5[(IOTA0 - (std::max<int>(1, int(7.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp14 = fTemp13 + fTemp12;
			fVec6[IOTA0 & 65535] = fTemp13 - fTemp12;
			float fTemp15 = fVec6[(IOTA0 - (std::max<int>(1, int(23.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp16 = fTemp15 + fTemp14;
			fVec7[IOTA0 & 65535] = fTemp15 - fTemp14;
			float fTemp17 = fVec7[(IOTA0 - (std::max<int>(1, int(54.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp18 = fTemp17 + fTemp16;
			fVec8[IOTA0 & 65535] = fTemp17 - fTemp16;
			float fTemp19 = fVec8[(IOTA0 - (std::max<int>(1, int(79.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp20 = fTemp19 + fTemp18;
			fVec9[IOTA0 & 65535] = fTemp19 - fTemp18;
			float fTemp21 = fVec9[(IOTA0 - (std::max<int>(1, int(2.2e+02f * fRec6[0])) & 65535)) & 65535];
			float fTemp22 = fTemp21 + fTemp20;
			fVec10[IOTA0 & 65535] = fTemp21 - fTemp20;
			float fTemp23 = fVec10[(IOTA0 - (std::max<int>(1, int(3.4e+02f * fRec6[0])) & 65535)) & 65535];
			float fTemp24 = fTemp23 + fTemp22;
			fVec11[IOTA0 & 65535] = fTemp23 - fTemp22;
			float fTemp25 = fVec11[(IOTA0 - (std::max<int>(1, int(454.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp26 = fTemp25 + fTemp24;
			fVec12[IOTA0 & 65535] = fTemp25 - fTemp24;
			float fTemp27 = fVec12[(IOTA0 - (std::max<int>(1, int(623.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp28 = fTemp27 + fTemp26;
			fVec13[IOTA0 & 65535] = fTemp27 - fTemp26;
			float fTemp29 = fVec13[(IOTA0 - (std::max<int>(1, int(845.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp30 = fTemp29 + fTemp28;
			fVec14[IOTA0 & 65535] = fTemp29 - fTemp28;
			float fTemp31 = fVec14[(IOTA0 - (std::max<int>(1, int(1304.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp32 = fTemp31 + fTemp30;
			fVec15[IOTA0 & 65535] = fTemp31 - fTemp30;
			float fTemp33 = fVec15[(IOTA0 - (std::max<int>(1, int(1532.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp34 = fTemp33 + fTemp32;
			fVec16[IOTA0 & 65535] = fTemp33 - fTemp32;
			float fTemp35 = fVec16[(IOTA0 - (std::max<int>(1, int(2204.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp36 = fTemp35 + fTemp34;
			fVec17[IOTA0 & 65535] = fTemp35 - fTemp34;
			float fTemp37 = fVec17[(IOTA0 - (std::max<int>(1, int(3137.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp38 = fTemp37 + fTemp36;
			fVec18[IOTA0 & 65535] = fTemp37 - fTemp36;
			float fTemp39 = fVec18[(IOTA0 - (std::max<int>(1, int(3567.0f * fRec6[0])) & 65535)) & 65535];
			fVec19[IOTA0 & 65535] = fTemp39 - fTemp38;
			fRec5[0] = 0.999f * fRec5[1] + fSlow3 * fVec19[(IOTA0 - (std::max<int>(1, int(4218.0f * fRec6[0])) & 65535)) & 65535];
			float fTemp40 = std::min<float>(1.0f, std::max<float>(-1.0f, fRec5[0]));
			fVec20[0] = fTemp40;
			fRec4[0] = fTemp40 + 0.995f * fRec4[1] - fVec20[1];
			float fTemp41 = fSlow4 * fRec4[0];
			fRec1[IOTA0 & 32767] = fTemp41 + fTemp2 * fRec1[(IOTA0 - (int(2.6e+03f * fTemp1) + 1)) & 32767];
			fRec7[IOTA0 & 32767] = fTemp41 + fTemp2 * fRec7[(IOTA0 - (int(2913.0f * fTemp1) + 1)) & 32767];
			fRec8[IOTA0 & 32767] = fTemp41 + fTemp2 * fRec8[(IOTA0 - (int(1723.0f * fTemp1) + 1)) & 32767];
			fRec9[IOTA0 & 16383] = fTemp41 + fTemp2 * fRec9[(IOTA0 - (int(1025.0f * fTemp1) + 1)) & 16383];
			fRec10[IOTA0 & 4095] = fTemp2 * fRec10[(IOTA0 - (int(301.0f * fTemp1) + 1)) & 4095] + fTemp41;
			float fTemp42 = fRec10[IOTA0 & 4095] + fRec9[IOTA0 & 16383] + fRec8[IOTA0 & 32767] + fRec7[IOTA0 & 32767] + fRec1[IOTA0 & 32767];
			fVec21[0] = fTemp42;
			fRec0[0] = fTemp42 + 0.995f * fRec0[1] - fVec21[1];
			output0[i0] = FAUSTFLOAT(std::min<float>(1.0f, std::max<float>(-1.0f, fRec0[0])));
			fRec14[0] = 0.999f * fRec14[1] + fSlow3 * (fTemp39 + fTemp38);
			float fTemp43 = std::min<float>(1.0f, std::max<float>(-1.0f, fRec14[0]));
			fVec22[0] = fTemp43;
			fRec13[0] = fTemp43 + 0.995f * fRec13[1] - fVec22[1];
			float fTemp44 = fSlow4 * fRec13[0];
			fRec12[IOTA0 & 32767] = fTemp44 + fTemp2 * fRec12[(IOTA0 - (int(3137.0f * fTemp1) + 1)) & 32767];
			fRec15[IOTA0 & 8191] = fTemp44 + fTemp2 * fRec15[(IOTA0 - (int(506.0f * fTemp1) + 1)) & 8191];
			fRec16[IOTA0 & 32767] = fTemp44 + fTemp2 * fRec16[(IOTA0 - (int(2317.0f * fTemp1) + 1)) & 32767];
			fRec17[IOTA0 & 16383] = fTemp44 + fTemp2 * fRec17[(IOTA0 - (int(1317.0f * fTemp1) + 1)) & 16383];
			fRec18[IOTA0 & 8191] = fTemp2 * fRec18[(IOTA0 - (int(461.0f * fTemp1) + 1)) & 8191] + fTemp44;
			float fTemp45 = fRec18[IOTA0 & 8191] + fRec17[IOTA0 & 16383] + fRec16[IOTA0 & 32767] + fRec15[IOTA0 & 8191] + fRec12[IOTA0 & 32767];
			fVec23[0] = fTemp45;
			fRec11[0] = fTemp45 + 0.995f * fRec11[1] - fVec23[1];
			output1[i0] = FAUSTFLOAT(std::min<float>(1.0f, std::max<float>(-1.0f, fRec11[0])));
			IOTA0 = IOTA0 + 1;
			fRec2[1] = fRec2[0];
			fVec0[1] = fVec0[0];
			fRec3[1] = fRec3[0];
			fVec1[1] = fVec1[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fVec20[1] = fVec20[0];
			fRec4[1] = fRec4[0];
			fVec21[1] = fVec21[0];
			fRec0[1] = fRec0[0];
			fRec14[1] = fRec14[0];
			fVec22[1] = fVec22[0];
			fRec13[1] = fRec13[0];
			fVec23[1] = fVec23[0];
			fRec11[1] = fRec11[0];
		}
	}

};

#endif
