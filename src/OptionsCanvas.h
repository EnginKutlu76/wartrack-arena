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

	void tabSetup();
	void gameTabButtonSetup();
	void controlsTabButtonSetup();
	void graphicsTabButtonSetup();
	void audioTabButtonSetup();
	void applyTabButtonSetup();
	void resetTabButtonSetup();

	void containerSetup();
	void gameSettingsSetup();
	void controlsSettingsSetup();
	void graphicsSettingsSetup();
	void audioSettingsSetup();

	void tabDraw();
	void gameTabButtonDraw();
	void controlsTabButtonDraw();
	void graphicsTabButtonDraw();
	void audioTabButtonDraw();
	void applyTabButtonDraw();
	void resetTabButtonDraw();

	void containerDraw();
	void gameSettingsDraw();
	void controlsSettingsDraw();
	void graphicsSettingsDraw();
	void audioSettingsDraw();

	void tabButtonPressed(int x, int y);
	void tabButtonReleased(int x, int y);
	void tabButtonFocus(int x, int y);

	void containerButtonPressed(int x, int y);
	void containerButtonReleased(int x, int y);
	void containerButtonFocus(int x, int y);

	void gameSettingsPressed(int x, int y);
	void gameSettingsReleased(int x, int y);
	void gameSettingsFocus(int x, int y);
	void controlsSettingsPressed(int x, int y);
	void controlsSettingsReleased(int x, int y);
	void controlsSettingsFocus(int x, int y);
	void graphicsSettingsPressed(int x, int y);
	void graphicsSettingsReleased(int x, int y);
	void graphicsSettingsFocus(int x, int y);
	void audioSettingsPressed(int x, int y);
	void audioSettingsReleased(int x, int y);
	void audioSettingsFocus(int x, int y);

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
	int languagelabelx, languagelabely, languagelabelw, languagelabelh;
	int languagesx, languagesw, languagesh;

	//controls settings
	bool ischangingkey;
	int selectedkey;
	int keyboardcontrols[keynum];

	std::string controllabeltext[keynum], controldisplaytext[keynum];
	gRect controlbutton[keynum];
	int controlbuttonstate[keynum];
	int controllabelx[keynum], controllabely[keynum], controllabelw[keynum], controllabelh[keynum];
	int controlx[keynum], controly[keynum], controlw[keynum], controlh[keynum];

	std::string backwardlabeltext, backwarddisplaytext;
	gRect backwardbutton;
	int backwardbuttonstate;
	int backwardkey;
	int backwardlabelx, backwardlabely, backwardlabelw, backwardlabelh;
	int backwardx, backwardy, backwardw, backwardh;

	std::string rightlabeltext, rightdisplaytext;
	gRect rightbutton;
	int rightbuttonstate;
	int rightkey;
	int rightlabelx, rightlabely, rightlabelw, rightlabelh;
	int rightx, righty, rightw, righth;

	std::string leftlabeltext, leftdisplaytext;
	gRect leftbutton;
	int leftbuttonstate;
	int leftkey;
	int leftlabelx, leftlabely, leftlabelw, leftlabelh;
	int leftx, lefty, leftw, lefth;

	std::string runlabeltext, rundisplaytext;
	gRect runbutton;
	int runbuttonstate;
	int runkey;
	int runlabelx, runlabely, runlabelw, runlabelh;
	int runx, runy, runw, runh;

	std::string firelabeltext, firedisplaytext;
	gRect firebutton;
	int firebuttonstate;
	int firekey;
	int firelabelx, firelabely, firelabelw, firelabelh;
	int firex, firey, firew, fireh;

    std::string interactlabeltext, interactdisplaytext;
	gRect interactbutton;
    int interactbuttonstate;
	int interactkey;
	int interactlabelx, interactlabely, interactlabelw, interactlabelh;
	int interactx, interacty, interactw, interacth;

	int sensitivity;
	std::string senslabeltext, sensnumtext;
	int senslabelx, senslabely, senslabelw, senslabelh;
	int sensx, sensw, sensh	;
	gImage sensbackbutton, sensforwardbutton;
	int sensbackbuttonx, sensbackbuttony, sensbackbuttonw, sensbackbuttonh, sensforwardbuttonx;
	gRect sensbackbuttonhitbox, sensforwardbuttonhitbox;
	int sensbackstate, sensfwstate;

	   //items settings
	std::string graphicslabeltext[5];
	int graphicslabelx[5], graphicslabely[5], graphicslabelw[5], graphicslabelh[5];

    void returnSetup();
	void returnDraw();

	int returnx, returny, returnw, returnh;
	std::string returntext;
	gRect returnhitbox;
	int returnbuttonstate;

	gImage logo[5];
	int logox[5], logoy[5], logow[5], logoh[5];

	std::vector<std::string> generallabellines;

	std::string tabtitle;
	int tabtextx, tabtexty, tabtextw, tabtexth;

	std::string sectiontitle;
	int titlex, titley;

	//game section
	gImage langbackbutton, langforwardbutton;
	int langbackbuttonx, langbackbuttony, langbackbuttonw, langbackbuttonh, langforwardbuttonx;
	gRect langbackbuttonhitbox, langforwardbuttonhitbox;
	int langbackstate, langfwstate;
	int selectedlanguage;

	std::string minimaptext;
	int maptextx, maptexty, maptextw, maptexth;
	gImage muncheck, mcheck;
	int muncheckx, munchecky, muncheckw, muncheckh;
	int mcheckw, mcheckh;
	gRect mapbuttonhitbox;
	int maptickstate;
	bool isminimapenabled;

	std::string fpstext;
	int fpstextx, fpstexty, fpstextw, fpstexth;
	gImage fpsuncheck, fpscheck;
	int fpsuncheckx, fpsunchecky, fpsuncheckw, fpsuncheckh;
	int fpscheckw, fpscheckh;
	gRect fpsbuttonhitbox;
	int fpstickstate;
	bool isfpsenabled;
};

#endif /* SRC_OPTIONSCANVAS_H_ */
