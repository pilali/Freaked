/* ------------------------------------------------------------
author: "Mayank Sanganeria"
name: "Granulator"
version: "1.2"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -cn GranulatorDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __GranulatorDSP_H__
#define  __GranulatorDSP_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS GranulatorDSP
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

class GranulatorDSPSIG0 {
	
  private:
	
	
  public:
	
	int getNumInputsGranulatorDSPSIG0() {
		return 0;
	}
	int getNumOutputsGranulatorDSPSIG0() {
		return 1;
	}
	
	void instanceInitGranulatorDSPSIG0(int sample_rate) {
	}
	
	void fillGranulatorDSPSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			table[i1] = 0.0f;
		}
	}

};

static GranulatorDSPSIG0* newGranulatorDSPSIG0() { return (GranulatorDSPSIG0*)new GranulatorDSPSIG0(); }
static void deleteGranulatorDSPSIG0(GranulatorDSPSIG0* dsp) { delete dsp; }


class GranulatorDSP : public dsp {
	
 private:
	
	int iVec0[2];
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	int fSampleRate;
	float fConst0;
	int iRec2[2];
	FAUSTFLOAT fHslider1;
	float fRec18[2];
	int iRec1[2];
	int iRec19[2];
	float ftbl0[960000];
	int iRec20[2];
	int iRec21[2];
	FAUSTFLOAT fHslider2;
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
	FAUSTFLOAT fHslider3;
	float fRec36[2];
	int iRec37[2];
	float ftbl1[960000];
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
	
 public:
	GranulatorDSP() {}

	void metadata(Meta* m) { 
		m->declare("author", "Mayank Sanganeria");
		m->declare("compile_options", "-lang cpp -ct 1 -cn GranulatorDSP -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "granulator.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("maintainer", "Pjotr Lasschuit");
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
		m->declare("name", "Granulator");
		m->declare("version", "1.2");
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
		fConst0 = float(int(std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)))));
		GranulatorDSPSIG0* sig0 = newGranulatorDSPSIG0();
		sig0->instanceInitGranulatorDSPSIG0(sample_rate);
		sig0->fillGranulatorDSPSIG0(960000, ftbl0);
		sig0->instanceInitGranulatorDSPSIG0(sample_rate);
		sig0->fillGranulatorDSPSIG0(960000, ftbl1);
		deleteGranulatorDSPSIG0(sig0);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.1f);
		fHslider1 = FAUSTFLOAT(1e+01f);
		fHslider2 = FAUSTFLOAT(2.0f);
		fHslider3 = FAUSTFLOAT(0.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec0[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iRec2[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec18[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			iRec1[l4] = 0;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			iRec19[l5] = 0;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			iRec20[l6] = 0;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			iRec21[l7] = 0;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			iRec22[l8] = 0;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			iRec23[l9] = 0;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			iRec24[l10] = 0;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			iRec25[l11] = 0;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			iRec26[l12] = 0;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			iRec27[l13] = 0;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			iRec28[l14] = 0;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			iRec29[l15] = 0;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			iRec30[l16] = 0;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			iRec31[l17] = 0;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			iRec32[l18] = 0;
		}
		for (int l19 = 0; l19 < 2; l19 = l19 + 1) {
			iRec33[l19] = 0;
		}
		for (int l20 = 0; l20 < 2; l20 = l20 + 1) {
			iRec34[l20] = 0;
		}
		for (int l21 = 0; l21 < 2; l21 = l21 + 1) {
			iRec35[l21] = 0;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fRec36[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			iRec37[l23] = 0;
		}
		for (int l24 = 0; l24 < 2; l24 = l24 + 1) {
			iRec38[l24] = 0;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			iRec39[l25] = 0;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			iRec40[l26] = 0;
		}
		for (int l27 = 0; l27 < 2; l27 = l27 + 1) {
			iRec41[l27] = 0;
		}
		for (int l28 = 0; l28 < 2; l28 = l28 + 1) {
			iRec42[l28] = 0;
		}
		for (int l29 = 0; l29 < 2; l29 = l29 + 1) {
			iRec43[l29] = 0;
		}
		for (int l30 = 0; l30 < 2; l30 = l30 + 1) {
			iRec44[l30] = 0;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			iRec45[l31] = 0;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			iRec46[l32] = 0;
		}
		for (int l33 = 0; l33 < 2; l33 = l33 + 1) {
			iRec47[l33] = 0;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			iRec48[l34] = 0;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			iRec49[l35] = 0;
		}
		for (int l36 = 0; l36 < 2; l36 = l36 + 1) {
			iRec50[l36] = 0;
		}
		for (int l37 = 0; l37 < 2; l37 = l37 + 1) {
			iRec51[l37] = 0;
		}
		for (int l38 = 0; l38 < 2; l38 = l38 + 1) {
			iRec52[l38] = 0;
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
	
	virtual GranulatorDSP* clone() {
		return new GranulatorDSP();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Granulator");
		ui_interface->addHorizontalSlider("delay length", &fHslider1, FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.5f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("grain density", &fHslider2, FAUSTFLOAT(2.0f), FAUSTFLOAT(2.0f), FAUSTFLOAT(16.0f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("grain length", &fHslider0, FAUSTFLOAT(0.1f), FAUSTFLOAT(0.01f), FAUSTFLOAT(0.5f), FAUSTFLOAT(0.01f));
		ui_interface->addHorizontalSlider("mix", &fHslider3, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 0.001f * float(fHslider0);
		float fSlow1 = 0.001f * float(fHslider1);
		float fSlow2 = float(fHslider2);
		float fSlow3 = float(14.0f < fSlow2);
		float fSlow4 = float(12.0f < fSlow2);
		float fSlow5 = float(1e+01f < fSlow2);
		float fSlow6 = float(8.0f < fSlow2);
		float fSlow7 = float(6.0f < fSlow2);
		float fSlow8 = float(4.0f < fSlow2);
		float fSlow9 = float(2.0f < fSlow2);
		float fSlow10 = float(0.0f < fSlow2);
		float fSlow11 = 0.001f * float(fHslider3);
		float fSlow12 = float(15.0f < fSlow2);
		float fSlow13 = float(13.0f < fSlow2);
		float fSlow14 = float(11.0f < fSlow2);
		float fSlow15 = float(9.0f < fSlow2);
		float fSlow16 = float(7.0f < fSlow2);
		float fSlow17 = float(5.0f < fSlow2);
		float fSlow18 = float(3.0f < fSlow2);
		float fSlow19 = float(1.0f < fSlow2);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec0[0] = 1;
			fRec0[0] = fSlow0 + 0.999f * fRec0[1];
			int iTemp0 = std::max<int>(2, int(fConst0 * fRec0[0]));
			float fTemp1 = float(iTemp0 + -1);
			int iTemp2 = 1103515245 * (iRec2[1] + 12345);
			int iTemp3 = 1103515245 * (iTemp2 + 12345);
			int iTemp4 = 1103515245 * (iTemp3 + 12345);
			int iTemp5 = 1103515245 * (iTemp4 + 12345);
			int iTemp6 = 1103515245 * (iTemp5 + 12345);
			int iTemp7 = 1103515245 * (iTemp6 + 12345);
			int iTemp8 = 1103515245 * (iTemp7 + 12345);
			int iTemp9 = 1103515245 * (iTemp8 + 12345);
			int iTemp10 = 1103515245 * (iTemp9 + 12345);
			int iTemp11 = 1103515245 * (iTemp10 + 12345);
			int iTemp12 = 1103515245 * (iTemp11 + 12345);
			int iTemp13 = 1103515245 * (iTemp12 + 12345);
			int iTemp14 = 1103515245 * (iTemp13 + 12345);
			int iTemp15 = 1103515245 * (iTemp14 + 12345);
			int iTemp16 = 1103515245 * (iTemp15 + 12345);
			int iTemp17 = 1103515245 * (iTemp16 + 12345);
			iRec2[0] = 1103515245 * (iTemp17 + 12345);
			int iRec3 = iTemp17;
			int iRec4 = iTemp16;
			int iRec5 = iTemp15;
			int iRec6 = iTemp14;
			int iRec7 = iTemp13;
			int iRec8 = iTemp12;
			int iRec9 = iTemp11;
			int iRec10 = iTemp10;
			int iRec11 = iTemp9;
			int iRec12 = iTemp8;
			int iRec13 = iTemp7;
			int iRec14 = iTemp6;
			int iRec15 = iTemp5;
			int iRec16 = iTemp4;
			int iRec17 = iTemp3;
			fRec18[0] = fSlow1 + 0.999f * fRec18[1];
			int iTemp18 = std::max<int>(1, int(std::min<float>(fConst0 * fRec18[0], 959999.0f)));
			float fTemp19 = float(iTemp18);
			int iTemp20 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec16) + 1.0f));
			int iTemp21 = 1 - iVec0[1];
			iRec1[0] = iVec0[1] * iRec1[1] + iTemp21 * iTemp20;
			iRec19[0] = (iRec19[1] + 1) % iTemp0;
			int iTemp22 = (iRec19[0] + iRec1[0]) % iTemp0;
			float fTemp23 = float(iTemp22) / fTemp1;
			float fTemp24 = float(input0[i0]);
			iRec20[0] = 1 % iTemp18 + iRec20[1];
			int iTemp25 = iRec20[0] % iTemp18;
			ftbl0[iTemp25] = fTemp24;
			int iTemp26 = int(fTemp23);
			iRec21[0] = iRec21[1] * (1 - iTemp26) + iTemp20 * iTemp26;
			int iTemp27 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec14) + 1.0f));
			iRec22[0] = iVec0[1] * iRec22[1] + iTemp21 * iTemp27;
			int iTemp28 = (iRec19[0] + iRec22[0]) % iTemp0;
			float fTemp29 = float(iTemp28) / fTemp1;
			int iTemp30 = int(fTemp29);
			iRec23[0] = iRec23[1] * (1 - iTemp30) + iTemp27 * iTemp30;
			int iTemp31 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec12) + 1.0f));
			iRec24[0] = iVec0[1] * iRec24[1] + iTemp21 * iTemp31;
			int iTemp32 = (iRec19[0] + iRec24[0]) % iTemp0;
			float fTemp33 = float(iTemp32) / fTemp1;
			int iTemp34 = int(fTemp33);
			iRec25[0] = iRec25[1] * (1 - iTemp34) + iTemp31 * iTemp34;
			int iTemp35 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec10) + 1.0f));
			iRec26[0] = iVec0[1] * iRec26[1] + iTemp21 * iTemp35;
			int iTemp36 = (iRec19[0] + iRec26[0]) % iTemp0;
			float fTemp37 = float(iTemp36) / fTemp1;
			int iTemp38 = int(fTemp37);
			iRec27[0] = iRec27[1] * (1 - iTemp38) + iTemp35 * iTemp38;
			int iTemp39 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec8) + 1.0f));
			iRec28[0] = iVec0[1] * iRec28[1] + iTemp21 * iTemp39;
			int iTemp40 = (iRec19[0] + iRec28[0]) % iTemp0;
			float fTemp41 = float(iTemp40) / fTemp1;
			int iTemp42 = int(fTemp41);
			iRec29[0] = iRec29[1] * (1 - iTemp42) + iTemp39 * iTemp42;
			int iTemp43 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec6) + 1.0f));
			iRec30[0] = iVec0[1] * iRec30[1] + iTemp21 * iTemp43;
			int iTemp44 = (iRec19[0] + iRec30[0]) % iTemp0;
			float fTemp45 = float(iTemp44) / fTemp1;
			int iTemp46 = int(fTemp45);
			iRec31[0] = iRec31[1] * (1 - iTemp46) + iTemp43 * iTemp46;
			int iTemp47 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec4) + 1.0f));
			iRec32[0] = iVec0[1] * iRec32[1] + iTemp21 * iTemp47;
			int iTemp48 = (iRec19[0] + iRec32[0]) % iTemp0;
			float fTemp49 = float(iTemp48) / fTemp1;
			int iTemp50 = int(fTemp49);
			iRec33[0] = iRec33[1] * (1 - iTemp50) + iTemp47 * iTemp50;
			int iTemp51 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec2[0]) + 1.0f));
			iRec34[0] = iVec0[1] * iRec34[1] + iTemp21 * iTemp51;
			int iTemp52 = (iRec19[0] + iRec34[0]) % iTemp0;
			float fTemp53 = float(iTemp52) / fTemp1;
			int iTemp54 = int(fTemp53);
			iRec35[0] = iRec35[1] * (1 - iTemp54) + iTemp51 * iTemp54;
			fRec36[0] = fSlow11 + 0.999f * fRec36[1];
			float fTemp55 = 1.0f - fRec36[0];
			output0[i0] = FAUSTFLOAT(fTemp24 * fTemp55 + 2.0f * fRec36[0] * (fSlow10 * ftbl0[std::max<int>(0, std::min<int>((iRec35[0] + iTemp52) % iTemp18, 959999))] * std::sin(6.28318f * fTemp53) + fSlow9 * ftbl0[std::max<int>(0, std::min<int>((iRec33[0] + iTemp48) % iTemp18, 959999))] * std::sin(6.28318f * fTemp49) + fSlow8 * ftbl0[std::max<int>(0, std::min<int>((iRec31[0] + iTemp44) % iTemp18, 959999))] * std::sin(6.28318f * fTemp45) + fSlow7 * ftbl0[std::max<int>(0, std::min<int>((iRec29[0] + iTemp40) % iTemp18, 959999))] * std::sin(6.28318f * fTemp41) + fSlow6 * ftbl0[std::max<int>(0, std::min<int>((iRec27[0] + iTemp36) % iTemp18, 959999))] * std::sin(6.28318f * fTemp37) + fSlow5 * ftbl0[std::max<int>(0, std::min<int>((iRec25[0] + iTemp32) % iTemp18, 959999))] * std::sin(6.28318f * fTemp33) + fSlow4 * ftbl0[std::max<int>(0, std::min<int>((iRec23[0] + iTemp28) % iTemp18, 959999))] * std::sin(6.28318f * fTemp29) + fSlow3 * ftbl0[std::max<int>(0, std::min<int>((iRec21[0] + iTemp22) % iTemp18, 959999))] * std::sin(6.28318f * fTemp23)));
			int iTemp56 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec17) + 1.0f));
			iRec37[0] = iVec0[1] * iRec37[1] + iTemp21 * iTemp56;
			int iTemp57 = (iRec19[0] + iRec37[0]) % iTemp0;
			float fTemp58 = float(iTemp57) / fTemp1;
			float fTemp59 = float(input1[i0]);
			ftbl1[iTemp25] = fTemp59;
			int iTemp60 = int(fTemp58);
			iRec38[0] = iRec38[1] * (1 - iTemp60) + iTemp56 * iTemp60;
			int iTemp61 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec15) + 1.0f));
			iRec39[0] = iVec0[1] * iRec39[1] + iTemp21 * iTemp61;
			int iTemp62 = (iRec19[0] + iRec39[0]) % iTemp0;
			float fTemp63 = float(iTemp62) / fTemp1;
			int iTemp64 = int(fTemp63);
			iRec40[0] = iRec40[1] * (1 - iTemp64) + iTemp61 * iTemp64;
			int iTemp65 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec13) + 1.0f));
			iRec41[0] = iVec0[1] * iRec41[1] + iTemp21 * iTemp65;
			int iTemp66 = (iRec19[0] + iRec41[0]) % iTemp0;
			float fTemp67 = float(iTemp66) / fTemp1;
			int iTemp68 = int(fTemp67);
			iRec42[0] = iRec42[1] * (1 - iTemp68) + iTemp65 * iTemp68;
			int iTemp69 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec11) + 1.0f));
			iRec43[0] = iVec0[1] * iRec43[1] + iTemp21 * iTemp69;
			int iTemp70 = (iRec19[0] + iRec43[0]) % iTemp0;
			float fTemp71 = float(iTemp70) / fTemp1;
			int iTemp72 = int(fTemp71);
			iRec44[0] = iRec44[1] * (1 - iTemp72) + iTemp69 * iTemp72;
			int iTemp73 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec9) + 1.0f));
			iRec45[0] = iVec0[1] * iRec45[1] + iTemp21 * iTemp73;
			int iTemp74 = (iRec19[0] + iRec45[0]) % iTemp0;
			float fTemp75 = float(iTemp74) / fTemp1;
			int iTemp76 = int(fTemp75);
			iRec46[0] = iRec46[1] * (1 - iTemp76) + iTemp73 * iTemp76;
			int iTemp77 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec7) + 1.0f));
			iRec47[0] = iVec0[1] * iRec47[1] + iTemp21 * iTemp77;
			int iTemp78 = (iRec19[0] + iRec47[0]) % iTemp0;
			float fTemp79 = float(iTemp78) / fTemp1;
			int iTemp80 = int(fTemp79);
			iRec48[0] = iRec48[1] * (1 - iTemp80) + iTemp77 * iTemp80;
			int iTemp81 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec5) + 1.0f));
			iRec49[0] = iVec0[1] * iRec49[1] + iTemp21 * iTemp81;
			int iTemp82 = (iRec19[0] + iRec49[0]) % iTemp0;
			float fTemp83 = float(iTemp82) / fTemp1;
			int iTemp84 = int(fTemp83);
			iRec50[0] = iRec50[1] * (1 - iTemp84) + iTemp81 * iTemp84;
			int iTemp85 = int(0.5f * fTemp19 * (2.3283064e-10f * float(iRec3) + 1.0f));
			iRec51[0] = iVec0[1] * iRec51[1] + iTemp21 * iTemp85;
			int iTemp86 = (iRec19[0] + iRec51[0]) % iTemp0;
			float fTemp87 = float(iTemp86) / fTemp1;
			int iTemp88 = int(fTemp87);
			iRec52[0] = iRec52[1] * (1 - iTemp88) + iTemp85 * iTemp88;
			output1[i0] = FAUSTFLOAT(fTemp59 * fTemp55 + 2.0f * fRec36[0] * (fSlow19 * ftbl1[std::max<int>(0, std::min<int>((iRec52[0] + iTemp86) % iTemp18, 959999))] * std::sin(6.28318f * fTemp87) + fSlow18 * ftbl1[std::max<int>(0, std::min<int>((iRec50[0] + iTemp82) % iTemp18, 959999))] * std::sin(6.28318f * fTemp83) + fSlow17 * ftbl1[std::max<int>(0, std::min<int>((iRec48[0] + iTemp78) % iTemp18, 959999))] * std::sin(6.28318f * fTemp79) + fSlow16 * ftbl1[std::max<int>(0, std::min<int>((iRec46[0] + iTemp74) % iTemp18, 959999))] * std::sin(6.28318f * fTemp75) + fSlow15 * ftbl1[std::max<int>(0, std::min<int>((iRec44[0] + iTemp70) % iTemp18, 959999))] * std::sin(6.28318f * fTemp71) + fSlow14 * ftbl1[std::max<int>(0, std::min<int>((iRec42[0] + iTemp66) % iTemp18, 959999))] * std::sin(6.28318f * fTemp67) + fSlow13 * ftbl1[std::max<int>(0, std::min<int>((iRec40[0] + iTemp62) % iTemp18, 959999))] * std::sin(6.28318f * fTemp63) + fSlow12 * ftbl1[std::max<int>(0, std::min<int>((iRec38[0] + iTemp57) % iTemp18, 959999))] * std::sin(6.28318f * fTemp58)));
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			iRec2[1] = iRec2[0];
			fRec18[1] = fRec18[0];
			iRec1[1] = iRec1[0];
			iRec19[1] = iRec19[0];
			iRec20[1] = iRec20[0];
			iRec21[1] = iRec21[0];
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
			fRec36[1] = fRec36[0];
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

#endif
