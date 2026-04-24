/*
 * HelpMenu.cpp
 *
 *  Created on: 13 Nis 2026
 *      Author: Engin Kutlu
 */


#include "HelpMenu.h"
#include "gCanvas.h"
#include "MainMenu.h"

HelpMenu::HelpMenu(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

HelpMenu::~HelpMenu() {
}

void HelpMenu::setup() {
	tabSetup();
	containerSetup();
	forwardButtonSetup();
	backButtonSetup();
	leveltabtext = "HELLO WORLD";
	activetab = TAB_GENERAL;
}

void HelpMenu::update() {
}

void HelpMenu::draw() {
	root->drawMenuBackground(getWidth(), getHeight());
	tabDraw();
	containerDraw();
	forwardButtonDraw();
	backButtonDraw();
}

void HelpMenu::keyPressed(int key) {
	//	gLogi("HelpMenu") << "keyPressed:" << key;
}

void HelpMenu::keyReleased(int key) {
	//	gLogi("HelpMenu") << "keyReleased:" << key;
	if(key == G_KEY_ESC) {
		root->setCurrentCanvas(new mainMenu(root));
	}
	if(ischangingkey) {
		keyboardcontrols[selectedkey] = key;
		ischangingkey = false;
		controlsdisplaytext[selectedkey] = gCodepointToStr(key);
	}
}

void HelpMenu::charPressed(unsigned int codepoint) {
	//	gLogi("HelpMenu") << "charPressed:" << gCodepointToStr(codepoint);
}

void HelpMenu::mouseMoved(int x, int y) {
	//	gLogi("HelpMenu") << "mouseMoved" << ", x:" << x << ", y:" << y;
	tabButtonFocus(x, y);
	containerButtonFocus(x, y);
}

void HelpMenu::mouseDragged(int x, int y, int button) {
	//	gLogi("HelpMenu") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void HelpMenu::mousePressed(int x, int y, int button) {
	//	gLogi("HelpMenu") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	tabButtonPressed(x, y);
	containerButtonPressed(x, y);
}

void HelpMenu::mouseReleased(int x, int y, int button) {
	//	gLogi("HelpMenu") << "mouseReleased" << ", button:" << button;
	tabButtonReleased(x, y);
	containerButtonReleased(x, y);
}

void HelpMenu::mouseScrolled(int x, int y) {
	//	gLogi("HelpMenu") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void HelpMenu::mouseEntered() {

}

void HelpMenu::mouseExited() {

}

void HelpMenu::windowResized(int w, int h) {

}

void HelpMenu::showNotify() {

}

void HelpMenu::hideNotify() {

}

void HelpMenu::tabSetup() {
	tabw = getWidth() / 2;
	tabh = getHeight() / 10;
	tabx = (getWidth() - tabw) / 2;
	taby = tabh;
	tabcolor.set(54, 126, 127);
	normalcolor.set(45, 50, 70);
	pressedcolor.set(65, 70, 90);
	focuscolor.set(55, 60, 80);
	//generalTabSetup();
	//levelTabSetup();
	//itemsTabSetup();
	//controlsTabSetup();
	returnSetup();

	activetab = TAB_GENERAL;
}

void HelpMenu::tabDraw() {
	setColor(tabcolor);
	gDrawRectangle(tabx, taby, tabw, tabh, true);
	setColor(normalcolor);
	tabtitle = getTabTitle();
	tabtextw = root->menutitlefont.getStringWidth(tabtitle);
	tabtexth = root->menutitlefont.getStringHeight(tabtitle);

	tabtextx = tabx + (tabw - tabtextw) / 2;
	tabtexty = taby + (tabh + tabtexth) / 2;

	setColor(0, 0, 0);
	root->menutitlefont.drawText(tabtitle, tabtextx, tabtexty);
	setColor(normalcolor);

	returnDraw();
}

void HelpMenu::tabButtonPressed(int x, int y) {
	if(returnhitbox.contains(x, y)) {
		returnbuttonstate = BUTTON_PRESSED;
		returny += 2;
	}
	if(forwardbutton.contains(x, y)) {
		forwardstate = BUTTON_PRESSED;
	}
	if(backbutton.contains(x, y)) {
		backstate = BUTTON_PRESSED;
	}
}

void HelpMenu::tabButtonReleased(int x, int y) {
    if(returnhitbox.contains(x, y) && returnbuttonstate == BUTTON_PRESSED) {
		returnbuttonstate = BUTTON_PERFORMED;
		returny -= 2;
		//root->gamestate = root->GAME_LOAD;
		root->setCurrentCanvas(new mainMenu(root));
	}

	else if(forwardbutton.contains(x, y) && forwardstate == BUTTON_PRESSED && activetab < TAB_CONTROLS) {
		forwardstate = BUTTON_PERFORMED;
		activetab += 1;
		activeposx += 40;
	}

	else if(backbutton.contains(x, y) && backstate == BUTTON_PRESSED && activetab > TAB_GENERAL) {
		backstate = BUTTON_PERFORMED;
		activetab -= 1;
		activeposx -= 40;
	}

	else {
		returnbuttonstate = BUTTON_CANCELED;
		forwardstate = BUTTON_CANCELED;
		backstate = BUTTON_CANCELED;
	}
}

void HelpMenu::tabButtonFocus(int x, int y) {
	if(returnbuttonstate != BUTTON_PRESSED) {
		if(returnhitbox.contains(x, y)) {
			returnbuttonstate = BUTTON_FOCUS;
		}
		else {
			returnbuttonstate = BUTTON_NONE;
		}
	}

	if(forwardstate != BUTTON_PRESSED) {
		if(forwardbutton.contains(x, y)) {
			forwardstate = BUTTON_FOCUS;
		}
		else {
			forwardstate = BUTTON_NONE;
		}
	}

	if(backstate != BUTTON_PRESSED) {
		if(backbutton.contains(x, y)) {
			backstate = BUTTON_FOCUS;
		}
		else {
			backstate = BUTTON_NONE;
		}
	}
}

void HelpMenu::containerSetup() {
	containerw = tabw;
	containerh = tabh * 7;
	containerx = tabx;
	containery = taby + tabh;
	containercolor.set(255, 255, 255);
	activepart.loadImage("PNG/activecolor.png");
	inactivepart.loadImage("PNG/inactivecolor.png");
	activew = activepart.getWidth();
	activeh = activepart.getHeight();
	activex = (containerx + containerw / 2) - 80;
	activey = (containery + containerw / 1.25) - activeh;
	activeposx = activex;
	generalSettingsSetup();
	levelSettingsSetup();
	itemsSettingsSetup();
	controlsSettingsSetup();
}

void HelpMenu::generalSettingsSetup() {
	generallabeltext = root->localizeWord(root->generallabelkey);
    generallabellines = root->menutitlefont.wrapSentenceByWidth(generallabeltext, containerw * 0.8f);
    generallabelh = root->menutitlefont.getStringHeight("y");
    generallabelx = containerx + containerw / 10;
    generallabely = containery + containerh / 15 + generallabelh;
}

void HelpMenu::levelSettingsSetup() {

	levelonelabeltext = "Merkez";
	level_picture[0].loadImage("levelonemap.png");
	levelonelabelw = root->menutitlefont.getStringWidth(levelonelabeltext);
	levelonelabelh = root->menutitlefont.getStringHeight(levelonelabeltext);
	levelonelabelx = containerx + containerw / 10;
	levelonelabely = containery + containerh / 10 + levelonelabelh;

	leveltwolabeltext = "Irak";
	level_picture[1].loadImage("iraqmap.png");
	leveltwolabelw = root->menutitlefont.getStringWidth(leveltwolabeltext);
	leveltwolabelh = root->menutitlefont.getStringHeight(leveltwolabeltext);
	leveltwolabelx = containerx + containerw / 10;
	leveltwolabely = levelonelabely + 200;

}

void HelpMenu::itemsSettingsSetup() {
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

	 itemslabeltext[0] = "Zirh";
	 itemslabeltext[1] = "Super Zirh";
	 itemslabeltext[2] = "Kask";
	 itemslabeltext[3] = "Gorunmezlik";
	 itemslabeltext[4] = "Guc";

	 for(int i = 0; i < 5; i++) {
		 logo[i];
		logoh[i];
		logox[i];
		logoy[i];
		itemslabelw[i] = root->menutitlefont.getStringWidth(itemslabeltext[i]);
	    itemslabelh[i] = root->menutitlefont.getStringHeight(itemslabeltext[i]);
	    itemslabelx[i] = containerx + containerw / 10;
	    itemslabely[i] = containery + containerh / 10 + (i * 60);
	 }
}

void HelpMenu::controlsSettingsSetup() {
	ischangingkey = false;

	selectedkey = KEY_NONE;
/*	keyboardcontrols[KEY_FORWARD] = root->getForwardKey();
	keyboardcontrols[KEY_BACKWARD] = root->getBackwardKey();
	keyboardcontrols[KEY_RIGHT] = root->getRightKey();
	keyboardcontrols[KEY_LEFT] = root->getLeftKey();
	keyboardcontrols[KEY_RUN] = root->getRunKey();
	keyboardcontrols[KEY_FIRE] = root->getFireKey();
	keyboardcontrols[KEY_INTERACT] = root->getInteractKey();
*/
	//forward
	controlslabeltext[KEY_FORWARD] = root->localizeWord(root->forwardkey);
	controlsdisplaytext[KEY_FORWARD] = gCodepointToStr(keyboardcontrols[KEY_FORWARD]);
	controlslabelw[KEY_FORWARD] = root->menutitlefont.getStringWidth(controlslabeltext[KEY_FORWARD]);
	controlslabelh[KEY_FORWARD] = root->menutitlefont.getStringHeight(controlslabeltext[KEY_FORWARD]);
	controlslabelx[KEY_FORWARD] = containerx + containerw / 10;
	controlslabely[KEY_FORWARD] = containery + containerh / 15 + controlslabelh[KEY_FORWARD];
	controlsw[KEY_FORWARD] = root->menutitlefont.getStringWidth(controlsdisplaytext[KEY_FORWARD]);
	controlsh[KEY_FORWARD] = root->menutitlefont.getStringHeight(controlsdisplaytext[KEY_FORWARD]);
	controlsx[KEY_FORWARD] = containerx + (containerw / 2) - (containerw / 10) - controlsw[KEY_FORWARD];
	controlsy[KEY_FORWARD] = controlslabely[KEY_FORWARD];

	controlsbutton[KEY_FORWARD].set(controlsx[KEY_FORWARD], controlsy[KEY_FORWARD] - controlsh[KEY_FORWARD], controlsx[KEY_FORWARD] + controlsw[KEY_FORWARD], controlsy[KEY_FORWARD]);

	//backward
	controlslabeltext[KEY_BACKWARD] = root->localizeWord(root->backwardkey);
	controlsdisplaytext[KEY_BACKWARD] = gCodepointToStr(keyboardcontrols[KEY_BACKWARD]);
	controlslabelw[KEY_BACKWARD] = root->menutitlefont.getStringWidth(controlslabeltext[KEY_BACKWARD]);
	controlslabelh[KEY_BACKWARD] = root->menutitlefont.getStringHeight(controlslabeltext[KEY_BACKWARD]);
	controlslabelx[KEY_BACKWARD] = controlslabelx[KEY_FORWARD];
	controlslabely[KEY_BACKWARD] = controlslabely[KEY_FORWARD]  + containerh / 15 + controlslabelh[KEY_BACKWARD];
	controlsw[KEY_BACKWARD] = root->menutitlefont.getStringWidth(controlsdisplaytext[KEY_BACKWARD]);
	controlsh[KEY_BACKWARD] = root->menutitlefont.getStringHeight(controlsdisplaytext[KEY_BACKWARD]);
	controlsx[KEY_BACKWARD] = containerx + (containerw / 2) - (containerw / 10) - controlsw[KEY_BACKWARD];
	controlsy[KEY_BACKWARD] = controlslabely[KEY_BACKWARD];

	controlsbutton[KEY_BACKWARD].set(controlsx[KEY_BACKWARD], controlsy[KEY_BACKWARD] - controlsh[KEY_BACKWARD], controlsx[KEY_BACKWARD] + controlsw[KEY_BACKWARD], controlsy[KEY_BACKWARD]);

	//right
	controlslabeltext[KEY_RIGHT] = root->localizeWord(root->rightkey);
	controlsdisplaytext[KEY_RIGHT] = gCodepointToStr(keyboardcontrols[KEY_RIGHT]);
	controlslabelw[KEY_RIGHT] = root->menutitlefont.getStringWidth(controlslabeltext[KEY_RIGHT]);
	controlslabelh[KEY_RIGHT] = root->menutitlefont.getStringHeight(controlslabeltext[KEY_RIGHT]);
	controlslabelx[KEY_RIGHT] = controlslabelx[KEY_FORWARD];
	controlslabely[KEY_RIGHT] = controlslabely[KEY_BACKWARD]  + containerh / 15 + controlslabelh[KEY_RIGHT];
	controlsw[KEY_RIGHT] = root->menutitlefont.getStringWidth(controlsdisplaytext[KEY_RIGHT]);
	controlsh[KEY_RIGHT] = root->menutitlefont.getStringHeight(controlsdisplaytext[KEY_RIGHT]);
	controlsx[KEY_RIGHT] = containerx + (containerw / 2) - (containerw / 10) - controlsw[KEY_RIGHT];
	controlsy[KEY_RIGHT] = controlslabely[KEY_RIGHT];

	controlsbutton[KEY_RIGHT].set(controlsx[KEY_RIGHT], controlsy[KEY_RIGHT] - controlsh[KEY_RIGHT], controlsx[KEY_RIGHT] + controlsw[KEY_RIGHT], controlsy[KEY_RIGHT]);

	//left
	controlslabeltext[KEY_LEFT] = root->localizeWord(root->leftkey);
	controlsdisplaytext[KEY_LEFT] = gCodepointToStr(keyboardcontrols[KEY_LEFT]);
	controlslabelw[KEY_LEFT] = root->menutitlefont.getStringWidth(controlslabeltext[KEY_LEFT]);
	controlslabelh[KEY_LEFT] = root->menutitlefont.getStringHeight(controlslabeltext[KEY_LEFT]);
	controlslabelx[KEY_LEFT] = controlslabelx[KEY_FORWARD];
	controlslabely[KEY_LEFT] = controlslabely[KEY_RIGHT]  + containerh / 15 + controlslabelh[KEY_LEFT];
	controlsw[KEY_LEFT] = root->menutitlefont.getStringWidth(controlsdisplaytext[KEY_LEFT]);
	controlsh[KEY_LEFT] = root->menutitlefont.getStringHeight(controlsdisplaytext[KEY_LEFT]);
	controlsx[KEY_LEFT] = containerx + (containerw / 2) - (containerw / 10) - controlsw[KEY_LEFT];
	controlsy[KEY_LEFT] = controlslabely[KEY_LEFT];

	controlsbutton[KEY_LEFT].set(controlsx[KEY_LEFT], controlsy[KEY_LEFT] - controlsh[KEY_LEFT], controlsx[KEY_LEFT] + controlsw[KEY_LEFT], controlsy[KEY_LEFT]);

	//run
	controlslabeltext[KEY_RUN] = root->localizeWord(root->runkey);
	controlsdisplaytext[KEY_RUN] = gCodepointToStr(keyboardcontrols[KEY_RUN]);
	controlslabelw[KEY_RUN] = root->menutitlefont.getStringWidth(controlslabeltext[KEY_RUN]);
	controlslabelh[KEY_RUN] = root->menutitlefont.getStringHeight(controlslabeltext[KEY_RUN]);
	controlslabelx[KEY_RUN] = containerx + containerw / 2;
	controlslabely[KEY_RUN] = containery  + containerh / 15 + controlslabelh[KEY_RUN];
	controlsw[KEY_RUN] = root->menutitlefont.getStringWidth(controlsdisplaytext[KEY_RUN]);
	controlsh[KEY_RUN] = root->menutitlefont.getStringHeight(controlsdisplaytext[KEY_RUN]);
	controlsx[KEY_RUN] = containerx + containerw - (containerw / 10) - controlsw[KEY_RUN];
	controlsy[KEY_RUN] = controlslabely[KEY_RUN];

	controlsbutton[KEY_RUN].set(controlsx[KEY_RUN], controlsy[KEY_RUN] - controlsh[KEY_RUN], controlsx[KEY_RUN] + controlsw[KEY_RUN], controlsy[KEY_RUN]);

	//fire
	controlslabeltext[KEY_FIRE] = root->localizeWord(root->firekey);
	controlsdisplaytext[KEY_FIRE] = gCodepointToStr(keyboardcontrols[KEY_FIRE]);
	controlslabelw[KEY_FIRE] = root->menutitlefont.getStringWidth(controlslabeltext[KEY_FIRE]);
	controlslabelh[KEY_FIRE] = root->menutitlefont.getStringHeight(controlslabeltext[KEY_FIRE]);
	controlslabelx[KEY_FIRE] = controlslabelx[KEY_RUN];
	controlslabely[KEY_FIRE] = controlslabely[KEY_RUN]  + containerh / 15 + controlslabelh[KEY_FIRE];
	controlsw[KEY_FIRE] = root->menutitlefont.getStringWidth(controlsdisplaytext[KEY_FIRE]);
	controlsh[KEY_FIRE] = root->menutitlefont.getStringHeight(controlsdisplaytext[KEY_FIRE]);
	controlsx[KEY_FIRE] = containerx + containerw - (containerw / 10) - controlsw[KEY_FIRE];
	controlsy[KEY_FIRE] = controlslabely[KEY_FIRE];

	controlsbutton[KEY_FIRE].set(controlsx[KEY_FIRE], controlsy[KEY_FIRE] - controlsh[KEY_FIRE], controlsx[KEY_FIRE] + controlsw[KEY_FIRE], controlsy[KEY_FIRE]);

	//interact
	controlslabeltext[KEY_INTERACT] = root->localizeWord(root->interactkey);
	controlsdisplaytext[KEY_INTERACT] = gCodepointToStr(keyboardcontrols[KEY_INTERACT]);
	controlslabelw[KEY_INTERACT] = root->menutitlefont.getStringWidth(controlslabeltext[KEY_INTERACT]);
	controlslabelh[KEY_INTERACT] = root->menutitlefont.getStringHeight(controlslabeltext[KEY_INTERACT]);
	controlslabelx[KEY_INTERACT] = controlslabelx[KEY_RUN];
	controlslabely[KEY_INTERACT] = controlslabely[KEY_FIRE]  + containerh / 15 + controlslabelh[KEY_INTERACT];
	controlsw[KEY_INTERACT] = root->menutitlefont.getStringWidth(controlsdisplaytext[KEY_INTERACT]);
	controlsh[KEY_INTERACT] = root->menutitlefont.getStringHeight(controlsdisplaytext[KEY_INTERACT]);
	controlsx[KEY_INTERACT] = containerx + containerw - (containerw / 10) - controlsw[KEY_INTERACT];
	controlsy[KEY_INTERACT] = controlslabely[KEY_INTERACT];

	controlsbutton[KEY_INTERACT].set(controlsx[KEY_INTERACT], controlsy[KEY_INTERACT] - controlsh[KEY_INTERACT], controlsx[KEY_INTERACT] + controlsw[KEY_INTERACT], controlsy[KEY_INTERACT]);
}


void HelpMenu::containerDraw() {
	setColor(containercolor);
	gDrawRectangle(containerx, containery, containerw, containerh, true);
	if(activetab == TAB_GENERAL) generalSettingsDraw();
	else if(activetab == TAB_LEVEL) levelSettingsDraw();
	else if(activetab == TAB_ITEMS) itemsSettingsDraw();
	else if(activetab == TAB_CONTROLS) controlsSettingsDraw();
	setColor(255, 255, 255);
	inactivepart.draw(activex, activey, activew, activeh);
	inactivepart.draw(activex + 40, activey, activew, activeh);
	inactivepart.draw(activex + 80, activey, activew, activeh);
	inactivepart.draw(activex + 120, activey, activew, activeh);
	activepart.draw(activeposx, activey, activew, activeh);
	setColor(255, 255, 255);
}

void HelpMenu::generalSettingsDraw() {
	setColor(0, 0, 0);

	float y = generallabely;

	for (const auto& line : generallabellines) {
	    root->menutitlefont.drawText(line, generallabelx, y);
	    y += generallabelh + 10.0f;
	}
}

void HelpMenu::levelSettingsDraw() {
	setColor(0, 0, 0);

	    level_picture[0].draw(levelonelabelx, levelonelabely, 255, 150);
	    root->menutitlefont.drawText(levelonelabeltext, levelonelabelx + 270, levelonelabely + 75);

	    level_picture[1].draw(leveltwolabelx, leveltwolabely, 255, 150);
	    root->menutitlefont.drawText(leveltwolabeltext, leveltwolabelx + 270, leveltwolabely + 75);
}


void HelpMenu::itemsSettingsDraw() {
	setColor(0, 0, 0);
	    for(int i = 0; i < 5; i++) {
	    	logo[0].draw(logox[0], logoy[0], logow[0], logoh[0]);
	    	logo[1].draw(logox[1], logoy[1], logow[1], logoh[1]);
	    	logo[2].draw(logox[2], logoy[2], logow[2], logoh[2]);
	    	logo[3].draw(logox[3], logoy[3], logow[3], logoh[3]);
	    	logo[4].draw(logox[4], logoy[4], logow[4], logoh[4]);

	        root->menutitlefont.drawText(itemslabeltext[i], itemslabelx[i], itemslabely[i]);
	    }
}

void HelpMenu::controlsSettingsDraw() {
	setColor(0, 0, 0);
	root->menutitlefont.drawText(controlslabeltext[KEY_FORWARD], controlslabelx[KEY_FORWARD], controlslabely[KEY_FORWARD] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_FORWARD] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_FORWARD] == BUTTON_PRESSED || controlsbuttonstate[KEY_FORWARD] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controlsdisplaytext[KEY_FORWARD], controlsx[KEY_FORWARD], controlsy[KEY_FORWARD]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controlslabeltext[KEY_BACKWARD], controlslabelx[KEY_BACKWARD], controlslabely[KEY_BACKWARD] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_BACKWARD] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_BACKWARD] == BUTTON_PRESSED || controlsbuttonstate[KEY_BACKWARD] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controlsdisplaytext[KEY_BACKWARD], controlsx[KEY_BACKWARD], controlsy[KEY_BACKWARD]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controlslabeltext[KEY_RIGHT], controlslabelx[KEY_RIGHT], controlslabely[KEY_RIGHT] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_RIGHT] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_RIGHT] == BUTTON_PRESSED || controlsbuttonstate[KEY_RIGHT] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controlsdisplaytext[KEY_RIGHT], controlsx[KEY_RIGHT], controlsy[KEY_RIGHT]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controlslabeltext[KEY_LEFT], controlslabelx[KEY_LEFT], controlslabely[KEY_LEFT] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_LEFT] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_LEFT] == BUTTON_PRESSED || controlsbuttonstate[KEY_LEFT] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controlsdisplaytext[KEY_LEFT], controlsx[KEY_LEFT], controlsy[KEY_LEFT]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controlslabeltext[KEY_RUN], controlslabelx[KEY_RUN], controlslabely[KEY_RUN] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_RUN] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_RUN] == BUTTON_PRESSED || controlsbuttonstate[KEY_RUN] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controlsdisplaytext[KEY_RUN], controlsx[KEY_RUN], controlsy[KEY_RUN]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controlslabeltext[KEY_FIRE], controlslabelx[KEY_FIRE], controlslabely[KEY_FIRE] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_FIRE] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_FIRE] == BUTTON_PRESSED || controlsbuttonstate[KEY_FIRE] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controlsdisplaytext[KEY_FIRE], controlsx[KEY_FIRE], controlsy[KEY_FIRE]);

	setColor(0, 0, 0);
	root->menutitlefont.drawText(controlslabeltext[KEY_INTERACT], controlslabelx[KEY_INTERACT], controlslabely[KEY_INTERACT] );
	setColor(normalcolor);
	if(controlsbuttonstate[KEY_INTERACT] == BUTTON_FOCUS) setColor(focuscolor);
	if(controlsbuttonstate[KEY_INTERACT] == BUTTON_PRESSED || controlsbuttonstate[KEY_INTERACT] == BUTTON_PERFORMED) setColor(pressedcolor);
	root->menutitlefont.drawText(controlsdisplaytext[KEY_INTERACT], controlsx[KEY_INTERACT], controlsy[KEY_INTERACT]);
}

void HelpMenu::containerButtonPressed(int x, int y) {
	if(activetab == TAB_GENERAL) {
		generalSettingsPressed(x, y);
	}
	else if(activetab == TAB_LEVEL) {
		levelSettingsPressed(x, y);
	}
	else if(activetab == TAB_ITEMS) {
		itemsSettingsPressed(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		controlsSettingsPressed(x, y);
	}
}

void HelpMenu::containerButtonReleased(int x, int y) {
	if(activetab == TAB_GENERAL) {
		generalSettingsReleased(x, y);
	}
	else if(activetab == TAB_LEVEL) {
		levelSettingsReleased(x, y);
	}
	else if(activetab == TAB_ITEMS) {
		itemsSettingsReleased(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		controlsSettingsReleased(x, y);
	}
}

void HelpMenu::containerButtonFocus(int x, int y) {
	if(activetab == TAB_GENERAL) {
		generalSettingsFocus(x, y);
	}
	else if(activetab == TAB_LEVEL) {
		levelSettingsFocus(x, y);
	}
	else if(activetab == TAB_ITEMS) {
		itemsSettingsFocus(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		controlsSettingsFocus(x, y);
	}
}

void HelpMenu::generalSettingsPressed(int x, int y) {

}

void HelpMenu::generalSettingsReleased(int x, int y) {

}

void HelpMenu::generalSettingsFocus(int x, int y) {

}

void HelpMenu::levelSettingsPressed(int x, int y) {

}

void HelpMenu::levelSettingsReleased(int x, int y) {

}

void HelpMenu::levelSettingsFocus(int x, int y) {

}

void HelpMenu::itemsSettingsPressed(int x, int y) {

}

void HelpMenu::itemsSettingsReleased(int x, int y) {

}

void HelpMenu::itemsSettingsFocus(int x, int y) {

}

void HelpMenu::controlsSettingsPressed(int x, int y) {

}

void HelpMenu::controlsSettingsReleased(int x, int y) {

}

void HelpMenu::controlsSettingsFocus(int x, int y) {

}

void HelpMenu::returnSetup() {
	returntext = root->localizeWord(root->returnkey);
	returnh = root->menutitlefont.getStringHeight(returntext);
	returnw = root->menutitlefont.getStringWidth(returntext);
	returnx = getWidth() * 5/100;
	returny = getHeight() * 95/100;

	returnhitbox.set(returnx, returny - returnh, returnx + returnw, returny);
	returnbuttonstate = BUTTON_NONE;
}

void HelpMenu::returnDraw() {
	setColor(0, 0, 0);
	if(returnbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(returnbuttonstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(returntext, returnx, returny);
	setColor(0, 0, 0);
}

void HelpMenu::forwardButtonSetup() {
//	generaltabbuttonstate = BUTTON_NONE;
	arrowright.loadImage("PNG/Icons/ArrowsRight2.png");
	forwardbuttonw = arrowright.getWidth();
	forwardbuttonh = arrowright.getHeight();
	forwardbuttonx = (containerx - forwardbuttonw) + containerw + forwardbuttonw;
	forwardbuttony =  containery + (containerh - forwardbuttonh) / 2;
	forwardstate = BUTTON_NONE;
	forwardbutton.set(forwardbuttonx, forwardbuttony, forwardbuttonx + forwardbuttonw, forwardbuttony + forwardbuttonh);
}

void HelpMenu::forwardButtonDraw() {
	if(forwardstate == BUTTON_FOCUS) setColor(focuscolor);
	if(forwardstate == BUTTON_PRESSED || forwardstate == BUTTON_PERFORMED || activetab == TAB_ITEMS) setColor(pressedcolor);
	setColor(0, 0, 0);
	gDrawRectangle(forwardbuttonx, forwardbuttony, forwardbuttonw, forwardbuttonh, true);
	setColor(255, 255, 255);
	arrowright.draw(forwardbuttonx, forwardbuttony, forwardbuttonw, forwardbuttonh);
	setColor(normalcolor);
}

void HelpMenu::backButtonSetup() {
	arrowleft.loadImage("PNG/Icons/ArrowsLeft2.png");
	backbuttonw = arrowleft.getWidth();
	backbuttonh = arrowleft.getHeight();
	backbuttonx = containerx - backbuttonw;
	backbuttony = containery + (containerh - backbuttonh) / 2;
	backstate = BUTTON_NONE;
	backbutton.set(backbuttonx, backbuttony, backbuttonx + backbuttonw, backbuttony + backbuttonh);
}

void HelpMenu::backButtonDraw() {
	if(backstate == BUTTON_FOCUS) setColor(focuscolor);
	if(backstate == BUTTON_PRESSED || backstate == BUTTON_PERFORMED) setColor(pressedcolor);
	setColor(0, 0, 0);
	gDrawRectangle(backbuttonx, backbuttony, backbuttonw, backbuttonh, true);
	setColor(255, 255, 255);
	arrowleft.draw(backbuttonx, backbuttony, backbuttonw, backbuttonh);
	setColor(normalcolor);
}

std::string HelpMenu::getTabTitle() const {
	if(activetab == TAB_GENERAL) return "GENERAL";
	if(activetab == TAB_LEVEL) return "LEVELS";
	if(activetab == TAB_ITEMS) return "ITEMS";
	if(activetab == TAB_CONTROLS) return "CONTROLS";
	return "";
}
