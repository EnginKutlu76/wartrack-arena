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
		activetab = TAB_APPLY;
	}

	else if(resettabbutton.contains(x, y) && resettabbuttonstate == BUTTON_PRESSED) {
		resettabbuttonstate = BUTTON_PERFORMED;
		activetab = TAB_RESET;
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
	languagelabeltext = "Language: ";
	languages[0] = "English";
	languages[1] = "Turkish";
	langbackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	langforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");

	minimaptext = "Minimap";
	muncheck.loadImage("PNG/inactivecolor.png");
	mcheck.loadImage("PNG/check-markred.png");

	fpstext = "Show Fps";
	fpsuncheck.loadImage("PNG/inactivecolor.png");
	fpscheck.loadImage("PNG/check-markred.png");

	selectedlanguage = 0;
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
	isminimapenabled = true;

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
	isfpsenabled = true;
}

void OptionsCanvas::controlsSettingsSetup() {
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
	controllabeltext[KEY_FORWARD] = root->localizeWord(root->forwardkey);
	controldisplaytext[KEY_FORWARD] = gCodepointToStr(keyboardcontrols[KEY_FORWARD]);
	controllabelw[KEY_FORWARD] = root->menutitlefont.getStringWidth(controllabeltext[KEY_FORWARD]);
	controllabelh[KEY_FORWARD] = root->menutitlefont.getStringHeight(controllabeltext[KEY_FORWARD]);
	controllabelx[KEY_FORWARD] = containerx + containerw / 10;
	controllabely[KEY_FORWARD] = containery + containerh / 15 + controllabelh[KEY_FORWARD];
	controlw[KEY_FORWARD] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_FORWARD]);
	controlh[KEY_FORWARD] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_FORWARD]);
	controlx[KEY_FORWARD] = containerx + (containerw / 2) - (containerw / 10) - controlw[KEY_FORWARD];
	controly[KEY_FORWARD] = controllabely[KEY_FORWARD];

	controlbutton[KEY_FORWARD].set(controlx[KEY_FORWARD], controly[KEY_FORWARD] - controlh[KEY_FORWARD], controlx[KEY_FORWARD] + controlw[KEY_FORWARD], controly[KEY_FORWARD]);

	//backward
	controllabeltext[KEY_BACKWARD] = root->localizeWord(root->backwardkey);
	controldisplaytext[KEY_BACKWARD] = gCodepointToStr(keyboardcontrols[KEY_BACKWARD]);
	controllabelw[KEY_BACKWARD] = root->menutitlefont.getStringWidth(controllabeltext[KEY_BACKWARD]);
	controllabelh[KEY_BACKWARD] = root->menutitlefont.getStringHeight(controllabeltext[KEY_BACKWARD]);
	controllabelx[KEY_BACKWARD] = controllabelx[KEY_FORWARD];
	controllabely[KEY_BACKWARD] = controllabely[KEY_FORWARD]  + containerh / 15 + controllabelh[KEY_BACKWARD];
	controlw[KEY_BACKWARD] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_BACKWARD]);
	controlh[KEY_BACKWARD] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_BACKWARD]);
	controlx[KEY_BACKWARD] = containerx + (containerw / 2) - (containerw / 10) - controlw[KEY_BACKWARD];
	controly[KEY_BACKWARD] = controllabely[KEY_BACKWARD];

	controlbutton[KEY_BACKWARD].set(controlx[KEY_BACKWARD], controly[KEY_BACKWARD] - controlh[KEY_BACKWARD], controlx[KEY_BACKWARD] + controlw[KEY_BACKWARD], controly[KEY_BACKWARD]);

	//right
	controllabeltext[KEY_RIGHT] = root->localizeWord(root->rightkey);
	controldisplaytext[KEY_RIGHT] = gCodepointToStr(keyboardcontrols[KEY_RIGHT]);
	controllabelw[KEY_RIGHT] = root->menutitlefont.getStringWidth(controllabeltext[KEY_RIGHT]);
	controllabelh[KEY_RIGHT] = root->menutitlefont.getStringHeight(controllabeltext[KEY_RIGHT]);
	controllabelx[KEY_RIGHT] = controllabelx[KEY_FORWARD];
	controllabely[KEY_RIGHT] = controllabely[KEY_BACKWARD]  + containerh / 15 + controllabelh[KEY_RIGHT];
	controlw[KEY_RIGHT] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_RIGHT]);
	controlh[KEY_RIGHT] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_RIGHT]);
	controlx[KEY_RIGHT] = containerx + (containerw / 2) - (containerw / 10) - controlw[KEY_RIGHT];
	controly[KEY_RIGHT] = controllabely[KEY_RIGHT];

	controlbutton[KEY_RIGHT].set(controlx[KEY_RIGHT], controly[KEY_RIGHT] - controlh[KEY_RIGHT], controlx[KEY_RIGHT] + controlw[KEY_RIGHT], controly[KEY_RIGHT]);

	//left
	controllabeltext[KEY_LEFT] = root->localizeWord(root->leftkey);
	controldisplaytext[KEY_LEFT] = gCodepointToStr(keyboardcontrols[KEY_LEFT]);
	controllabelw[KEY_LEFT] = root->menutitlefont.getStringWidth(controllabeltext[KEY_LEFT]);
	controllabelh[KEY_LEFT] = root->menutitlefont.getStringHeight(controllabeltext[KEY_LEFT]);
	controllabelx[KEY_LEFT] = controllabelx[KEY_FORWARD];
	controllabely[KEY_LEFT] = controllabely[KEY_RIGHT]  + containerh / 15 + controllabelh[KEY_LEFT];
	controlw[KEY_LEFT] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_LEFT]);
	controlh[KEY_LEFT] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_LEFT]);
	controlx[KEY_LEFT] = containerx + (containerw / 2) - (containerw / 10) - controlw[KEY_LEFT];
	controly[KEY_LEFT] = controllabely[KEY_LEFT];

	controlbutton[KEY_LEFT].set(controlx[KEY_LEFT], controly[KEY_LEFT] - controlh[KEY_LEFT], controlx[KEY_LEFT] + controlw[KEY_LEFT], controly[KEY_LEFT]);

	//run
	controllabeltext[KEY_RUN] = root->localizeWord(root->runkey);
	controldisplaytext[KEY_RUN] = gCodepointToStr(keyboardcontrols[KEY_RUN]);
	controllabelw[KEY_RUN] = root->menutitlefont.getStringWidth(controllabeltext[KEY_RUN]);
	controllabelh[KEY_RUN] = root->menutitlefont.getStringHeight(controllabeltext[KEY_RUN]);
	controllabelx[KEY_RUN] = containerx + containerw / 2;
	controllabely[KEY_RUN] = containery  + containerh / 15 + controllabelh[KEY_RUN];
	controlw[KEY_RUN] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_RUN]);
	controlh[KEY_RUN] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_RUN]);
	controlx[KEY_RUN] = containerx + containerw - (containerw / 10) - controlw[KEY_RUN];
	controly[KEY_RUN] = controllabely[KEY_RUN];

	controlbutton[KEY_RUN].set(controlx[KEY_RUN], controly[KEY_RUN] - controlh[KEY_RUN], controlx[KEY_RUN] + controlw[KEY_RUN], controly[KEY_RUN]);

	//fire
	controllabeltext[KEY_FIRE] = root->localizeWord(root->firekey);
	controldisplaytext[KEY_FIRE] = gCodepointToStr(keyboardcontrols[KEY_FIRE]);
	controllabelw[KEY_FIRE] = root->menutitlefont.getStringWidth(controllabeltext[KEY_FIRE]);
	controllabelh[KEY_FIRE] = root->menutitlefont.getStringHeight(controllabeltext[KEY_FIRE]);
	controllabelx[KEY_FIRE] = controllabelx[KEY_RUN];
	controllabely[KEY_FIRE] = controllabely[KEY_RUN]  + containerh / 15 + controllabelh[KEY_FIRE];
	controlw[KEY_FIRE] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_FIRE]);
	controlh[KEY_FIRE] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_FIRE]);
	controlx[KEY_FIRE] = containerx + containerw - (containerw / 10) - controlw[KEY_FIRE];
	controly[KEY_FIRE] = controllabely[KEY_FIRE];

	controlbutton[KEY_FIRE].set(controlx[KEY_FIRE], controly[KEY_FIRE] - controlh[KEY_FIRE], controlx[KEY_FIRE] + controlw[KEY_FIRE], controly[KEY_FIRE]);

	//interact
	controllabeltext[KEY_INTERACT] = root->localizeWord(root->interactkey);
	controldisplaytext[KEY_INTERACT] = gCodepointToStr(keyboardcontrols[KEY_INTERACT]);
	controllabelw[KEY_INTERACT] = root->menutitlefont.getStringWidth(controllabeltext[KEY_INTERACT]);
	controllabelh[KEY_INTERACT] = root->menutitlefont.getStringHeight(controllabeltext[KEY_INTERACT]);
	controllabelx[KEY_INTERACT] = controllabelx[KEY_RUN];
	controllabely[KEY_INTERACT] = controllabely[KEY_FIRE]  + containerh / 15 + controllabelh[KEY_INTERACT];
	controlw[KEY_INTERACT] = root->menutitlefont.getStringWidth(controldisplaytext[KEY_INTERACT]);
	controlh[KEY_INTERACT] = root->menutitlefont.getStringHeight(controldisplaytext[KEY_INTERACT]);
	controlx[KEY_INTERACT] = containerx + containerw - (containerw / 10) - controlw[KEY_INTERACT];
	controly[KEY_INTERACT] = controllabely[KEY_INTERACT];

	controlbutton[KEY_INTERACT].set(controlx[KEY_INTERACT], controly[KEY_INTERACT] - controlh[KEY_INTERACT], controlx[KEY_INTERACT] + controlw[KEY_INTERACT], controly[KEY_INTERACT]);

	sensbackbutton.loadImage("PNG/Icons/ArrowsLeft3.png");
	sensforwardbutton.loadImage("PNG/Icons/ArrowsRight3.png");

	minimaptext = "Minimap";
	muncheck.loadImage("PNG/inactivecolor.png");
	mcheck.loadImage("PNG/check-markred.png");

	fpstext = "Show Fps";
	fpsuncheck.loadImage("PNG/inactivecolor.png");
	fpscheck.loadImage("PNG/check-markred.png");

	sensitivity = 50;
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
	sensbackbuttony = senslabely - (sensh / 2) - (sensbackbuttonh / 2) + 3;
	sensforwardbuttonx = sensx + sensw + 10;
	sensbackbuttonhitbox.set(sensbackbuttonx, sensbackbuttony, sensbackbuttonx + sensbackbuttonw, sensbackbuttony + sensbackbuttonh);
	sensforwardbuttonhitbox.set(sensforwardbuttonx, sensbackbuttony, sensforwardbuttonx + sensbackbuttonw, sensbackbuttony + sensbackbuttonh);
}

void OptionsCanvas::graphicsSettingsSetup() {
	logo[0].loadImage("armor.png");
	logo[1].loadImage("heavyarmor.png");
	logo[2].loadImage("helmet.png");
	logo[3].loadImage("invisible.png");
	logo[4].loadImage("strength.png");

	logow[0] =  50; logoh[0] = 50; logox[0] = (containerx + containerw / 10) - 50; logoy[0] = (containery + containerh / 10) - 30;
	logow[1] =  50;	logoh[1] = 50; logox[1] = (containerx + containerw / 10) - 50; logoy[1] = (containery + containerh / 10) + 28;
	logow[2] =  50;	logoh[2] = 50; logox[2] = (containerx + containerw / 10) - 50; logoy[2] = (containery + containerh / 10) + 86;
	logow[3] =  50;	logoh[3] = 50; logox[3] = (containerx + containerw / 10) - 50; logoy[3] = (containery + containerh / 10) + 148;
	logow[4] =  50;	logoh[4] = 50; logox[4] = (containerx + containerw / 10) - 50; logoy[4] = (containery + containerh / 10) + 200;

	 graphicslabeltext[0] = "Zirh";
	 graphicslabeltext[1] = "Super Zirh";
	 graphicslabeltext[2] = "Kask";
	 graphicslabeltext[3] = "Gorunmezlik";
	 graphicslabeltext[4] = "Guc";

	 for(int i = 0; i < 5; i++) {
		 logo[i];
		logoh[i];
		logox[i];
		logoy[i];
		graphicslabelw[i] = root->menutitlefont.getStringWidth(graphicslabeltext[i]);
	    graphicslabelh[i] = root->menutitlefont.getStringHeight(graphicslabeltext[i]);
	    graphicslabelx[i] = containerx + containerw / 10;
	    graphicslabely[i] = containery + containerh / 10 + (i * 60);
	 }
}

void OptionsCanvas::audioSettingsSetup() {
}


void OptionsCanvas::containerDraw() {
	setColor(containercolor);
	gDrawRectangle(containerx, containery, containerw, containerh, true);
	if(activetab == TAB_GAME) gameSettingsDraw();
	else if(activetab == TAB_CONTROLS) controlsSettingsDraw();
	else if(activetab == TAB_GRAPHICS) graphicsSettingsDraw();
	else if(activetab == TAB_AUDIO) audioSettingsDraw();
	setColor(255, 255, 255);
	setColor(255, 255, 255);
}

void OptionsCanvas::gameSettingsDraw() {
	setColor(0, 0, 0);

	root->menutitlefont.drawText(languagelabeltext, languagelabelx, languagelabely);
	root->menutitlefont.drawText(languages[selectedlanguage], languagesx, languagelabely);
	langbackbutton.draw(langbackbuttonx, langbackbuttony, langbackbuttonw, langbackbuttonh);
	langforwardbutton.draw(langforwardbuttonx, langbackbuttony, langbackbuttonw, langbackbuttonh);

	root->menutitlefont.drawText(minimaptext, maptextx, maptexty);
	muncheck.draw(muncheckx, munchecky);
	if(isminimapenabled) {
		setColor(255, 255, 255);
	    mcheck.draw(muncheckx, munchecky, mcheckw, mcheckh);
	}

	setColor(0, 0, 0);
	root->menutitlefont.drawText(fpstext, fpstextx, fpstexty);
	fpsuncheck.draw(fpsuncheckx, fpsunchecky);
	if(isfpsenabled) {
		setColor(255, 255, 255);
	    fpscheck.draw(fpsuncheckx, fpsunchecky, fpscheckw, fpscheckh);
	}

	if(langbackstate == BUTTON_FOCUS) setColor(focuscolor);
	if(langbackstate == BUTTON_PRESSED || langbackstate == BUTTON_PERFORMED) setColor(pressedcolor);

	if(langfwstate == BUTTON_FOCUS) setColor(focuscolor);
	if(langfwstate == BUTTON_PRESSED || langfwstate == BUTTON_PERFORMED) setColor(pressedcolor);
}

void OptionsCanvas::controlsSettingsDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_FORWARD], controllabelx[KEY_FORWARD], controllabely[KEY_FORWARD] );
	setColor(normalcolor);
	if(controlbuttonstate[KEY_FORWARD] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlbuttonstate[KEY_FORWARD] == BUTTON_PRESSED || controlbuttonstate[KEY_FORWARD] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_FORWARD], controlx[KEY_FORWARD], controly[KEY_FORWARD]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_BACKWARD], controllabelx[KEY_BACKWARD], controllabely[KEY_BACKWARD] );
	setColor(normalcolor);
	if(controlbuttonstate[KEY_BACKWARD] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlbuttonstate[KEY_BACKWARD] == BUTTON_PRESSED || controlbuttonstate[KEY_BACKWARD] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_BACKWARD], controlx[KEY_BACKWARD], controly[KEY_BACKWARD]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_RIGHT], controllabelx[KEY_RIGHT], controllabely[KEY_RIGHT] );
	setColor(normalcolor);
	if(controlbuttonstate[KEY_RIGHT] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlbuttonstate[KEY_RIGHT] == BUTTON_PRESSED || controlbuttonstate[KEY_RIGHT] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_RIGHT], controlx[KEY_RIGHT], controly[KEY_RIGHT]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_LEFT], controllabelx[KEY_LEFT], controllabely[KEY_LEFT] );
	setColor(normalcolor);
	if(controlbuttonstate[KEY_LEFT] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlbuttonstate[KEY_LEFT] == BUTTON_PRESSED || controlbuttonstate[KEY_LEFT] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_LEFT], controlx[KEY_LEFT], controly[KEY_LEFT]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_RUN], controllabelx[KEY_RUN], controllabely[KEY_RUN] );
	setColor(normalcolor);
	if(controlbuttonstate[KEY_RUN] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlbuttonstate[KEY_RUN] == BUTTON_PRESSED || controlbuttonstate[KEY_RUN] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_RUN], controlx[KEY_RUN], controly[KEY_RUN]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_FIRE], controllabelx[KEY_FIRE], controllabely[KEY_FIRE] );
	setColor(normalcolor);
	if(controlbuttonstate[KEY_FIRE] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlbuttonstate[KEY_FIRE] == BUTTON_PRESSED || controlbuttonstate[KEY_FIRE] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_FIRE], controlx[KEY_FIRE], controly[KEY_FIRE]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controllabeltext[KEY_INTERACT], controllabelx[KEY_INTERACT], controllabely[KEY_INTERACT] );
	setColor(normalcolor);
	if(controlbuttonstate[KEY_INTERACT] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlbuttonstate[KEY_INTERACT] == BUTTON_PRESSED || controlbuttonstate[KEY_INTERACT] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controldisplaytext[KEY_INTERACT], controlx[KEY_INTERACT], controly[KEY_INTERACT]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(senslabeltext, senslabelx, senslabely + 300);
	root->menutitlefont.drawText(sensnumtext, sensx, senslabely + 300);
	sensbackbutton.draw(sensbackbuttonx, sensbackbuttony + 300, sensbackbuttonw, sensbackbuttonh);
	sensforwardbutton.draw(sensforwardbuttonx, sensbackbuttony + 300, sensbackbuttonw, sensbackbuttonh);
}


void OptionsCanvas::graphicsSettingsDraw() {
	setColor(0, 0, 0);
	    for(int i = 0; i < 5; i++) {
	    	logo[0].draw(logox[0], logoy[0], logow[0], logoh[0]);
	    	logo[1].draw(logox[1], logoy[1], logow[1], logoh[1]);
	    	logo[2].draw(logox[2], logoy[2], logow[2], logoh[2]);
	    	logo[3].draw(logox[3], logoy[3], logow[3], logoh[3]);
	    	logo[4].draw(logox[4], logoy[4], logow[4], logoh[4]);

	        root->menutitlefont.drawText(graphicslabeltext[i], graphicslabelx[i], graphicslabely[i]);
	    }
}

void OptionsCanvas::audioSettingsDraw() {
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

	else {
		langbackstate = BUTTON_CANCELED;
		langfwstate = BUTTON_CANCELED;
		maptickstate = BUTTON_CANCELED;
		fpstickstate = BUTTON_CANCELED;
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
}

void OptionsCanvas::controlsSettingsPressed(int x, int y) {
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

void OptionsCanvas::controlsSettingsReleased(int x, int y) {
	if(sensbackbuttonhitbox.contains(x, y) && sensbackstate == BUTTON_PRESSED) {
		sensbackstate = BUTTON_PERFORMED;
		sensitivity += 5;
	}

	else if(sensforwardbuttonhitbox.contains(x, y) && sensfwstate == BUTTON_PRESSED) {
		sensfwstate = BUTTON_PERFORMED;
		sensitivity += 50;
	}

	else {
		sensbackstate = BUTTON_CANCELED;
		sensfwstate = BUTTON_CANCELED;
	}
}

void OptionsCanvas::controlsSettingsFocus(int x, int y) {
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

}

void OptionsCanvas::graphicsSettingsReleased(int x, int y) {

}

void OptionsCanvas::graphicsSettingsFocus(int x, int y) {

}

void OptionsCanvas::audioSettingsPressed(int x, int y) {

}

void OptionsCanvas::audioSettingsReleased(int x, int y) {

}

void OptionsCanvas::audioSettingsFocus(int x, int y) {

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
