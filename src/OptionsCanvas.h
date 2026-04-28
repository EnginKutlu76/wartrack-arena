/*
 * OptionsCanvas.h
 *
 *  Created on: 13 Nis 2026
 *      Author: Engin
 */

#ifndef SRC_OPTIONSCANVAS_H_
#define SRC_OPTIONSCANVAS_H_

#include <gBaseCanvas.h>
#include "gApp.h"

class OptionsCanvas: public gBaseCanvas {
public:
	OptionsCanvas(gApp* root);
	virtual ~OptionsCanvas();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();
	void windowResized(int w, int h);

	void showNotify();
	void hideNotify();
private:
	gApp* root;

	static const int  BUTTON_NONE = 0, BUTTON_PRESSED = 1, BUTTON_CANCELED = -1, BUTTON_PERFORMED = 2, BUTTON_FOCUS = 3;
	static const int TAB_NONE = 0, TAB_GAME = 1, TAB_CONTROLS = 2, TAB_GRAPHICS = 3, TAB_AUDIO = 4, TAB_APPLY = 5, TAB_RESET = 6;
	static const int languagenum = 2, resolutionnum = 3, windowmodenum = 3, qualitynum = 3, keynum = 7;
	static const int LANG_EN = 1, LANG_TR = 2;
	static const int KEY_NONE = -1, KEY_FORWARD = 0, KEY_BACKWARD = 1, KEY_RIGHT = 2, KEY_LEFT = 3, KEY_RUN = 4, KEY_FIRE = 5, KEY_INTERACT = 6;

	//tab funcs
	void tabSetup();
	void tabDraw();
	void tabButtonPressed(int x, int y);
	void tabButtonReleased(int x, int y);
	void tabButtonFocus(int x, int y);

	//container funcs
	void containerSetup();
	void containerDraw();
	void containerButtonPressed(int x, int y);
	void containerButtonReleased(int x, int y);
	void containerButtonFocus(int x, int y);

	//game funcs
	void gameTabButtonSetup();
	void gameTabButtonDraw();
	void gameSettingsSetup();
	void languageSetup();
	void minimapSetup();
	void fpsSetup();
	void vsyncSetup();
	void gameSettingsPressed(int x, int y);
	void gameSettingsReleased(int x, int y);
	void gameSettingsFocus(int x, int y);
	void gameSettingsDraw();
	void languageDraw();
	void minimapDraw();
	void fpsDraw();
	void vsyncDraw();

	//control funcs
	void controlsTabButtonSetup();
	void controlsTabButtonDraw();
	void controlsSettingsSetup();
	void controlButtonsSetup();
	void sensitivitySetup();
	void controlsSettingsPressed(int x, int y);
	void controlsSettingsReleased(int x, int y);
	void controlsSettingsFocus(int x, int y);
	void controlsSettingsDraw();
	void controlButtonsDraw();
	void sensitivityDraw();

	//graphics funcs
	void graphicsTabButtonSetup();
	void graphicsTabButtonDraw();
	void graphicsSettingsSetup();
	void brightnessSetup();
	void resolutionSetup();
	void windowmodeSetup();
	void qualitySetup();
	void graphicsSettingsPressed(int x, int y);
	void graphicsSettingsReleased(int x, int y);
	void graphicsSettingsFocus(int x, int y);
	void graphicsSettingsDraw();
	void brightnessDraw();
	void resolutionDraw();
	void windowmodeDraw();
	void qualityDraw();

	//audio funcs
	void audioTabButtonSetup();
	void audioTabButtonDraw();
	void audioSettingsSetup();
	void musicSetup();
	void fxSetup();
	void musictickSetup();
	void fxtickSetup();
	void audioSettingsPressed(int x, int y);
	void audioSettingsReleased(int x, int y);
	void audioSettingsFocus(int x, int y);
	void audioSettingsDraw();
	void musicDraw();
	void fxDraw();
	void musictickDraw();
	void fxtickDraw();

	//apply&reset funcs
	void applyTabButtonSetup();
	void resetTabButtonSetup();
	void applyTabButtonDraw();
	void resetTabButtonDraw();

	void applyGameSettings();
	void resetGameSettings();

	//return funcs
	void returnSetup();
	void returnDraw();

	//tabs
	gRect gametabbutton, controlstabbutton, graphicstabbutton, audiotabbutton, applytabbutton, resettabbutton;
	std::string gametabtext, controlstabtext, graphicstabtext, audiotabtext, applytabtext, resettabtext;
	int gametabbuttonstate, controlstabbuttonstate, graphicstabbuttonstate, audiotabbuttonstate, applytabbuttonstate, resettabbuttonstate;

	int gametabbuttonx, gametabbuttony, gametabbuttonw, gametabbuttonh;
	int controlstabbuttonx, controlstabbuttony, controlstabbuttonw, controlstabbuttonh;
	int graphicstabbuttonx, graphicstabbuttony, graphicstabbuttonw, graphicstabbuttonh;
	int audiotabbuttonx, audiotabbuttony, audiotabbuttonw, audiotabbuttonh;
	int applytabbuttonx, applytabbuttony, applytabbuttonw, applytabbuttonh;
	int resettabbuttonx, resettabbuttony, resettabbuttonw, resettabbuttonh;
	int tabfontx, tabfonty, tabfontw, tabfonth;
	int tabx, taby, tabw, tabh;

	gColor tabcolor, pressedcolor, focuscolor, normalcolor;

	int activetab;

	//container
	int containerx, containery, containerw, containerh;
	gColor containercolor;

	//game settings
	std::string languagelabeltext;
	std::string languages[2];
	gImage langbackbutton, langforwardbutton;
	gRect langbackbuttonhitbox, langforwardbuttonhitbox;
	int languagelabelx, languagelabely, languagelabelw, languagelabelh;
	int languagesx, languagesw, languagesh;
	int langbackbuttonx, langbackbuttony, langbackbuttonw, langbackbuttonh, langforwardbuttonx;
	int langbackstate, langfwstate;
	int selectedlanguage;

	gImage muncheck, mcheck;
	gRect mapbuttonhitbox;
	std::string minimaptext;
	int maptextx, maptexty, maptextw, maptexth;
	int muncheckx, munchecky, muncheckw, muncheckh;
	int mcheckw, mcheckh;
	int maptickstate;
	bool isminimapenabled;

	gImage fpsuncheck, fpscheck;
	gRect fpsbuttonhitbox;
	std::string fpstext;
	int fpstextx, fpstexty, fpstextw, fpstexth;
	int fpsuncheckx, fpsunchecky, fpsuncheckw, fpsuncheckh;
	int fpscheckw, fpscheckh;
	int fpstickstate;
	bool isfpsenabled;

	gImage vsyncuncheck, vsynccheck;
	gRect vsyncbuttonhitbox;
	std::string vsynctext;
	int vsynctextx, vsynctexty, vsynctextw, vsynctexth;
	int vsyncuncheckx, vsyncunchecky, vsyncuncheckw, vsyncuncheckh;
	int vsynccheckw, vsynccheckh;
	int vsynctickstate;
	bool isvsyncenabled;

	//controls settings
	bool ischangingkey;
	int selectedkey;
	int keyboardcontrols[keynum];

	gRect controlbutton[keynum];
	std::string controllabeltext[keynum], controldisplaytext[keynum];
	int controlbuttonstate[keynum];
	int controllabelx[keynum], controllabely[keynum], controllabelw[keynum], controllabelh[keynum];
	int controlx[keynum], controly[keynum], controlw[keynum], controlh[keynum];

	gRect backwardbutton;
	std::string backwardlabeltext, backwarddisplaytext;
	int backwardbuttonstate;
	int backwardkey;
	int backwardlabelx, backwardlabely, backwardlabelw, backwardlabelh;
	int backwardx, backwardy, backwardw, backwardh;

	gRect rightbutton;
	std::string rightlabeltext, rightdisplaytext;
	int rightbuttonstate;
	int rightkey;
	int rightlabelx, rightlabely, rightlabelw, rightlabelh;
	int rightx, righty, rightw, righth;

	gRect leftbutton;
	std::string leftlabeltext, leftdisplaytext;
	int leftbuttonstate;
	int leftkey;
	int leftlabelx, leftlabely, leftlabelw, leftlabelh;
	int leftx, lefty, leftw, lefth;

	gRect runbutton;
	std::string runlabeltext, rundisplaytext;
	int runbuttonstate;
	int runkey;
	int runlabelx, runlabely, runlabelw, runlabelh;
	int runx, runy, runw, runh;

	gRect firebutton;
	std::string firelabeltext, firedisplaytext;
	int firebuttonstate;
	int firekey;
	int firelabelx, firelabely, firelabelw, firelabelh;
	int firex, firey, firew, fireh;

	gRect interactbutton;
    std::string interactlabeltext, interactdisplaytext;
    int interactbuttonstate;
	int interactkey;
	int interactlabelx, interactlabely, interactlabelw, interactlabelh;
	int interactx, interacty, interactw, interacth;

	gImage sensbackbutton, sensforwardbutton;
	gRect sensbackbuttonhitbox, sensforwardbuttonhitbox;
	std::string senslabeltext, sensnumtext;
	int sensitivity;
	int senslabelx, senslabely, senslabelw, senslabelh;
	int sensx, sensw, sensh	;
	int sensbackbuttonx, sensbackbuttony, sensbackbuttonw, sensbackbuttonh, sensforwardbuttonx;
	int sensbackstate, sensfwstate;

	//graphics settings
	gImage brightbackbutton, brightforwardbutton;
	gRect brightbackbuttonhitbox, brightforwardbuttonhitbox;
	std::string brightlabeltext, brightnumtext;
	int brightness;
	int brightlabelx, brightlabely, brightlabelw, brightlabelh;
	int brightx, brightw, brighth	;
	int brightbackbuttonx, brightbackbuttony, brightbackbuttonw, brightbackbuttonh, brightforwardbuttonx;
	int brightbackstate, brightfwstate;

	gImage quabackbutton, quaforwardbutton;
	gRect quabackbuttonhitbox, quaforwardbuttonhitbox;
	std::string qualitylabeltext;
	std::string qualities[3];
	int qualabelx, qualabely, qualabelw, qualabelh;
	int qualitiesx, qualitiesw, qualitiesh;
	int quabackbuttonx, quabackbuttony, quabackbuttonw, quabackbuttonh, quaforwardbuttonx;
	int quabackstate, quafwstate;
	int selectedquality;

	gImage winbackbutton, winforwardbutton;
	gRect winbackbuttonhitbox, winforwardbuttonhitbox;
	std::string windowmodelabeltext;
	std::string windowmodes[3];
	int winlabelx, winlabely, winlabelw, winlabelh;
	int windowmodesx, windowmodesw, windowmodesh;
	int winbackbuttonx, winbackbuttony, winbackbuttonw, winbackbuttonh, winforwardbuttonx;
	int winbackstate, winfwstate;
	int selectedwindowmode;

	gImage resbackbutton, resforwardbutton;
	gRect resbackbuttonhitbox, resforwardbuttonhitbox;
	std::string resolutionlabeltext;
	std::string resolutions[3];
	int reslabelx, reslabely, reslabelw, reslabelh;
	int resolutionsx, resolutionsw, resolutionsh;
	int resbackbuttonx, resbackbuttony, resbackbuttonw, resbackbuttonh, resforwardbuttonx;
	int resbackstate, resfwstate;
	int selectedresolution;

	//audio settings
	gImage musicbackbutton, musicforwardbutton;
	gRect musicbackbuttonhitbox, musicforwardbuttonhitbox;
	std::string musiclabeltext, musicnumtext;
	int musicvalue;
	int musiclabelx, musiclabely, musiclabelw, musiclabelh;
	int musicx, musicw, musich;
	int musicbackbuttonx, musicbackbuttony, musicbackbuttonw, musicbackbuttonh, musicforwardbuttonx;
	int musicbackstate, musicfwstate;

	gImage fxbackbutton, fxforwardbutton;
	gRect fxbackbuttonhitbox, fxforwardbuttonhitbox;
	std::string fxlabeltext, fxnumtext;
	int effectvalue;
	int fxlabelx, fxlabely, fxlabelw, fxlabelh;
	int fxx, fxw, fxh;
	int fxbackbuttonx, fxbackbuttony, fxbackbuttonw, fxbackbuttonh, fxforwardbuttonx;
	int fxbackstate, fxfwstate;

	gImage musicuncheck, musiccheck;
	gRect musicbuttonhitbox;
	std::string musictext;
	int musictextx, musictexty, musictextw, musictexth;
	int musicuncheckx, musicunchecky, musicuncheckw, musicuncheckh;
	int musiccheckw, musiccheckh;
	int musictickstate;
	bool ismusicenabled;

	gImage fxuncheck, fxcheck;
	gRect fxbuttonhitbox;
	std::string fxtext;
	int fxtextx, fxtexty, fxtextw, fxtexth;
	int fxuncheckx, fxunchecky, fxuncheckw, fxuncheckh;
	int fxcheckw, fxcheckh;
	int fxtickstate;
	bool isfxenabled;

	//return
	int returnx, returny, returnw, returnh;
	std::string returntext;
	gRect returnhitbox;
	int returnbuttonstate;

	//titles
	std::string tabtitle;
	int tabtextx, tabtexty, tabtextw, tabtexth;
	std::string sectiontitle;
	int titlex, titley;
};

#endif /* SRC_OPTIONSCANVAS_H_ */
