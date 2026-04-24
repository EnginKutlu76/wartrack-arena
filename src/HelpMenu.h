/*
 * HelpMenu.h
 *
 *  Created on: 13 Nis 2026
 *      Author: Engin
 */

#ifndef SRC_HELPMENU_H_
#define SRC_HELPMENU_H_

#include <gBaseCanvas.h>
#include "gApp.h"

class HelpMenu: public gBaseCanvas {
public:

	HelpMenu(gApp* root);
	virtual ~HelpMenu();

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
	static const int TAB_NONE = 0, TAB_GENERAL = 1, TAB_LEVEL = 2, TAB_ITEMS = 3, TAB_CONTROLS = 4;
	static const int languagenum = 3, resolutionnum = 3, windowmodenum = 3, qualitynum = 3, keynum = 7;
	static const int LANG_EN = 1, LANG_TR = 2;
	static const int KEY_NONE = -1, KEY_FORWARD = 0, KEY_BACKWARD = 1, KEY_RIGHT = 2, KEY_LEFT = 3, KEY_RUN = 4, KEY_FIRE = 5, KEY_INTERACT = 6;

	void tabSetup();

	void containerSetup();
	void generalSettingsSetup();
	void levelSettingsSetup();
	void itemsSettingsSetup();
	void controlsSettingsSetup();

	void tabDraw();

	void containerDraw();
	void generalSettingsDraw();
	void levelSettingsDraw();
	void itemsSettingsDraw();
	void controlsSettingsDraw();

	void tabButtonPressed(int x, int y);
	void tabButtonReleased(int x, int y);
	void tabButtonFocus(int x, int y);

	void containerButtonPressed(int x, int y);
	void containerButtonReleased(int x, int y);
	void containerButtonFocus(int x, int y);

	void generalSettingsPressed(int x, int y);
	void generalSettingsReleased(int x, int y);
	void generalSettingsFocus(int x, int y);
	void levelSettingsPressed(int x, int y);
	void levelSettingsReleased(int x, int y);
	void levelSettingsFocus(int x, int y);
	void itemsSettingsPressed(int x, int y);
	void itemsSettingsReleased(int x, int y);
	void itemsSettingsFocus(int x, int y);
	void controlsSettingsPressed(int x, int y);
	void controlsSettingsReleased(int x, int y);
	void controlsSettingsFocus(int x, int y);

	void forwardButtonSetup();
	void forwardButtonDraw();
	void backButtonSetup();
	void backButtonDraw();

	std::string getTabTitle() const;

	//forwar&back buttons
	gRect forwardbutton, backbutton;
	int forwardbuttonx, forwardbuttony, forwardbuttonw, forwardbuttonh;
	int backbuttonx, backbuttony, backbuttonw, backbuttonh;
	gImage arrowleft, arrowright;
	int forwardstate, backstate;

	//tabs
	gRect generaltabbutton, leveltabbutton, itemstabbutton, controlstabbutton;
	std::string generaltabtext, leveltabtext, itemstabtext, controlstabtext;

	int tabfontx, tabfonty, tabfontw, tabfonth;
	int tabx, taby, tabw, tabh;
	gColor tabcolor, pressedcolor, focuscolor, normalcolor;

	int activetab;

	//container
	int containerx, containery, containerw, containerh;
	gColor containercolor;

	//general settings
	std::string generallabeltext;
	int generallabelx, generallabely, generallabelw, generallabelh;
	int genearaldisplayx, generaldisplayy, genaraldisplayw, generaldisplayh;

	//level settings
	std::string levellabeltext, leveldisplaytext[resolutionnum];
	std::string levelonelabeltext, levelonedisplaytext[resolutionnum];
	std::string leveltwolabeltext, leveltwodisplaytext[resolutionnum];
	gImage level_picture[2];
	gRect resolutionprev, resolutionnext;
	int resolutionprevstate, resolutionnextstate;
	int resolution;
	int levelonelabelx, levelonelabely, levelonelabelw, levelonelabelh;
	int leveltwolabelx, leveltwolabely, leveltwolabelw, leveltwolabelh;
	int resolutiondisplayx, resolutiondisplayy, resolutiondisplayw, resolutiondisplayh;
	int resolutionprevx, resolutionprevy, resolutionprevw, resolutionprevh;
	int resolutionnextx, resolutionnexty, resolutionnextw, resolutionnexth;
	//controls settings
	bool ischangingkey;
	int selectedkey;
	int keyboardcontrols[keynum];

	std::string controlslabeltext[keynum], controlsdisplaytext[keynum];
	gRect controlsbutton[keynum];
	int controlsbuttonstate[keynum];
	int controlslabelx[keynum], controlslabely[keynum], controlslabelw[keynum], controlslabelh[keynum];
	int controlsx[keynum], controlsy[keynum], controlsw[keynum], controlsh[keynum];

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

	   //items settings
	std::string itemslabeltext[5];
	int itemslabelx[5], itemslabely[5], itemslabelw[5], itemslabelh[5];

    void returnSetup();
	void returnDraw();

	int returnx, returny, returnw, returnh;
	std::string returntext;
	gRect returnhitbox;
	int returnbuttonstate;

	gImage logo[5];
	int logox[5], logoy[5], logow[5], logoh[5];

	std::vector<std::string> generallabellines;

	//active color
	gImage activepart, inactivepart;
	int activex, activey, activew, activeh;
	int activeposx;

	std::string tabtitle;
	int tabtextx, tabtexty, tabtextw, tabtexth;
};

#endif /* SRC_HELPMENU_H_ */
