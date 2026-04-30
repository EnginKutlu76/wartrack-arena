/*
 * HelpMenu.cpp
 *
 *  Created on: 13 Nis 2026
 *      Author: Engin Kutlu
 */


#include "OptionsCanvas.h"
#include "gCanvas.h"
#include "MainMenu.h"

OptionsCanvas::OptionsCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

OptionsCanvas::~OptionsCanvas() {
}

void OptionsCanvas::setup() {
	containerSetup();
	tabSetup();
	activetab = TAB_GAME;
	sectiontitle = "OPTIONS";
	titlex = (containerw + gametabbuttonw) / 2;
	titley = tabh;
}

void OptionsCanvas::update() {
}

void OptionsCanvas::draw() {
	root->drawMenuBackground(getWidth(), getHeight());
	containerDraw();
	tabDraw();
	setColor(255, 255, 255);
	root->menutitlefont.drawText(sectiontitle, titlex, titley);
	setColor(normalcolor);
}

void OptionsCanvas::keyPressed(int key) {
	//	gLogi("OptionsCanvas") << "keyPressed:" << key;
}

void OptionsCanvas::keyReleased(int key) {
	//	gLogi("OptionsCanvas") << "keyReleased:" << key;
	if(key == G_KEY_ESC) {
		root->setCurrentCanvas(new mainMenu(root));
	}
	if(ischangingkey) {
		keyboardcontrols[selectedkey] = key;
		ischangingkey = false;
		controldisplaytext[selectedkey] = gCodepointToStr(key);
	}
}

void OptionsCanvas::charPressed(unsigned int codepoint) {
	//	gLogi("HelpMenu") << "charPressed:" << gCodepointToStr(codepoint);
}

void OptionsCanvas::mouseMoved(int x, int y) {
	//	gLogi("HelpMenu") << "mouseMoved" << ", x:" << x << ", y:" << y;
	tabButtonFocus(x, y);
	containerButtonFocus(x, y);
}

void OptionsCanvas::mouseDragged(int x, int y, int button) {
	//	gLogi("OptionsCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void OptionsCanvas::mousePressed(int x, int y, int button) {
	//	gLogi("OptionsCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	tabButtonPressed(x, y);
	containerButtonPressed(x, y);
}

void OptionsCanvas::mouseReleased(int x, int y, int button) {
	//	gLogi("OptionsCanvas") << "mouseReleased" << ", button:" << button;
	tabButtonReleased(x, y);
	containerButtonReleased(x, y);
}

void OptionsCanvas::mouseScrolled(int x, int y) {
	//	gLogi("OptionsCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void OptionsCanvas::mouseEntered() {

}

void OptionsCanvas::mouseExited() {

}

void OptionsCanvas::windowResized(int w, int h) {

}

void OptionsCanvas::showNotify() {

}

void OptionsCanvas::hideNotify() {

}

void OptionsCanvas::tabSetup() {
	tabw = getWidth() / 2;
	tabh = getHeight() / 10;
	tabx = (getWidth() - tabw) / 2;
	taby = tabh;
	tabcolor.set(54, 126, 127);
	normalcolor.set(45, 50, 70);
	pressedcolor.set(65, 70, 90);
	focuscolor.set(55, 60, 80);
	gameTabButtonSetup();
	controlsTabButtonSetup();
	graphicsTabButtonSetup();
	audioTabButtonSetup();
	applyTabButtonSetup();
	resetTabButtonSetup();
	returnSetup();

	activetab = TAB_GAME;
}

void OptionsCanvas::tabDraw() {
	setColor(tabcolor);
	//gDrawRectangle(tabx, taby, tabw, tabh, true);
	setColor(normalcolor);
	gameTabButtonDraw();
	controlsTabButtonDraw();
	graphicsTabButtonDraw();
	audioTabButtonDraw();
	applyTabButtonDraw();
	resetTabButtonDraw();
	returnDraw();
}

void OptionsCanvas::tabButtonPressed(int x, int y) {
	if(returnhitbox.contains(x, y)) {
		returnbuttonstate = BUTTON_PRESSED;
		returny += 2;
	}

	if(gametabbutton.contains(x, y)) {
		gametabbuttonstate = BUTTON_PRESSED;
	}

	if(controlstabbutton.contains(x, y)) {
		controlstabbuttonstate = BUTTON_PRESSED;
	}

	if(graphicstabbutton.contains(x, y)) {
		graphicstabbuttonstate = BUTTON_PRESSED;
	}

	if(audiotabbutton.contains(x, y)) {
		audiotabbuttonstate = BUTTON_PRESSED;
	}

	if(applytabbutton.contains(x, y)) {
		applytabbuttonstate = BUTTON_PRESSED;
	}

	if(resettabbutton.contains(x, y)) {
		resettabbuttonstate = BUTTON_PRESSED;
	}
}

void OptionsCanvas::tabButtonReleased(int x, int y) {
	if(gametabbutton.contains(x, y) && gametabbuttonstate == BUTTON_PRESSED) {
		gametabbuttonstate = BUTTON_PERFORMED;
		activetab = TAB_GAME;
	}

	else if(controlstabbutton.contains(x, y) && controlstabbuttonstate == BUTTON_PRESSED) {
		controlstabbuttonstate = BUTTON_PERFORMED;
		activetab = TAB_CONTROLS;
	}

	else if(graphicstabbutton.contains(x, y) && graphicstabbuttonstate == BUTTON_PRESSED) {
		graphicstabbuttonstate = BUTTON_PERFORMED;
		activetab = TAB_GRAPHICS;
	}

	else if(audiotabbutton.contains(x, y) && audiotabbuttonstate == BUTTON_PRESSED) {
		audiotabbuttonstate = BUTTON_PERFORMED;
		activetab = TAB_AUDIO;
	}

	else if(applytabbutton.contains(x, y) && applytabbuttonstate == BUTTON_PRESSED) {
		applytabbuttonstate = BUTTON_PERFORMED;
		if(activetab == TAB_GAME) applyGameSettings();
		if(activetab == TAB_CONTROLS) applyControlsSettings();
		if(activetab == TAB_GRAPHICS) applyGraphicsSettings();
		if(activetab == TAB_AUDIO) applyAudioSettings();
	}

	else if(resettabbutton.contains(x, y) && resettabbuttonstate == BUTTON_PRESSED) {
		resettabbuttonstate = BUTTON_PERFORMED;
		if(activetab == TAB_GAME) resetGameSettings();
		if(activetab == TAB_CONTROLS) resetControlsSettings();
		if(activetab == TAB_GRAPHICS) resetGraphicsSettings();
		if(activetab == TAB_AUDIO) resetAudioSettings();
	}

	else if(returnhitbox.contains(x, y) && returnbuttonstate == BUTTON_PRESSED) {
		returnbuttonstate = BUTTON_PERFORMED;
		root->setCurrentCanvas(new mainMenu(root));
	}

	else {
		gametabbuttonstate = BUTTON_CANCELED;
		controlstabbuttonstate = BUTTON_CANCELED;
		graphicstabbuttonstate = BUTTON_CANCELED;
		audiotabbuttonstate = BUTTON_CANCELED;
		applytabbuttonstate = BUTTON_CANCELED;
		resettabbuttonstate = BUTTON_CANCELED;
		returnbuttonstate= BUTTON_CANCELED;
	}
}

void OptionsCanvas::tabButtonFocus(int x, int y) {
	if(gametabbuttonstate != BUTTON_PRESSED) {
		if(gametabbutton.contains(x, y)) {
			gametabbuttonstate = BUTTON_FOCUS;
		}
		else {
			gametabbuttonstate = BUTTON_NONE;
		}
	}

	if(controlstabbuttonstate != BUTTON_PRESSED) {
		if(controlstabbutton.contains(x, y)) {
			controlstabbuttonstate = BUTTON_FOCUS;
		}
		else {
			controlstabbuttonstate = BUTTON_NONE;
		}
	}

	if(graphicstabbuttonstate != BUTTON_PRESSED) {
		if(graphicstabbutton.contains(x, y)) {
			graphicstabbuttonstate = BUTTON_FOCUS;
		}
		else {
			graphicstabbuttonstate = BUTTON_NONE;
		}
	}

	if(audiotabbuttonstate != BUTTON_PRESSED) {
		if(audiotabbutton.contains(x, y)) {
			audiotabbuttonstate = BUTTON_FOCUS;
		}
		else {
			audiotabbuttonstate = BUTTON_NONE;
		}
	}

	if(applytabbuttonstate != BUTTON_PRESSED) {
		if(applytabbutton.contains(x, y)) {
			applytabbuttonstate = BUTTON_FOCUS;
		}
		else {
			applytabbuttonstate = BUTTON_NONE;
		}
	}

	if(resettabbuttonstate != BUTTON_PRESSED) {
		if(resettabbutton.contains(x, y)) {
			resettabbuttonstate = BUTTON_FOCUS;
		}
		else {
			resettabbuttonstate = BUTTON_NONE;
		}
	}

	if(returnbuttonstate != BUTTON_PRESSED) {
		if(returnhitbox.contains(x, y)) {
			returnbuttonstate = BUTTON_FOCUS;
		}
		else {
			returnbuttonstate = BUTTON_NONE;
		}
	}
}

void OptionsCanvas::containerSetup() {
	int width = getWidth() / 2;
	int height = getHeight() / 10;
	containerw = width * 1.5;
	containerh = height * 7;
	containerx = ((getWidth() - containerw) / 2) + (width / 8);
	containery = (getHeight() - containerh) / 2;
	containercolor.set(255, 255, 255);
	gameSettingsSetup();
	controlsSettingsSetup();
	graphicsSettingsSetup();
	audioSettingsSetup();
}

void OptionsCanvas::gameSettingsSetup() {
	languageSetup();
	minimapSetup();
	fpsSetup();
	vsyncSetup();
}

void OptionsCanvas::controlsSettingsSetup() {
	controlButtonsSetup();
	sensitivitySetup();
}

void OptionsCanvas::graphicsSettingsSetup() {
	brightnessSetup();
	qualitySetup();
	windowmodeSetup();
	resolutionSetup();
}

void OptionsCanvas::audioSettingsSetup() {
	musicSetup();
	fxSetup();
	musictickSetup();
	fxtickSetup();
}


void OptionsCanvas::containerDraw() {
	setColor(containercolor);
	gDrawRectangle(containerx, containery, containerw, containerh, true);
	if(activetab == TAB_GAME) gameSettingsDraw();
	else if(activetab == TAB_CONTROLS) controlsSettingsDraw();
	else if(activetab == TAB_GRAPHICS) graphicsSettingsDraw();
	else if(activetab == TAB_AUDIO) audioSettingsDraw();
	setColor(255, 255, 255);
}

void OptionsCanvas::gameSettingsDraw() {
	languageDraw();
	minimapDraw();
	fpsDraw();
	vsyncDraw();
}

void OptionsCanvas::controlsSettingsDraw() {
	controlButtonsDraw();
	sensitivityDraw();
}


void OptionsCanvas::graphicsSettingsDraw() {
	brightnessDraw();
	qualityDraw();
	windowmodeDraw();
	resolutionDraw();
}

void OptionsCanvas::audioSettingsDraw() {
	musicDraw();
	fxDraw();
	musictickDraw();
	fxtickDraw();
}

void OptionsCanvas::containerButtonPressed(int x, int y) {
	if(activetab == TAB_GAME) {
		gameSettingsPressed(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		controlsSettingsPressed(x, y);
	}
	else if(activetab == TAB_GRAPHICS) {
		graphicsSettingsPressed(x, y);
	}
	else if(activetab == TAB_AUDIO) {
		audioSettingsPressed(x, y);
	}
}

void OptionsCanvas::containerButtonReleased(int x, int y) {
	if(activetab == TAB_GAME) {
		gameSettingsReleased(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		controlsSettingsReleased(x, y);
	}
	else if(activetab == TAB_GRAPHICS) {
		graphicsSettingsReleased(x, y);
	}
	else if(activetab == TAB_AUDIO) {
		audioSettingsReleased(x, y);
	}
}

void OptionsCanvas::containerButtonFocus(int x, int y) {
	if(activetab == TAB_GAME) {
		gameSettingsFocus(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		controlsSettingsFocus(x, y);
	}
	else if(activetab == TAB_GRAPHICS) {
		graphicsSettingsFocus(x, y);
	}
	else if(activetab == TAB_AUDIO) {
		audioSettingsFocus(x, y);
	}
}

void OptionsCanvas::gameSettingsPressed(int x, int y) {
	if(langbackbuttonhitbox.contains(x, y)) {
		langbackstate = BUTTON_PRESSED;
	}

	if(langforwardbuttonhitbox.contains(x, y)) {
		langfwstate = BUTTON_PRESSED;
	}

	if(mapbuttonhitbox.contains(x, y)) {
		maptickstate = BUTTON_PRESSED;
	}

	if(fpsbuttonhitbox.contains(x, y)) {
		fpstickstate = BUTTON_PRESSED;
	}

	if(vsyncbuttonhitbox.contains(x, y)) {
		vsynctickstate = BUTTON_PRESSED;
	}
}

void OptionsCanvas::gameSettingsReleased(int x, int y) {
	if(langbackbuttonhitbox.contains(x, y) && langbackstate == BUTTON_PRESSED) {
		langbackstate = BUTTON_PERFORMED;
		selectedlanguage++;
		if(selectedlanguage >= languagenum) selectedlanguage = 0;
	}

	else if(langforwardbuttonhitbox.contains(x, y) && langfwstate == BUTTON_PRESSED) {
		langfwstate = BUTTON_PERFORMED;
		selectedlanguage++;
		if(selectedlanguage >= languagenum) selectedlanguage = 0;
	}

	else if(mapbuttonhitbox.contains(x, y) && maptickstate == BUTTON_PRESSED) {
	    maptickstate = BUTTON_PERFORMED;
	    isminimapenabled = !isminimapenabled;
	}

	else if(fpsbuttonhitbox.contains(x, y) && fpstickstate == BUTTON_PRESSED) {
	    fpstickstate = BUTTON_PERFORMED;
	    isfpsenabled = !isfpsenabled;
	}

	else if(vsyncbuttonhitbox.contains(x, y) && vsynctickstate == BUTTON_PRESSED) {
		vsynctickstate = BUTTON_PERFORMED;
	    isvsyncenabled = !isvsyncenabled;
	}

	else {
		langbackstate = BUTTON_CANCELED;
		langfwstate = BUTTON_CANCELED;
		maptickstate = BUTTON_CANCELED;
		fpstickstate = BUTTON_CANCELED;
		vsynctickstate = BUTTON_CANCELED;
	}

}

void OptionsCanvas::gameSettingsFocus(int x, int y) {
	if(langbackstate != BUTTON_PRESSED) {
		if(langbackbuttonhitbox.contains(x, y)) {
			langbackstate = BUTTON_FOCUS;
		}

		else {
			langbackstate = BUTTON_NONE;
		}
	}

	if(langfwstate != BUTTON_PRESSED) {
		if(langforwardbuttonhitbox.contains(x, y)) {
			langfwstate = BUTTON_FOCUS;
		}

		else {
			langfwstate = BUTTON_NONE;
		}
	}

	if(maptickstate != BUTTON_PRESSED) {
		if(mapbuttonhitbox.contains(x, y)) {
			maptickstate = BUTTON_FOCUS;
		}

		else {
			maptickstate = BUTTON_NONE;
		}
	}

	if(fpstickstate != BUTTON_PRESSED) {
		if(fpsbuttonhitbox.contains(x, y)) {
			fpstickstate = BUTTON_FOCUS;
		}

		else {
			fpstickstate = BUTTON_NONE;
		}
	}

	if(vsynctickstate != BUTTON_PRESSED) {
		if(vsyncbuttonhitbox.contains(x, y)) {
			vsynctickstate = BUTTON_FOCUS;
		}

		else {
			vsynctickstate = BUTTON_NONE;
		}
	}
}

void OptionsCanvas::controlsSettingsPressed(int x, int y) {
	if(controlsbutton[KEY_FORWARD].contains(x, y)) {
		controlsbuttonstate[KEY_FORWARD] = BUTTON_PRESSED;
	}

	if(controlsbutton[KEY_BACKWARD].contains(x, y)) {
		controlsbuttonstate[KEY_BACKWARD] = BUTTON_PRESSED;
	}

	if(controlsbutton[KEY_RIGHT].contains(x, y)) {
		controlsbuttonstate[KEY_RIGHT] = BUTTON_PRESSED;
	}

	if(controlsbutton[KEY_LEFT].contains(x, y)) {
		controlsbuttonstate[KEY_LEFT] = BUTTON_PRESSED;
	}

	if(controlsbutton[KEY_RUN].contains(x, y)) {
		controlsbuttonstate[KEY_RUN] = BUTTON_PRESSED;
	}

	if(controlsbutton[KEY_FIRE].contains(x, y)) {
		controlsbuttonstate[KEY_FIRE] = BUTTON_PRESSED;
	}

	if(controlsbutton[KEY_INTERACT].contains(x, y)) {
		controlsbuttonstate[KEY_INTERACT] = BUTTON_PRESSED;
	}

	if(sensbackstate != BUTTON_PRESSED) {
		if(sensbackbuttonhitbox.contains(x, y)) {
			sensbackstate = BUTTON_PRESSED;
		}
		else {
			sensbackstate = BUTTON_NONE;
		}
	}

	if(sensfwstate != BUTTON_PRESSED) {
		if(sensforwardbuttonhitbox.contains(x, y)) {
			sensfwstate = BUTTON_PRESSED;
		}
		else {
			sensfwstate = BUTTON_NONE;
		}
	}
}

void OptionsCanvas::controlsSettingsReleased(int x, int y) {
	if(controlsbutton[KEY_FORWARD].contains(x, y) && controlsbuttonstate[KEY_FORWARD] == BUTTON_PRESSED) {
		controlsbuttonstate[KEY_FORWARD] = BUTTON_PERFORMED;
		selectedkey = KEY_FORWARD;
		ischangingkey = true;

	}

	else if(controlsbutton[KEY_BACKWARD].contains(x, y) && controlsbuttonstate[KEY_BACKWARD] == BUTTON_PRESSED) {
		controlsbuttonstate[KEY_BACKWARD] = BUTTON_PERFORMED;
		selectedkey = KEY_BACKWARD;
		ischangingkey = true;
	}

	else if(controlsbutton[KEY_RIGHT].contains(x, y) && controlsbuttonstate[KEY_RIGHT] == BUTTON_PRESSED) {
		controlsbuttonstate[KEY_RIGHT] = BUTTON_PERFORMED;
		selectedkey = KEY_RIGHT;
		ischangingkey = true;
	}

	else if(controlsbutton[KEY_LEFT].contains(x, y) && controlsbuttonstate[KEY_LEFT] == BUTTON_PRESSED) {
		controlsbuttonstate[KEY_LEFT] = BUTTON_PERFORMED;
		selectedkey = KEY_LEFT;
		ischangingkey = true;
	}

	else if(controlsbutton[KEY_RUN].contains(x, y) && controlsbuttonstate[KEY_RUN] == BUTTON_PRESSED) {
		controlsbuttonstate[KEY_RUN] = BUTTON_PERFORMED;
		selectedkey = KEY_RUN;
		ischangingkey = true;
	}

	else if(controlsbutton[KEY_FIRE].contains(x, y) && controlsbuttonstate[KEY_FIRE] == BUTTON_PRESSED) {
		controlsbuttonstate[KEY_FIRE] = BUTTON_PERFORMED;
		selectedkey = KEY_FIRE;
		ischangingkey = true;
	}

	else if(controlsbutton[KEY_INTERACT].contains(x, y) && controlsbuttonstate[KEY_INTERACT] == BUTTON_PRESSED) {
		controlsbuttonstate[KEY_INTERACT] = BUTTON_PERFORMED;
		selectedkey = KEY_INTERACT;
		ischangingkey = true;
	}

	else if(sensbackbuttonhitbox.contains(x, y) && sensbackstate == BUTTON_PRESSED) {
		sensbackstate = BUTTON_PERFORMED;
		if(sensitivity >= 5) sensitivity -= 5;
		sensnumtext = gToStr(sensitivity);
	}
	else if(sensforwardbuttonhitbox.contains(x, y) && sensfwstate == BUTTON_PRESSED) {
		sensfwstate = BUTTON_PERFORMED;
		if(sensitivity < 100) sensitivity += 5;
		sensnumtext = gToStr(sensitivity);
	}

	else {
		controlsbuttonstate[KEY_FORWARD] = BUTTON_CANCELED;
		controlsbuttonstate[KEY_BACKWARD] = BUTTON_CANCELED;
		controlsbuttonstate[KEY_RIGHT] = BUTTON_CANCELED;
		controlsbuttonstate[KEY_LEFT] = BUTTON_CANCELED;
		controlsbuttonstate[KEY_RUN] = BUTTON_CANCELED;
		controlsbuttonstate[KEY_FIRE] = BUTTON_CANCELED;
		controlsbuttonstate[KEY_INTERACT] = BUTTON_CANCELED;
		sensbackstate = BUTTON_CANCELED;
		sensfwstate = BUTTON_CANCELED;
	}
}

void OptionsCanvas::controlsSettingsFocus(int x, int y) {
	if(controlsbuttonstate[KEY_FORWARD] != BUTTON_PRESSED) {
		if(controlsbutton[KEY_FORWARD].contains(x, y)) {
			controlsbuttonstate[KEY_FORWARD] = BUTTON_FOCUS;
		}

		else {
			controlsbuttonstate[KEY_FORWARD] = BUTTON_NONE;
		}
	}

	if(controlsbuttonstate[KEY_BACKWARD] != BUTTON_PRESSED) {
		if(controlsbutton[KEY_BACKWARD].contains(x, y)) {
			controlsbuttonstate[KEY_BACKWARD] = BUTTON_FOCUS;
		}

		else {
			controlsbuttonstate[KEY_BACKWARD] = BUTTON_NONE;
		}
	}

	if(controlsbuttonstate[KEY_RIGHT] != BUTTON_PRESSED) {
		if(controlsbutton[KEY_RIGHT].contains(x, y)) {
			controlsbuttonstate[KEY_RIGHT] = BUTTON_FOCUS;
		}

		else {
			controlsbuttonstate[KEY_RIGHT] = BUTTON_NONE;
		}
	}

	if(controlsbuttonstate[KEY_LEFT] != BUTTON_PRESSED) {
		if(controlsbutton[KEY_LEFT].contains(x, y)) {
			controlsbuttonstate[KEY_LEFT] = BUTTON_FOCUS;
		}

		else {
			controlsbuttonstate[KEY_LEFT] = BUTTON_NONE;
		}
	}

	if(controlsbuttonstate[KEY_RUN] != BUTTON_PRESSED) {
		if(controlsbutton[KEY_RUN].contains(x, y)) {
			controlsbuttonstate[KEY_RUN] = BUTTON_FOCUS;
		}

		else {
			controlsbuttonstate[KEY_RUN] = BUTTON_NONE;
		}
	}

	if(controlsbuttonstate[KEY_FIRE] != BUTTON_PRESSED) {
		if(controlsbutton[KEY_FIRE].contains(x, y)) {
			controlsbuttonstate[KEY_FIRE] = BUTTON_FOCUS;
		}

		else {
			controlsbuttonstate[KEY_FIRE] = BUTTON_NONE;
		}
	}

	if(controlsbuttonstate[KEY_INTERACT] != BUTTON_PRESSED) {
		if(controlsbutton[KEY_INTERACT].contains(x, y)) {
			controlsbuttonstate[KEY_INTERACT] = BUTTON_FOCUS;
		}

		else {
			controlsbuttonstate[KEY_INTERACT] = BUTTON_NONE;
		}
	}

	if(sensbackstate != BUTTON_PRESSED) {
		if(sensbackbuttonhitbox.contains(x, y)) {
			sensbackstate = BUTTON_FOCUS;
		}

		else {
			sensbackstate = BUTTON_NONE;
		}
	}

	if(sensfwstate != BUTTON_PRESSED) {
		if(sensforwardbuttonhitbox.contains(x, y)) {
			sensfwstate = BUTTON_FOCUS;
		}

		else {
			sensfwstate = BUTTON_NONE;
		}
	}
}

void OptionsCanvas::graphicsSettingsPressed(int x, int y) {
	if(brightbackstate != BUTTON_PRESSED) {
		if(brightbackbuttonhitbox.contains(x, y)) {
			brightbackstate = BUTTON_PRESSED;
		}
		else {
			brightbackstate = BUTTON_NONE;
		}
	}

	if(brightfwstate != BUTTON_PRESSED) {
		if(brightforwardbuttonhitbox.contains(x, y)) {
			brightfwstate = BUTTON_PRESSED;
		}
		else {
			brightfwstate = BUTTON_NONE;
		}
	}

	if(quabackbuttonhitbox.contains(x, y)) {
		quabackstate = BUTTON_PRESSED;
	}

	if(quaforwardbuttonhitbox.contains(x, y)) {
		quafwstate = BUTTON_PRESSED;
	}

	if(winbackbuttonhitbox.contains(x, y)) {
		winbackstate = BUTTON_PRESSED;
	}

	if(winforwardbuttonhitbox.contains(x, y)) {
		winfwstate = BUTTON_PRESSED;
	}

	if(resbackbuttonhitbox.contains(x, y)) {
		resbackstate = BUTTON_PRESSED;
	}

	if(resforwardbuttonhitbox.contains(x, y)) {
		resfwstate = BUTTON_PRESSED;
	}
}

void OptionsCanvas::graphicsSettingsReleased(int x, int y) {
	if(brightbackbuttonhitbox.contains(x, y) && brightbackstate == BUTTON_PRESSED) {
		brightbackstate = BUTTON_PERFORMED;
		if(brightness >= 5) brightness -= 5;
		brightnumtext = gToStr(brightness);
	}
	else if(brightforwardbuttonhitbox.contains(x, y) && brightfwstate == BUTTON_PRESSED) {
		brightfwstate = BUTTON_PERFORMED;
		if(brightness < 100) brightness += 5;
		brightnumtext = gToStr(brightness);
	}
	else if(quabackbuttonhitbox.contains(x, y) && quabackstate == BUTTON_PRESSED) {
		quabackstate = BUTTON_PERFORMED;
		selectedquality++;
		if(selectedquality >= qualitynum) selectedquality = 0;
	}

	else if(quaforwardbuttonhitbox.contains(x, y) && quafwstate == BUTTON_PRESSED) {
		quafwstate = BUTTON_PERFORMED;
		selectedquality++;
		if(selectedquality >= qualitynum) selectedquality = 0;
	}
	else if(winbackbuttonhitbox.contains(x, y) && winbackstate == BUTTON_PRESSED) {
		winbackstate = BUTTON_PERFORMED;
		selectedwindowmode++;
		if(selectedwindowmode >= windowmodenum) selectedwindowmode = 0;
	}

	else if(winforwardbuttonhitbox.contains(x, y) && winfwstate == BUTTON_PRESSED) {
		winfwstate = BUTTON_PERFORMED;
		selectedwindowmode++;
		if(selectedwindowmode >= qualitynum) selectedwindowmode = 0;
	}
	else if(resbackbuttonhitbox.contains(x, y) && resbackstate == BUTTON_PRESSED) {
		resbackstate = BUTTON_PERFORMED;
		selectedresolution++;
		if(selectedresolution >= resolutionnum) selectedresolution = 0;
	}

	else if(resforwardbuttonhitbox.contains(x, y) && resfwstate == BUTTON_PRESSED) {
		resfwstate = BUTTON_PERFORMED;
		selectedresolution++;
		if(selectedresolution >= resolutionnum) selectedresolution = 0;
	}
	else {
		brightbackstate = BUTTON_CANCELED;
		brightfwstate = BUTTON_CANCELED;
		quabackstate = BUTTON_CANCELED;
		quafwstate = BUTTON_CANCELED;
		winbackstate = BUTTON_CANCELED;
		winfwstate = BUTTON_CANCELED;
		resbackstate = BUTTON_CANCELED;
		resfwstate = BUTTON_CANCELED;
	}

}

void OptionsCanvas::graphicsSettingsFocus(int x, int y) {
	if(brightbackstate != BUTTON_PRESSED) {
		if(brightbackbuttonhitbox.contains(x, y)) {
			brightbackstate = BUTTON_FOCUS;
		}

		else {
			brightbackstate = BUTTON_NONE;
		}
	}

	if(brightfwstate != BUTTON_PRESSED) {
		if(brightforwardbuttonhitbox.contains(x, y)) {
			brightfwstate = BUTTON_FOCUS;
		}

		else {
			brightfwstate = BUTTON_NONE;
		}
	}

	if(quabackstate != BUTTON_PRESSED) {
		if(quabackbuttonhitbox.contains(x, y)) {
			quabackstate = BUTTON_FOCUS;
		}

		else {
			quabackstate = BUTTON_NONE;
		}
	}

	if(quafwstate != BUTTON_PRESSED) {
		if(quaforwardbuttonhitbox.contains(x, y)) {
			quafwstate = BUTTON_FOCUS;
		}

		else {
			quafwstate = BUTTON_NONE;
		}
	}

	if(winbackstate != BUTTON_PRESSED) {
		if(winbackbuttonhitbox.contains(x, y)) {
			winbackstate = BUTTON_FOCUS;
		}

		else {
			winbackstate = BUTTON_NONE;
		}
	}

	if(winfwstate != BUTTON_PRESSED) {
		if(winforwardbuttonhitbox.contains(x, y)) {
			winfwstate = BUTTON_FOCUS;
		}

		else {
			winfwstate = BUTTON_NONE;
		}
	}

	if(resbackstate != BUTTON_PRESSED) {
		if(resbackbuttonhitbox.contains(x, y)) {
			resbackstate = BUTTON_FOCUS;
		}

		else {
			resbackstate = BUTTON_NONE;
		}
	}

	if(resfwstate != BUTTON_PRESSED) {
		if(resforwardbuttonhitbox.contains(x, y)) {
			resfwstate = BUTTON_FOCUS;
		}

		else {
			resfwstate = BUTTON_NONE;
		}
	}
}

void OptionsCanvas::audioSettingsPressed(int x, int y) {
	if(musicbackstate != BUTTON_PRESSED) {
		if(musicbackbuttonhitbox.contains(x, y)) {
			musicbackstate = BUTTON_PRESSED;
		}
		else {
			musicbackstate = BUTTON_NONE;
		}
	}

	if(musicfwstate != BUTTON_PRESSED) {
		if(musicforwardbuttonhitbox.contains(x, y)) {
			musicfwstate = BUTTON_PRESSED;
		}
		else {
			musicfwstate = BUTTON_NONE;
		}
	}

	if(fxbackstate != BUTTON_PRESSED) {
		if(fxbackbuttonhitbox.contains(x, y)) {
			fxbackstate = BUTTON_PRESSED;
		}
		else {
			fxbackstate = BUTTON_NONE;
		}
	}

	if(fxfwstate != BUTTON_PRESSED) {
		if(fxforwardbuttonhitbox.contains(x, y)) {
			fxfwstate = BUTTON_PRESSED;
		}
		else {
			fxfwstate = BUTTON_NONE;
		}
	}

	if(musicbuttonhitbox.contains(x, y)) {
		musictickstate = BUTTON_PRESSED;
	}

	if(fxbuttonhitbox.contains(x, y)) {
		fxtickstate = BUTTON_PRESSED;
	}
}

void OptionsCanvas::audioSettingsReleased(int x, int y) {
	if(musicbackbuttonhitbox.contains(x, y) && musicbackstate == BUTTON_PRESSED) {
		musicbackstate = BUTTON_PERFORMED;
		if(musicvalue >= 5) musicvalue -= 5;
		musicnumtext = gToStr(musicvalue);
	}
	else if(musicforwardbuttonhitbox.contains(x, y) && musicfwstate == BUTTON_PRESSED) {
		musicfwstate = BUTTON_PERFORMED;
		if(musicvalue < 100) musicvalue += 5;
		musicnumtext = gToStr(musicvalue);
	}
	else if(fxbackbuttonhitbox.contains(x, y) && fxbackstate == BUTTON_PRESSED) {
		fxbackstate = BUTTON_PERFORMED;
		if(effectvalue >= 5) effectvalue -= 5;
		fxnumtext = gToStr(effectvalue);
	}
	else if(fxforwardbuttonhitbox.contains(x, y) && fxfwstate == BUTTON_PRESSED) {
		fxfwstate = BUTTON_PERFORMED;
		if(effectvalue < 100) effectvalue += 5;
		fxnumtext = gToStr(effectvalue);
	}
	else if(musicbuttonhitbox.contains(x, y) && musictickstate == BUTTON_PRESSED) {
	    musictickstate = BUTTON_PERFORMED;
	    ismusicenabled = !ismusicenabled;
	}
	else if(fxbuttonhitbox.contains(x, y) && fxtickstate == BUTTON_PRESSED) {
	    fxtickstate = BUTTON_PERFORMED;
	    isfxenabled = !isfxenabled;
	}
	else {
		musicbackstate = BUTTON_CANCELED;
		musicfwstate = BUTTON_CANCELED;
		fxbackstate = BUTTON_CANCELED;
		fxfwstate = BUTTON_CANCELED;
		musictickstate = BUTTON_CANCELED;
		fxtickstate = BUTTON_CANCELED;
	}

}

void OptionsCanvas::audioSettingsFocus(int x, int y) {
	if(musicbackstate != BUTTON_PRESSED) {
		if(musicbackbuttonhitbox.contains(x, y)) {
			musicbackstate = BUTTON_FOCUS;
		}

		else {
			musicbackstate = BUTTON_NONE;
		}
	}

	if(musicfwstate != BUTTON_PRESSED) {
		if(musicforwardbuttonhitbox.contains(x, y)) {
			musicfwstate = BUTTON_FOCUS;
		}

		else {
			musicfwstate = BUTTON_NONE;
		}
	}
	if(fxbackstate != BUTTON_PRESSED) {
		if(fxbackbuttonhitbox.contains(x, y)) {
			fxbackstate = BUTTON_FOCUS;
		}

		else {
			fxbackstate = BUTTON_NONE;
		}
	}

	if(fxfwstate != BUTTON_PRESSED) {
		if(fxforwardbuttonhitbox.contains(x, y)) {
			fxfwstate = BUTTON_FOCUS;
		}

		else {
			fxfwstate = BUTTON_NONE;
		}
	}
}

void OptionsCanvas::returnSetup() {
	returntext = root->localizeWord(root->returnkey);
	returnh = root->menutitlefont.getStringHeight(returntext);
	returnw = root->menutitlefont.getStringWidth(returntext);
	returnx = getWidth() * 5/100;
	returny = getHeight() * 95/100;

	returnhitbox.set(returnx, returny - returnh, returnx + returnw, returny);
	returnbuttonstate = BUTTON_NONE;
}

void OptionsCanvas::returnDraw() {
	setColor(255, 255, 255);
	if(returnbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(returnbuttonstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(returntext, returnx, returny);
	setColor(0, 0, 0);
}

void OptionsCanvas::gameTabButtonSetup() {
	gametabtext = "GAME";
	gametabbuttonstate = BUTTON_NONE;
	gametabbuttonw = tabw / 4;
	gametabbuttonh = tabh;
	gametabbuttonx = containerx - gametabbuttonw;
	gametabbuttony = containery;
	gametabbutton.set(gametabbuttonx, gametabbuttony, gametabbuttonx + gametabbuttonw, gametabbuttony + gametabbuttonh);
}

void OptionsCanvas::controlsTabButtonSetup() {
	controlstabtext = "CONTROLS";
	controlstabbuttonstate = BUTTON_NONE;
	controlstabbuttonw = tabw / 4;
	controlstabbuttonh = tabh;
	controlstabbuttonx = gametabbuttonx;
	controlstabbuttony = gametabbuttony + controlstabbuttonh;
	controlstabbutton.set(controlstabbuttonx, controlstabbuttony, controlstabbuttonx + controlstabbuttonw, controlstabbuttony + controlstabbuttonh);
}

void OptionsCanvas::graphicsTabButtonSetup() {
	graphicstabtext = "GRAPHICS";
	graphicstabbuttonstate = BUTTON_NONE;
	graphicstabbuttonw = tabw / 4;
	graphicstabbuttonh = tabh;
	graphicstabbuttonx = gametabbuttonx;
	graphicstabbuttony = controlstabbuttony + graphicstabbuttonh;
	graphicstabbutton.set(graphicstabbuttonx, graphicstabbuttony, graphicstabbuttonx + graphicstabbuttonw, graphicstabbuttony + graphicstabbuttonh);

}

void OptionsCanvas::audioTabButtonSetup() {
	audiotabtext = "AUDIO";
	audiotabbuttonstate = BUTTON_NONE;
	audiotabbuttonw = tabw / 4;
	audiotabbuttonh = tabh;
	audiotabbuttonx = gametabbuttonx;
	audiotabbuttony = graphicstabbuttony + audiotabbuttonh;
	audiotabbutton.set(audiotabbuttonx, audiotabbuttony, audiotabbuttonx + audiotabbuttonw, audiotabbuttony + audiotabbuttonh);

}

void OptionsCanvas::gameTabButtonDraw() {
	if(gametabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(gametabbuttonstate == BUTTON_PRESSED || gametabbuttonstate == BUTTON_PERFORMED || activetab == TAB_GAME) setColor(pressedcolor);
	gDrawRectangle(gametabbuttonx, gametabbuttony, gametabbuttonw, gametabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(gametabtext);
	tabfonth = root->menutitlefont.getStringHeight(gametabtext);
	tabfontx = gametabbuttonx + (gametabbuttonw - tabfontw) / 2;
	tabfonty = gametabbuttony + (gametabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(gametabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void OptionsCanvas::controlsTabButtonDraw() {
	if(controlstabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(controlstabbuttonstate == BUTTON_PRESSED || controlstabbuttonstate == BUTTON_PERFORMED || activetab == TAB_CONTROLS) setColor(pressedcolor);
	gDrawRectangle(controlstabbuttonx, controlstabbuttony, controlstabbuttonw, controlstabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(controlstabtext);
	tabfonth = root->menutitlefont.getStringHeight(controlstabtext);
	tabfontx = controlstabbuttonx + (controlstabbuttonw - tabfontw) / 2;
	tabfonty = controlstabbuttony + (controlstabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(controlstabtext, tabfontx, tabfonty);
	setColor(normalcolor);

}

void OptionsCanvas::graphicsTabButtonDraw() {
	if(graphicstabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(graphicstabbuttonstate == BUTTON_PRESSED || graphicstabbuttonstate == BUTTON_PERFORMED || activetab == TAB_GRAPHICS) setColor(pressedcolor);
	gDrawRectangle(graphicstabbuttonx, graphicstabbuttony, graphicstabbuttonw, graphicstabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(graphicstabtext);
	tabfonth = root->menutitlefont.getStringHeight(graphicstabtext);
	tabfontx = graphicstabbuttonx + (graphicstabbuttonw - tabfontw) / 2;
	tabfonty = graphicstabbuttony + (graphicstabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(graphicstabtext, tabfontx, tabfonty);
	setColor(normalcolor);

}

void OptionsCanvas::audioTabButtonDraw() {
	if(audiotabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(audiotabbuttonstate == BUTTON_PRESSED || audiotabbuttonstate == BUTTON_PERFORMED || activetab == TAB_AUDIO) setColor(pressedcolor);
	gDrawRectangle(audiotabbuttonx, audiotabbuttony, audiotabbuttonw, audiotabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(audiotabtext);
	tabfonth = root->menutitlefont.getStringHeight(audiotabtext);
	tabfontx = audiotabbuttonx + (audiotabbuttonw - tabfontw) / 2;
	tabfonty = audiotabbuttony + (audiotabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(audiotabtext, tabfontx, tabfonty);
	setColor(normalcolor);

}

void OptionsCanvas::applyTabButtonSetup() {
	applytabtext = "APPLY";
	applytabbuttonstate = BUTTON_NONE;
	applytabbuttonw = tabw / 4;
	applytabbuttonh = tabh;
	applytabbuttonx = gametabbuttonx;
	applytabbuttony = audiotabbuttony + (applytabbuttonh * 2);
	applytabbutton.set(applytabbuttonx, applytabbuttony, applytabbuttonx + applytabbuttonw, applytabbuttony + applytabbuttonh);

}

void OptionsCanvas::resetTabButtonSetup() {
	resettabtext = "RESET";
	resettabbuttonstate = BUTTON_NONE;
	resettabbuttonw = tabw / 4;
	resettabbuttonh = tabh;
	resettabbuttonx = gametabbuttonx;
	resettabbuttony = applytabbuttony + resettabbuttonh;
	resettabbutton.set(resettabbuttonx, resettabbuttony, resettabbuttonx + resettabbuttonw, resettabbuttony + resettabbuttonh);
}

void OptionsCanvas::applyTabButtonDraw() {
	if(applytabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(applytabbuttonstate == BUTTON_PRESSED || applytabbuttonstate == BUTTON_PERFORMED || activetab == TAB_APPLY) setColor(pressedcolor);
	gDrawRectangle(applytabbuttonx, applytabbuttony, applytabbuttonw, applytabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(applytabtext);
	tabfonth = root->menutitlefont.getStringHeight(applytabtext);
	tabfontx = applytabbuttonx + (applytabbuttonw - tabfontw) / 2;
	tabfonty = applytabbuttony + (applytabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(applytabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void OptionsCanvas::resetTabButtonDraw() {
	if(resettabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(resettabbuttonstate == BUTTON_PRESSED || resettabbuttonstate == BUTTON_PERFORMED || activetab == TAB_RESET) setColor(pressedcolor);
	gDrawRectangle(resettabbuttonx, resettabbuttony, resettabbuttonw, resettabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(resettabtext);
	tabfonth = root->menutitlefont.getStringHeight(resettabtext);
	tabfontx = resettabbuttonx + (resettabbuttonw - tabfontw) / 2;
	tabfonty = resettabbuttony + (resettabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(resettabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void OptionsCanvas::languageSetup() {
	languagelabeltext = "Language: ";
	languages[0] = "English";
	languages[1] = "Turkish";
	langbackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	langforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");

	selectedlanguage = root->getLanguage();
	languagelabelh = root->menutitlefont.getStringHeight("y");
	languagelabelx = containerx + containerw / 10;
	languagelabely = containery + containerh / 15 + languagelabelh;
	languagesw = root->menutitlefont.getStringWidth(languages[selectedlanguage]);
	languagesx = languagelabelx + languagesw * 2;
	languagesh = root->menutitlefont.getStringHeight(languages[selectedlanguage]);
	langbackbuttonw = langbackbutton.getWidth() * 0.4;
	langbackbuttonh = langbackbutton.getHeight() * 0.4;
	langbackbuttonx = languagesx - langbackbuttonw;
	langbackbuttony = languagelabely - (languagesh / 2) - (langbackbuttonh / 2) + 3;
	langforwardbuttonx = languagesx + languagesw + (langbackbuttonw / 2);
	langbackbuttonhitbox.set(langbackbuttonx, langbackbuttony, langbackbuttonx + langbackbuttonw, langbackbuttony + langbackbuttonh);
	langforwardbuttonhitbox.set(langforwardbuttonx, langbackbuttony, langforwardbuttonx + langbackbuttonw, langbackbuttony + langbackbuttonh);
}

void OptionsCanvas::minimapSetup() {
	minimaptext = "Minimap";
	muncheck.loadImage("PNG/inactivecolor.png");
	mcheck.loadImage("PNG/check-markred.png");

	maptextw = root->menutitlefont.getStringWidth(minimaptext);
	maptexth = root->menutitlefont.getStringHeight(minimaptext);
	maptextx = languagelabelx;
	maptexty = languagelabely + languagesw + maptexth;
	muncheckw = muncheck.getWidth();
	muncheckh = muncheck.getHeight();
	muncheckx = maptextx + maptextw + muncheckw;
	munchecky = maptexty - (maptexth / 2) - (muncheckh / 2) + 3;
	mcheckw = mcheck.getWidth() * 0.06;
	mcheckh = mcheck.getHeight() * 0.06;
	mapbuttonhitbox.set(muncheckx, munchecky, muncheckx + muncheckw, munchecky + muncheckh);
	isminimapenabled = root->getMinimap();
}

void OptionsCanvas::fpsSetup() {
	fpstext = "Show Fps";
	fpsuncheck.loadImage("PNG/inactivecolor.png");
	fpscheck.loadImage("PNG/check-markred.png");
	fpstextw = root->menutitlefont.getStringWidth(fpstext);
	fpstexth = root->menutitlefont.getStringHeight(fpstext);
	fpstextx = languagelabelx;
	fpstexty = maptexty + fpstexth + languagesw;
	fpsuncheckw = fpsuncheck.getWidth();
	fpsuncheckh = fpsuncheck.getHeight();
	fpsuncheckx = muncheckx;
	fpsunchecky = fpstexty - (fpstexth / 2) - (fpsuncheckh / 2) + 3;
	fpscheckw = fpscheck.getWidth() * 0.06;
	fpscheckh = fpscheck.getHeight() * 0.06;
	fpsbuttonhitbox.set(fpsuncheckx, fpsunchecky, fpsuncheckx + fpsuncheckw, fpsunchecky + fpsuncheckh);
	isfpsenabled = root->getShowFps();
}

void OptionsCanvas::vsyncSetup() {
	vsynctext = "VSync";
	vsyncuncheck.loadImage("PNG/inactivecolor.png");
	vsynccheck.loadImage("PNG/check-markred.png");
	vsynctextw = root->menutitlefont.getStringWidth(vsynctext);
	vsynctexth = root->menutitlefont.getStringHeight(vsynctext);
	vsynctextx = languagelabelx;
	vsynctexty = fpstexty + vsynctexth + languagesw;
	vsyncuncheckw = vsyncuncheck.getWidth();
	vsyncuncheckh = vsyncuncheck.getHeight();
	vsyncuncheckx = muncheckx;
	vsyncunchecky = vsynctexty - (vsynctexth / 2) - (vsyncuncheckh / 2) + 3;
	vsynccheckw = vsynccheck.getWidth() * 0.06;
	vsynccheckh = vsynccheck.getHeight() * 0.06;
	vsyncbuttonhitbox.set(vsyncuncheckx, vsyncunchecky, vsyncuncheckx + vsyncuncheckw, vsyncunchecky + vsyncuncheckh);
	isvsyncenabled = root->getVsync();
}

void OptionsCanvas::languageDraw() {
	setColor(0, 0, 0);

	root->menutitlefont.drawText(languagelabeltext, languagelabelx, languagelabely);
	root->menutitlefont.drawText(languages[selectedlanguage], languagesx, languagelabely);
	langbackbutton.draw(langbackbuttonx, langbackbuttony, langbackbuttonw, langbackbuttonh);
	langforwardbutton.draw(langforwardbuttonx, langbackbuttony, langbackbuttonw, langbackbuttonh);

	if(langbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(langbackstate == BUTTON_PRESSED || langbackstate == BUTTON_PERFORMED) setColor(pressedcolor);

	if(langfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(langfwstate == BUTTON_PRESSED || langfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
}

void OptionsCanvas::minimapDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(minimaptext, maptextx, maptexty);
	muncheck.draw(muncheckx, munchecky);
	if(isminimapenabled) {
		setColor(255, 255, 255);
	    mcheck.draw(muncheckx, munchecky, mcheckw, mcheckh);
	}
}

void OptionsCanvas::fpsDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(fpstext, fpstextx, fpstexty);
	fpsuncheck.draw(fpsuncheckx, fpsunchecky);
	if(isfpsenabled) {
		setColor(255, 255, 255);
	    fpscheck.draw(fpsuncheckx, fpsunchecky, fpscheckw, fpscheckh);
	}
	setColor(0, 0, 0);
}

void OptionsCanvas::vsyncDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(vsynctext, vsynctextx, vsynctexty);
	vsyncuncheck.draw(vsyncuncheckx, vsyncunchecky);
	if(isvsyncenabled) {
		setColor(255, 255, 255);
		vsynccheck.draw(vsyncuncheckx, vsyncunchecky, vsynccheckw, vsynccheckh);
	}
	setColor(0, 0, 0);
}

void OptionsCanvas::controlButtonsSetup() {
	ischangingkey = false;

	selectedkey = KEY_NONE;
	keyboardcontrols[KEY_FORWARD] = root->getForwardKey();
	keyboardcontrols[KEY_BACKWARD] = root->getBackwardKey();
	keyboardcontrols[KEY_RIGHT] = root->getRightKey();
	keyboardcontrols[KEY_LEFT] = root->getLeftKey();
	keyboardcontrols[KEY_RUN] = root->getRunKey();
	keyboardcontrols[KEY_FIRE] = root->getFireKey();
	keyboardcontrols[KEY_INTERACT] = root->getInteractKey();

	//forward
	controllabeltext[KEY_FORWARD] = root->localizeWord("forward");   // "Forward" veya "Ýleri" vs.
	int key1 = keyboardcontrols[KEY_FORWARD];

	if(key1 == 0) {
	    controldisplaytext[KEY_FORWARD] = "-";
	} else {
	    controldisplaytext[KEY_FORWARD] = gCodepointToStr(key1);
	}
	controldisplaytext[KEY_FORWARD] = gCodepointToStr(keyboardcontrols[KEY_FORWARD]);
	controllabelw[KEY_FORWARD] = root->menutitlefont.getStringWidth(controllabeltext[KEY_FORWARD]);
	controllabelh[KEY_FORWARD] = root->menutitlefont.getStringHeight(controllabeltext[KEY_FORWARD]);
	controllabelx[KEY_FORWARD] = containerx + containerw / 10;
	controllabely[KEY_FORWARD] = containery + containerh / 15 + controllabelh[KEY_FORWARD];
	controlw[KEY_FORWARD] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_FORWARD]);
	controlh[KEY_FORWARD] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_FORWARD]);
	controlx[KEY_FORWARD] = containerx + (containerw / 2) - (containerw / 10) - controlw[KEY_FORWARD];
	controly[KEY_FORWARD] = controllabely[KEY_FORWARD];

	controlsbutton[KEY_FORWARD].set(controlx[KEY_FORWARD], controly[KEY_FORWARD] - controlh[KEY_FORWARD], controlx[KEY_FORWARD] + controlw[KEY_FORWARD], controly[KEY_FORWARD]);

	//backward
	controllabeltext[KEY_BACKWARD] = root->localizeWord(root->backwardkey);
	int key2 = keyboardcontrols[KEY_BACKWARD];

	if(key2 == 0) {
	    controldisplaytext[KEY_BACKWARD] = "-";
	} else {
	    controldisplaytext[KEY_BACKWARD] = gCodepointToStr(key2);
	}
	controldisplaytext[KEY_BACKWARD] = gCodepointToStr(keyboardcontrols[KEY_BACKWARD]);
	controllabelw[KEY_BACKWARD] = root->menutitlefont.getStringWidth(controllabeltext[KEY_BACKWARD]);
	controllabelh[KEY_BACKWARD] = root->menutitlefont.getStringHeight(controllabeltext[KEY_BACKWARD]);
	controllabelx[KEY_BACKWARD] = controllabelx[KEY_FORWARD];
	controllabely[KEY_BACKWARD] = controllabely[KEY_FORWARD]  + containerh / 15 + controllabelh[KEY_BACKWARD];
	controlw[KEY_BACKWARD] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_BACKWARD]);
	controlh[KEY_BACKWARD] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_BACKWARD]);
	controlx[KEY_BACKWARD] = containerx + (containerw / 2) - (containerw / 10) - controlw[KEY_BACKWARD];
	controly[KEY_BACKWARD] = controllabely[KEY_BACKWARD];

	controlsbutton[KEY_BACKWARD].set(controlx[KEY_BACKWARD], controly[KEY_BACKWARD] - controlh[KEY_BACKWARD], controlx[KEY_BACKWARD] + controlw[KEY_BACKWARD], controly[KEY_BACKWARD]);

	//right
	controllabeltext[KEY_RIGHT] = root->localizeWord(root->rightkey);
	int key3 = keyboardcontrols[KEY_RIGHT];

	if(key3 == 0) {
	    controldisplaytext[KEY_RIGHT] = "-";
	} else {
	    controldisplaytext[KEY_RIGHT] = gCodepointToStr(key3);
	}
	controldisplaytext[KEY_RIGHT] = gCodepointToStr(keyboardcontrols[KEY_RIGHT]);
	controllabelw[KEY_RIGHT] = root->menutitlefont.getStringWidth(controllabeltext[KEY_RIGHT]);
	controllabelh[KEY_RIGHT] = root->menutitlefont.getStringHeight(controllabeltext[KEY_RIGHT]);
	controllabelx[KEY_RIGHT] = controllabelx[KEY_FORWARD];
	controllabely[KEY_RIGHT] = controllabely[KEY_BACKWARD]  + containerh / 15 + controllabelh[KEY_RIGHT];
	controlw[KEY_RIGHT] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_RIGHT]);
	controlh[KEY_RIGHT] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_RIGHT]);
	controlx[KEY_RIGHT] = containerx + (containerw / 2) - (containerw / 10) - controlw[KEY_RIGHT];
	controly[KEY_RIGHT] = controllabely[KEY_RIGHT];

	controlsbutton[KEY_RIGHT].set(controlx[KEY_RIGHT], controly[KEY_RIGHT] - controlh[KEY_RIGHT], controlx[KEY_RIGHT] + controlw[KEY_RIGHT], controly[KEY_RIGHT]);

	//left
	controllabeltext[KEY_LEFT] = root->localizeWord(root->leftkey);
	int key4 = keyboardcontrols[KEY_LEFT];

	if(key4 == 0) {
	    controldisplaytext[KEY_LEFT] = "-";
	} else {
	    controldisplaytext[KEY_LEFT] = gCodepointToStr(key4);
	}
	controldisplaytext[KEY_LEFT] = gCodepointToStr(keyboardcontrols[KEY_LEFT]);
	controllabelw[KEY_LEFT] = root->menutitlefont.getStringWidth(controllabeltext[KEY_LEFT]);
	controllabelh[KEY_LEFT] = root->menutitlefont.getStringHeight(controllabeltext[KEY_LEFT]);
	controllabelx[KEY_LEFT] = controllabelx[KEY_FORWARD];
	controllabely[KEY_LEFT] = controllabely[KEY_RIGHT]  + containerh / 15 + controllabelh[KEY_LEFT];
	controlw[KEY_LEFT] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_LEFT]);
	controlh[KEY_LEFT] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_LEFT]);
	controlx[KEY_LEFT] = containerx + (containerw / 2) - (containerw / 10) - controlw[KEY_LEFT];
	controly[KEY_LEFT] = controllabely[KEY_LEFT];

	controlsbutton[KEY_LEFT].set(controlx[KEY_LEFT], controly[KEY_LEFT] - controlh[KEY_LEFT], controlx[KEY_LEFT] + controlw[KEY_LEFT], controly[KEY_LEFT]);

	//run
	controllabeltext[KEY_RUN] = root->localizeWord(root->runkey);
	int key5 = keyboardcontrols[KEY_RUN];

	if(key5 == 0) {
	    controldisplaytext[KEY_RUN] = "-";
	} else {
	    controldisplaytext[KEY_RUN] = gCodepointToStr(key5);
	}
	controldisplaytext[KEY_RUN] = gCodepointToStr(keyboardcontrols[KEY_RUN]);
	controllabelw[KEY_RUN] = root->menutitlefont.getStringWidth(controllabeltext[KEY_RUN]);
	controllabelh[KEY_RUN] = root->menutitlefont.getStringHeight(controllabeltext[KEY_RUN]);
	controllabelx[KEY_RUN] = containerx + containerw / 2;
	controllabely[KEY_RUN] = containery  + containerh / 15 + controllabelh[KEY_RUN];
	controlw[KEY_RUN] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_RUN]);
	controlh[KEY_RUN] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_RUN]);
	controlx[KEY_RUN] = containerx + containerw - (containerw / 10) - controlw[KEY_RUN];
	controly[KEY_RUN] = controllabely[KEY_RUN];

	controlsbutton[KEY_RUN].set(controlx[KEY_RUN], controly[KEY_RUN] - controlh[KEY_RUN], controlx[KEY_RUN] + controlw[KEY_RUN], controly[KEY_RUN]);

	//fire
	controllabeltext[KEY_FIRE] = root->localizeWord(root->firekey);
	int key6 = keyboardcontrols[KEY_FIRE];

	if(key6 == 0) {
	    controldisplaytext[KEY_FIRE] = "-";
	} else {
	    controldisplaytext[KEY_FIRE] = gCodepointToStr(key6);
	}
	controldisplaytext[KEY_FIRE] = gCodepointToStr(keyboardcontrols[KEY_FIRE]);
	controllabelw[KEY_FIRE] = root->menutitlefont.getStringWidth(controllabeltext[KEY_FIRE]);
	controllabelh[KEY_FIRE] = root->menutitlefont.getStringHeight(controllabeltext[KEY_FIRE]);
	controllabelx[KEY_FIRE] = controllabelx[KEY_RUN];
	controllabely[KEY_FIRE] = controllabely[KEY_RUN]  + containerh / 15 + controllabelh[KEY_FIRE];
	controlw[KEY_FIRE] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_FIRE]);
	controlh[KEY_FIRE] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_FIRE]);
	controlx[KEY_FIRE] = containerx + containerw - (containerw / 10) - controlw[KEY_FIRE];
	controly[KEY_FIRE] = controllabely[KEY_FIRE];

	controlsbutton[KEY_FIRE].set(controlx[KEY_FIRE], controly[KEY_FIRE] - controlh[KEY_FIRE], controlx[KEY_FIRE] + controlw[KEY_FIRE], controly[KEY_FIRE]);

	//interact
	controllabeltext[KEY_INTERACT] = root->localizeWord(root->interactkey);
	int key7 = keyboardcontrols[KEY_INTERACT];

	if(key7 == 0) {
	    controldisplaytext[KEY_INTERACT] = "-";
	} else {
	    controldisplaytext[KEY_INTERACT] = gCodepointToStr(key7);
	}
	controllabelw[KEY_INTERACT] = root->menutitlefont.getStringWidth(controllabeltext[KEY_INTERACT]);
	controllabelh[KEY_INTERACT] = root->menutitlefont.getStringHeight(controllabeltext[KEY_INTERACT]);
	controllabelx[KEY_INTERACT] = controllabelx[KEY_RUN];
	controllabely[KEY_INTERACT] = controllabely[KEY_FIRE]  + containerh / 15 + controllabelh[KEY_INTERACT];
	controlw[KEY_INTERACT] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_INTERACT]);
	controlh[KEY_INTERACT] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_INTERACT]);
	controlx[KEY_INTERACT] = containerx + containerw - (containerw / 10) - controlw[KEY_INTERACT];
	controly[KEY_INTERACT] = controllabely[KEY_INTERACT];

	controlsbutton[KEY_INTERACT].set(controlx[KEY_INTERACT], controly[KEY_INTERACT] - controlh[KEY_INTERACT], controlx[KEY_INTERACT] + controlw[KEY_INTERACT], controly[KEY_INTERACT]);
}

void OptionsCanvas::sensitivitySetup() {
	sensbackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	sensforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");
	sensitivity = root->getSensitivity();
	sensnumtext = gToStr(sensitivity);
	senslabeltext = "Sensitivity";
	senslabelh = root->menutitlefont.getStringHeight("y");
	senslabelx = containerx + containerw / 10;
	senslabely = containery + containerh / 15 + senslabelh;
	sensw = root->menutitlefont.getStringWidth(sensnumtext);
	sensx = senslabelx + root->menutitlefont.getStringWidth(senslabeltext) + 40;
	sensh = root->menutitlefont.getStringHeight(sensnumtext);
	sensbackbuttonw = sensbackbutton.getWidth() * 0.4;
	sensbackbuttonh = sensbackbutton.getHeight() * 0.4;
	sensbackbuttonx = sensx - sensbackbuttonw - 10;
	sensbackbuttony = senslabely - (sensh / 2) - (sensbackbuttonh / 2) + 303;
	sensforwardbuttonx = sensx + sensw + 10;
	sensbackbuttonhitbox.set(sensbackbuttonx, sensbackbuttony, sensbackbuttonx + sensbackbuttonw, sensbackbuttony + sensbackbuttonh);
	sensforwardbuttonhitbox.set(sensforwardbuttonx, sensbackbuttony, sensforwardbuttonx + sensbackbuttonw, sensbackbuttony + sensbackbuttonh);
}

void OptionsCanvas::controlButtonsDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_FORWARD], controllabelx[KEY_FORWARD], controllabely[KEY_FORWARD] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_FORWARD] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_FORWARD] == BUTTON_PRESSED || controlsbuttonstate[KEY_FORWARD] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_FORWARD], controlx[KEY_FORWARD], controly[KEY_FORWARD]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_BACKWARD], controllabelx[KEY_BACKWARD], controllabely[KEY_BACKWARD] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_BACKWARD] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_BACKWARD] == BUTTON_PRESSED || controlsbuttonstate[KEY_BACKWARD] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_BACKWARD], controlx[KEY_BACKWARD], controly[KEY_BACKWARD]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_RIGHT], controllabelx[KEY_RIGHT], controllabely[KEY_RIGHT] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_RIGHT] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_RIGHT] == BUTTON_PRESSED || controlsbuttonstate[KEY_RIGHT] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_RIGHT], controlx[KEY_RIGHT], controly[KEY_RIGHT]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_LEFT], controllabelx[KEY_LEFT], controllabely[KEY_LEFT] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_LEFT] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_LEFT] == BUTTON_PRESSED || controlsbuttonstate[KEY_LEFT] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_LEFT], controlx[KEY_LEFT], controly[KEY_LEFT]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_RUN], controllabelx[KEY_RUN], controllabely[KEY_RUN] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_RUN] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_RUN] == BUTTON_PRESSED || controlsbuttonstate[KEY_RUN] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_RUN], controlx[KEY_RUN], controly[KEY_RUN]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_FIRE], controllabelx[KEY_FIRE], controllabely[KEY_FIRE] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_FIRE] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_FIRE] == BUTTON_PRESSED || controlsbuttonstate[KEY_FIRE] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_FIRE], controlx[KEY_FIRE], controly[KEY_FIRE]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_INTERACT], controllabelx[KEY_INTERACT], controllabely[KEY_INTERACT] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_INTERACT] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_INTERACT] == BUTTON_PRESSED || controlsbuttonstate[KEY_INTERACT] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_INTERACT], controlx[KEY_INTERACT], controly[KEY_INTERACT]);
}

void OptionsCanvas::sensitivityDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(senslabeltext, senslabelx, senslabely + 300);

	if(sensbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(sensbackstate == BUTTON_PRESSED || sensbackstate == BUTTON_PERFORMED) setColor(pressedcolor);
	sensbackbutton.draw(sensbackbuttonx, sensbackbuttony, sensbackbuttonw, sensbackbuttonh);

	setColor(0, 0, 0);
	if(sensfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(sensfwstate == BUTTON_PRESSED || sensfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
	sensforwardbutton.draw(sensforwardbuttonx, sensbackbuttony, sensbackbuttonw, sensbackbuttonh);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(sensnumtext, sensx, senslabely + 300);
}

void OptionsCanvas::brightnessSetup() {
	brightbackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	brightforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");

	brightness = root->getBrightness();
	brightnumtext = gToStr(brightness);
	brightlabeltext = "Brightness";
	brightlabelh = root->menutitlefont.getStringHeight("y");
	brightlabelx = containerx + containerw / 10;
	brightlabely = containery + containerh / 15 + brightlabelh;
	brightw = root->menutitlefont.getStringWidth(brightnumtext);
	brightx = brightlabelx + root->menutitlefont.getStringWidth(brightlabeltext) + 40;
	brighth = root->menutitlefont.getStringHeight(brightnumtext);
	brightbackbuttonw = brightbackbutton.getWidth() * 0.4;
	brightbackbuttonh = brightbackbutton.getHeight() * 0.4;
	brightbackbuttonx = brightx - brightbackbuttonw - 10;
	brightbackbuttony = brightlabely - (brighth / 2) - (brightbackbuttonh / 2) +  3;
	brightforwardbuttonx = brightx + brightw + 10;
	brightbackbuttonhitbox.set(brightbackbuttonx, brightbackbuttony, brightbackbuttonx + brightbackbuttonw, brightbackbuttony + brightbackbuttonh);
	brightforwardbuttonhitbox.set(brightforwardbuttonx, brightbackbuttony, brightforwardbuttonx + brightbackbuttonw, brightbackbuttony + brightbackbuttonh);
}

void OptionsCanvas::qualitySetup() {
	qualitylabeltext = "Quality: ";
	qualities[0] = "High";
	qualities[1] = "Normal";
	qualities[2] = "Low";
	quabackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	quaforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");

	selectedquality = root->getQuality();
	qualabelh = root->menutitlefont.getStringHeight("y");
	qualabelx = containerx + containerw / 10;
	qualabely = (containery + containerh / 15 + qualabelh) + 100;
	qualitiesw = root->menutitlefont.getStringWidth(qualities[selectedquality]);
	qualitiesx = qualabelx + qualitiesw * 2;
	qualitiesh = root->menutitlefont.getStringHeight(qualities[selectedquality]);
	quabackbuttonw = quabackbutton.getWidth() * 0.4;
	quabackbuttonh = quabackbutton.getHeight() * 0.4;
	quabackbuttonx = qualitiesx - quabackbuttonw;
	quabackbuttony = qualabely - (qualitiesh / 2) - (quabackbuttonh / 2) + 3;
	quaforwardbuttonx = qualitiesx + qualitiesw + (quabackbuttonw / 2);
	quabackbuttonhitbox.set(quabackbuttonx, quabackbuttony, quabackbuttonx + quabackbuttonw, quabackbuttony + quabackbuttonh);
	quaforwardbuttonhitbox.set(quaforwardbuttonx, quabackbuttony, quaforwardbuttonx + quabackbuttonw, quabackbuttony + quabackbuttonh);
}

void OptionsCanvas::windowmodeSetup() {
	windowmodelabeltext = "Window Mode: ";
	windowmodes[0] = "FullScreen";
	windowmodes[1] = "Borderless";
	windowmodes[2] = "Windowed";
	winbackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	winforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");

	selectedwindowmode = root->getWindowMode();
	winlabelh = root->menutitlefont.getStringHeight("y");
	winlabelx = containerx + containerw / 10;
	winlabely = (containery + containerh / 15 + winlabelh) + 200;
	windowmodesw = root->menutitlefont.getStringWidth(windowmodes[selectedwindowmode]);
	windowmodesx = winlabelx + windowmodesw * 2;
	windowmodesh = root->menutitlefont.getStringHeight(windowmodes[selectedwindowmode]);
	winbackbuttonw = winbackbutton.getWidth() * 0.4;
	winbackbuttonh = winbackbutton.getHeight() * 0.4;
	winbackbuttonx = windowmodesx - winbackbuttonw;
	winbackbuttony = winlabely - (windowmodesh / 2) - (winbackbuttonh / 2) + 3;
	winforwardbuttonx = windowmodesx + windowmodesw + (winbackbuttonw / 2);
	winbackbuttonhitbox.set(winbackbuttonx, winbackbuttony, winbackbuttonx + winbackbuttonw, winbackbuttony + winbackbuttonh);
	winforwardbuttonhitbox.set(winforwardbuttonx, winbackbuttony, winforwardbuttonx + winbackbuttonw, winbackbuttony + winbackbuttonh);
}

void OptionsCanvas::resolutionSetup() {
	resolutionlabeltext = "Resolution: ";
	resolutions[0] = "1920x1200";
	resolutions[1] = "1920x1080";
	resolutions[2] = "1600x900";
	resbackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	resforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");

	selectedresolution = root->getResolution();
	reslabelh = root->menutitlefont.getStringHeight("y");
	reslabelx = containerx + containerw / 10;
	reslabely = (containery + containerh / 15 + reslabelh) + 300;
	resolutionsw = root->menutitlefont.getStringWidth(resolutions[selectedresolution]);
	resolutionsx = reslabelx + resolutionsw * 2;
	resolutionsh = root->menutitlefont.getStringHeight(resolutions[selectedresolution]);
	resbackbuttonw = resbackbutton.getWidth() * 0.4;
	resbackbuttonh = resbackbutton.getHeight() * 0.4;
	resbackbuttonx = resolutionsx - resbackbuttonw;
	resbackbuttony = reslabely - (resolutionsh / 2) - (resbackbuttonh / 2) + 3;
	resforwardbuttonx = resolutionsx + resolutionsw + (resbackbuttonw / 2);
	resbackbuttonhitbox.set(resbackbuttonx, resbackbuttony, resbackbuttonx + resbackbuttonw, resbackbuttony + resbackbuttonh);
	resforwardbuttonhitbox.set(resforwardbuttonx, resbackbuttony, resforwardbuttonx + resbackbuttonw, resbackbuttony + resbackbuttonh);
}

void OptionsCanvas::brightnessDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(brightlabeltext, brightlabelx, brightlabely);

	if(brightbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(brightbackstate == BUTTON_PRESSED || brightbackstate == BUTTON_PERFORMED) setColor(pressedcolor);
	brightbackbutton.draw(brightbackbuttonx, brightbackbuttony, brightbackbuttonw, brightbackbuttonh);

	setColor(0, 0, 0);
	if(brightfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(brightfwstate == BUTTON_PRESSED || brightfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
	brightforwardbutton.draw(brightforwardbuttonx, brightbackbuttony, brightbackbuttonw, brightbackbuttonh);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(brightnumtext, brightx, brightlabely);
}

void OptionsCanvas::qualityDraw() {

	setColor(0, 0, 0);
	root->menutitlefont.drawText(qualitylabeltext, qualabelx, qualabely);
	root->menutitlefont.drawText(qualities[selectedquality], qualitiesx, qualabely);
	quabackbutton.draw(quabackbuttonx, quabackbuttony, quabackbuttonw, quabackbuttonh);
	quaforwardbutton.draw(quaforwardbuttonx, quabackbuttony, quabackbuttonw, quabackbuttonh);

	if(quabackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(quabackstate == BUTTON_PRESSED || quabackstate == BUTTON_PERFORMED) setColor(pressedcolor);

	if(quafwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(quafwstate == BUTTON_PRESSED || quafwstate == BUTTON_PERFORMED) setColor(pressedcolor);
}

void OptionsCanvas::windowmodeDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(windowmodelabeltext, winlabelx, winlabely);
	root->menutitlefont.drawText(windowmodes[selectedwindowmode], windowmodesx, winlabely);
	winbackbutton.draw(winbackbuttonx, winbackbuttony, winbackbuttonw, winbackbuttonh);
	winforwardbutton.draw(winforwardbuttonx, winbackbuttony, winbackbuttonw, winbackbuttonh);

	if(winbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(winbackstate == BUTTON_PRESSED || winbackstate == BUTTON_PERFORMED) setColor(pressedcolor);

	if(winfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(winfwstate == BUTTON_PRESSED || winfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
}

void OptionsCanvas::resolutionDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(resolutionlabeltext, reslabelx, reslabely);
	root->menutitlefont.drawText(resolutions[selectedresolution], resolutionsx, reslabely);
	resbackbutton.draw(resbackbuttonx, resbackbuttony, resbackbuttonw, resbackbuttonh);
	resforwardbutton.draw(resforwardbuttonx, resbackbuttony, resbackbuttonw, resbackbuttonh);

	if(resbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(resbackstate == BUTTON_PRESSED || winbackstate == BUTTON_PERFORMED) setColor(pressedcolor);

	if(resfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(resfwstate == BUTTON_PRESSED || resfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
}

void OptionsCanvas::musicSetup() {
	musicbackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	musicforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");

	musicvalue = root->getMusicVolume();
	musicnumtext = gToStr(musicvalue);
	musiclabeltext = "Music Value";
	musiclabelh = root->menutitlefont.getStringHeight("y");
	musiclabelx = containerx + containerw / 10;
	musiclabely = containery + containerh / 15 + musiclabelh;
	musicw = root->menutitlefont.getStringWidth(musicnumtext);
	musicx = musiclabelx + root->menutitlefont.getStringWidth(musiclabeltext) + 40;
	musich = root->menutitlefont.getStringHeight(musicnumtext);
	musicbackbuttonw = musicbackbutton.getWidth() * 0.4;
	musicbackbuttonh = musicbackbutton.getHeight() * 0.4;
	musicbackbuttonx = musicx - musicbackbuttonw - 10;
	musicbackbuttony = musiclabely - (musich / 2) - (musicbackbuttonh / 2) +  3;
	musicforwardbuttonx = musicx + musicw + 10;
	musicbackbuttonhitbox.set(musicbackbuttonx, musicbackbuttony, musicbackbuttonx + musicbackbuttonw, musicbackbuttony + musicbackbuttonh);
	musicforwardbuttonhitbox.set(musicforwardbuttonx, musicbackbuttony, musicforwardbuttonx + musicbackbuttonw, musicbackbuttony + musicbackbuttonh);
}

void OptionsCanvas::fxSetup() {
	fxbackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	fxforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");

	effectvalue = root->getSoundVolume();
	fxnumtext = gToStr(effectvalue);
	fxlabeltext = "Effect Value";
	fxlabelh = root->menutitlefont.getStringHeight("y");
	fxlabelx = containerx + containerw / 10;
	fxlabely = containery + containerh / 15 + fxlabelh + 100;
	fxw = root->menutitlefont.getStringWidth(fxnumtext);
	fxx = fxlabelx + root->menutitlefont.getStringWidth(fxlabeltext) + 40;
	fxh = root->menutitlefont.getStringHeight(fxnumtext);
	fxbackbuttonw = fxbackbutton.getWidth() * 0.4;
	fxbackbuttonh = fxbackbutton.getHeight() * 0.4;
	fxbackbuttonx = fxx - fxbackbuttonw - 10;
	fxbackbuttony = fxlabely - (fxh / 2) - (fxbackbuttonh / 2) +  3;
	fxforwardbuttonx = fxx + fxw + 10;
	fxbackbuttonhitbox.set(fxbackbuttonx, fxbackbuttony, fxbackbuttonx + fxbackbuttonw, fxbackbuttony + fxbackbuttonh);
	fxforwardbuttonhitbox.set(fxforwardbuttonx, fxbackbuttony, fxforwardbuttonx + fxbackbuttonw, fxbackbuttony + fxbackbuttonh);
}

void OptionsCanvas::musicDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(musiclabeltext, musiclabelx, musiclabely);

	if(musicbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(musicbackstate == BUTTON_PRESSED || musicbackstate == BUTTON_PERFORMED) setColor(pressedcolor);
	musicbackbutton.draw(musicbackbuttonx, musicbackbuttony, musicbackbuttonw, musicbackbuttonh);

	setColor(0, 0, 0);
	if(musicfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(musicfwstate == BUTTON_PRESSED || musicfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
	musicforwardbutton.draw(musicforwardbuttonx, musicbackbuttony, musicbackbuttonw, musicbackbuttonh);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(musicnumtext, musicx, musiclabely);
}

void OptionsCanvas::fxDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(fxlabeltext, fxlabelx, fxlabely);

	if(fxbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(fxbackstate == BUTTON_PRESSED || fxbackstate == BUTTON_PERFORMED) setColor(pressedcolor);
	fxbackbutton.draw(fxbackbuttonx, fxbackbuttony, fxbackbuttonw, fxbackbuttonh);

	setColor(0, 0, 0);
	if(fxfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(fxfwstate == BUTTON_PRESSED || fxfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
	fxforwardbutton.draw(fxforwardbuttonx, fxbackbuttony, fxbackbuttonw, fxbackbuttonh);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(fxnumtext, fxx, fxlabely);
}

void OptionsCanvas::musictickSetup() {
	musictext = "Music";
	musicuncheck.loadImage("PNG/inactivecolor.png");
	musiccheck.loadImage("PNG/check-markred.png");
	musictextw = root->menutitlefont.getStringWidth(musictext);
	musictexth = root->menutitlefont.getStringHeight(musictext);
	musictextx = fxlabelx;
	musictexty = fxlabely + 100;
	musicuncheckw = musicuncheck.getWidth();
	musicuncheckh = musicuncheck.getHeight();
	musicuncheckx = musictextx + 150;
	musicunchecky = musictexty - (musictexth / 2) - (musicuncheckh / 2) + 3;
	musiccheckw = musiccheck.getWidth() * 0.06;
	musiccheckh = musiccheck.getHeight() * 0.06;
	musicbuttonhitbox.set(musicuncheckx, musicunchecky, musicuncheckx + musicuncheckw, musicunchecky + musicuncheckh);
	ismusicenabled = root->getMusic();
}

void OptionsCanvas::fxtickSetup() {
	fxtext = "FX Sound";
	fxuncheck.loadImage("PNG/inactivecolor.png");
	fxcheck.loadImage("PNG/check-markred.png");
	fxtextw = root->menutitlefont.getStringWidth(fxtext);
	fxtexth = root->menutitlefont.getStringHeight(fxtext);
	fxtextx = fxlabelx;
	fxtexty = fxlabely + 200;
	fxuncheckw = fxuncheck.getWidth();
	fxuncheckh = fxuncheck.getHeight();
	fxuncheckx = fxtextx + 150;
	fxunchecky = fxtexty - (fxtexth / 2) - (fxuncheckh / 2) + 3;
	fxcheckw = fxcheck.getWidth() * 0.06;
	fxcheckh = fxcheck.getHeight() * 0.06;
	fxbuttonhitbox.set(fxuncheckx, fxunchecky, fxuncheckx + fxuncheckw, fxunchecky + fxuncheckh);
	isfxenabled = root->getSound();
}

void OptionsCanvas::musictickDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(musictext, musictextx, musictexty);
	musicuncheck.draw(musicuncheckx, musicunchecky);
	if(ismusicenabled) {
		setColor(255, 255, 255);
		musiccheck.draw(musicuncheckx, musicunchecky, musiccheckw, musiccheckh);
	}
	setColor(0, 0, 0);
}

void OptionsCanvas::fxtickDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(fxtext, fxtextx, fxtexty);
	fxuncheck.draw(fxuncheckx, fxunchecky);
	if(isfxenabled) {
		setColor(255, 255, 255);
		fxcheck.draw(fxuncheckx, fxunchecky, fxcheckw, fxcheckh);
	}
	setColor(0, 0, 0);
}

void OptionsCanvas::applyGameSettings() {
	root->saveGameSettings(selectedlanguage, isminimapenabled, isfpsenabled, isvsyncenabled);
	root->applyGameSettings();
	tabSetup();
	containerSetup();
}

void OptionsCanvas::resetGameSettings() {
	root->resetGameSettings();
	selectedlanguage = root->getLanguage();
	isminimapenabled = root->getMinimap();
	isfpsenabled = root->getShowFps();
	isvsyncenabled = root->getVsync();
}

void OptionsCanvas::applyControlsSettings() {
	root->saveControlsSettings(keyboardcontrols[KEY_FORWARD], keyboardcontrols[KEY_BACKWARD], keyboardcontrols[KEY_RIGHT],
	keyboardcontrols[KEY_LEFT], keyboardcontrols[KEY_RUN], keyboardcontrols[KEY_FIRE], keyboardcontrols[KEY_INTERACT], sensitivity);
	root->applyControlsSettings();
}

void OptionsCanvas::resetControlsSettings() {
	root->resetControlsSettings();
	keyboardcontrols[KEY_FORWARD] = root->getForwardKey();
	keyboardcontrols[KEY_BACKWARD] = root->getBackwardKey() ;
	keyboardcontrols[KEY_RIGHT] = root->getRightKey();
	keyboardcontrols[KEY_LEFT] = root->getLeftKey();
	keyboardcontrols[KEY_RUN] = root->getRunKey();
	keyboardcontrols[KEY_FIRE] = root->getFireKey();
	keyboardcontrols[KEY_INTERACT] = root->getInteractKey();
	sensitivity = root->getSensitivity();
}

void OptionsCanvas::applyGraphicsSettings() {
	root->saveGraphicsSettings(brightness, selectedresolution, selectedwindowmode, selectedquality);
	root->applyGraphicsSettings();
	tabSetup();
	containerSetup();
}

void OptionsCanvas::resetGraphicsSettings() {
	root->resetGraphicsSettings();
	brightness = root->getBrightness();
	selectedresolution = root->getResolution();
	selectedwindowmode = root->getWindowMode();
	selectedquality = root->getQuality();
}

void OptionsCanvas::applyAudioSettings() {
	root->saveAudioSettings(effectvalue, musicvalue, isfxenabled, ismusicenabled);
	root->applyAudioSettings();
}

void OptionsCanvas::resetAudioSettings() {
	root->resetAudioSettings();
	effectvalue = root->getSoundVolume();
	musicvalue = root->getMusicVolume();
	isfxenabled = root->getSound();
	ismusicenabled = root->getMusic();
}

