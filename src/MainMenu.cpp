/*
 * mainMenu.cpp
 *
 *  Created on: 13 Mar 2026
 *      Author: Engin Kutlu
 */

#include "MainMenu.h"
#include "ShopCanvas.h"
#include "gCanvas.h"
#include "StartCanvas.h"
#include "CreditsCanvas.h"
#include "HelpMenu.h"
#include "OptionsCanvas.h"

mainMenu::mainMenu(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

mainMenu::~mainMenu() {
}

void mainMenu::setup() {
	//background.loadImage("black.png");
	logoSetup();
	startSetup();
	offlineSetup();
	shopSetup();
	optionSetup();
	helpSetup();
	creditSetup();
	colorSetup();
	exitSetup();
}

void mainMenu::update() {
}

void mainMenu::draw() {
	backgroundDraw();
	logoDraw();
	startDraw();
	offlineDraw();
	shopDraw();
	optionDraw();
	helpDraw();
	creditDraw();
	exitDraw();
	//fadeEffectDraw();
}

void mainMenu::keyPressed(int key) {
}

void mainMenu::keyReleased(int key) {
	if(key == G_KEY_ESC) exit(0);
}

void mainMenu::charPressed(unsigned int codepoint) {
}

void mainMenu::mouseMoved(int x, int y) {
	//	gLogi("mainMenu") << "mouseMoved" << ", x:" << x << ", y:" << y;
	updateButtonState(x, y);
}

void mainMenu::mouseDragged(int x, int y, int button) {
	//	gLogi("mainMenu") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void mainMenu::mousePressed(int x, int y, int button) {
	//	gLogi("mainMenu") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	checkButtonPressed(x, y, button);
}

void mainMenu::mouseReleased(int x, int y, int button) {
	//	gLogi("mainMenu") << "mouseReleased" << ", button:" << button;
	checkButtonReleased(x, y, button);
}

void mainMenu::mouseScrolled(int x, int y) {
}

void mainMenu::mouseEntered() {
}

void mainMenu::mouseExited() {
}

void mainMenu::windowResized(int w, int h) {
}

void mainMenu::showNotify() {
}

void mainMenu::hideNotify() {
}

void mainMenu::backgroundDraw() {
	root->drawMenuBackground(getWidth(), getHeight());
	setColor(165, 55, 55);
	root->menutitlefont.drawText(root->titlekey, titlex, titley);
	setColor(255, 255, 255);
}

void mainMenu::logoSetup() {
	glistlogo.loadImage("glistengine_logo.png");

	int titlesizer = 10;
	int nitralogosizer = 8;
	int glistlogosizer = 3;
	int padding = 25;

	titlex = getWidth() / titlesizer;
	titley = getHeight() / titlesizer;

	glistlogow = glistlogo.getWidth() / glistlogosizer;
	glistlogoh = glistlogo.getHeight() / glistlogosizer;
	glistlogox = (getWidth() - glistlogow) - padding;
	glistlogoy = (getHeight() - glistlogoh) - padding;

}

void mainMenu::startSetup() {
	starttext = root->localizeWord(root->startkey);
	startw = root->menutitlefont.getStringWidth(starttext);
	starth = root->menutitlefont.getStringHeight(starttext);
	startx = getWidth() / 4;
	starty = getHeight() + 120;
	starthitbox.set(startx, starty - starth, startx + startw, starty);
	startstate = BUTTON_NONE;
}

void mainMenu::offlineSetup() {
	offlinetext = root->localizeWord(root->offlinekey);
	offlinew = root->menutitlefont.getStringWidth(offlinetext);
	offlineh = root->menutitlefont.getStringHeight(offlinetext);
	offlinex = startx + (startw + 60);
	offliney = starty;
	offlinehitbox.set(offlinex, offliney - offlineh, offlinex + offlinew, offliney);
	offlinestate = BUTTON_NONE;
}

void mainMenu::shopSetup(){
	shoptext = root->localizeWord(root->shopkey);
	shopw = root->menutitlefont.getStringWidth(shoptext);
	shoph = root->menutitlefont.getStringHeight(shoptext);
	shopx = offlinex + (offlinew + 60);
	shopy = starty;
	shophitbox.set(shopx, shopy - shoph, shopx + shopw, shopy);
	shopstate = BUTTON_NONE;
}

void mainMenu::optionSetup() {
	optiontext = root->localizeWord(root->optionskey);
	optionw = root->menutitlefont.getStringWidth(optiontext);
	optionh = root->menutitlefont.getStringHeight(optiontext);
	optionx = shopx + (shopw + 60);
	optiony = starty;
	optionhitbox.set(optionx, optiony - optionh, optionx + optionw, optiony);
	optionstate = BUTTON_NONE;
}

void mainMenu::helpSetup() {
	helptext = root->localizeWord(root->helpkey);
	helpw = root->menutitlefont.getStringWidth(helptext);
	helph = root->menutitlefont.getStringHeight(helptext);
	helpx = optionx + (optionw + 60);
	helpy = starty;
	helphitbox.set(helpx, helpy - helph, helpx + helpw, helpy);
	helpstate = BUTTON_NONE;
}

void mainMenu::creditSetup() {
	credittext = root->localizeWord(root->creditskey);
	creditw = root->menutitlefont.getStringWidth(credittext);
	credith = root->menutitlefont.getStringHeight(credittext);
	creditx = helpx + (helpw + 60);
	credity = starty;
	credithitbox.set(creditx, credity - credith, creditx + creditw, credity);
	creditstate = BUTTON_NONE;
}

void mainMenu::exitSetup() {
	exittext = root->localizeWord(root->exitkey);
	exitw = root->menutitlefont.getStringWidth(exittext);
	exith = root->menutitlefont.getStringHeight(exittext);
	exitx = creditx + (creditw + 60);
	exity = starty;
	exithitbox.set(exitx, exity - exith, exitx + exitw, exity);
	exitstate = BUTTON_NONE;
}

void mainMenu::colorSetup() {
	pressedcolor.set(190, 190, 190);
	normalcolor.set(255, 255, 255);
	focuscolor.set(200, 200, 200);
}

/*void mainMenu::backgroundDraw() {
	background.draw(getWidth(), getHeight());
	setColor(165, 55, 55);
	menutitlefont.drawText("TANKS", titlex, titley);
	setColor(255, 255, 255);
}*/

void mainMenu::logoDraw() {
	glistlogo.draw(glistlogox, glistlogoy, glistlogow, glistlogoh);
}

void mainMenu::offlineDraw() {
	if(offlinestate == BUTTON_FOCUS) setColor(focuscolor);
	if(offlinestate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(offlinetext, offlinex, offliney);
	setColor(normalcolor);
}

void mainMenu::startDraw() {
	//if (gamestate != gApp::GAME_PAUSE) return;
	if(startstate == BUTTON_FOCUS) setColor(focuscolor);
	if(startstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(starttext, startx, starty);
	setColor(normalcolor);
}

void mainMenu::shopDraw(){
	if(shopstate == BUTTON_FOCUS) setColor(focuscolor);
	if(shopstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(shoptext, shopx, shopy);
	setColor(normalcolor);
}

void mainMenu::optionDraw() {
	if(optionstate == BUTTON_FOCUS) setColor(focuscolor);
	if(optionstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(optiontext, optionx, optiony);
	setColor(normalcolor);
}

void mainMenu::helpDraw() {
	if(helpstate == BUTTON_FOCUS) setColor(focuscolor);
	if(helpstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(helptext, helpx, helpy);
	setColor(normalcolor);
}

void mainMenu::creditDraw() {
	if(creditstate == BUTTON_FOCUS) setColor(focuscolor);
	if(creditstate == BUTTON_PRESSED) {
		setColor(pressedcolor);
	}
	root->menutitlefont.drawText(credittext, creditx, credity);
	setColor(normalcolor);
}

void mainMenu::exitDraw() {
	if(exitstate == BUTTON_FOCUS) setColor(focuscolor);
	if(exitstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(exittext, exitx, exity);
	setColor(normalcolor);
}

void mainMenu::fadeEffectDraw() {
	//if(fadeeffect->isDrawing()) fadeeffect->drawFadeEffect();
}

void mainMenu::updateButtonState(int x, int y) {
	if(startstate != BUTTON_PRESSED) {
		if(starthitbox.contains(x, y)) {
			startstate = BUTTON_FOCUS;
		}
		else {
			startstate = BUTTON_NONE;
		}
	}
	if(offlinestate != BUTTON_PRESSED) {
		if(offlinehitbox.contains(x, y)) {
			offlinestate = BUTTON_FOCUS;
		}
		else {
			offlinestate = BUTTON_NONE;
		}
	}
	if(shopstate != BUTTON_PRESSED) {
		if(shophitbox.contains(x, y)) {
			shopstate = BUTTON_FOCUS;
		}
		else {
			shopstate = BUTTON_NONE;
		}
	}
	if(optionstate != BUTTON_PRESSED) {
		if(optionhitbox.contains(x, y)) {
			optionstate = BUTTON_FOCUS;
		}
		else {
			optionstate = BUTTON_NONE;
		}
	}
	if(creditstate != BUTTON_PRESSED) {
		if(credithitbox.contains(x, y)) {
			creditstate = BUTTON_FOCUS;
		}
		else {
			creditstate = BUTTON_NONE;
		}
	}
	if(exitstate != BUTTON_PRESSED) {
		if(exithitbox.contains(x, y)) {
			exitstate = BUTTON_FOCUS;
		}
		else {
			exitstate = BUTTON_NONE;
		}
	}

    if(helpstate != BUTTON_PRESSED) {
        if(helphitbox.contains(x, y)) {
            helpstate = BUTTON_FOCUS;
        }
        else {
            helpstate = BUTTON_NONE;
        }
    }
}

void mainMenu::checkButtonPressed(int x, int y, int button) {
	if(starthitbox.contains(x, y)) {
		startstate = BUTTON_PRESSED;
		starty += 2;
	}

	if(offlinehitbox.contains(x, y)) {
		offlinestate = BUTTON_PRESSED;
		offliney += 2;
	}

	if(shophitbox.contains(x, y)) {
		shopstate = BUTTON_PRESSED;
		shopy += 2;
	}

	if(optionhitbox.contains(x, y)) {
		optionstate = BUTTON_PRESSED;
		optiony += 2;
	}

	if(credithitbox.contains(x, y)) {
		creditstate = BUTTON_PRESSED;
		credity += 2;
	}

	if(exithitbox.contains(x, y)) {
		exitstate = BUTTON_PRESSED;
		exity += 2;
	}

	if(helphitbox.contains(x, y)) {
		helpstate = BUTTON_PRESSED;
		helpy += 2;
	}
}

void mainMenu::checkButtonReleased(int x, int y, int button) {
	if(starthitbox.contains(x, y) && startstate == BUTTON_PRESSED) {
		startstate = BUTTON_PERFORMED;
		starty -= 2;
		//root->gamestate = root->GAME_LOAD;
		root->setCurrentCanvas(new StartCanvas(root));
	}

	else if(offlinehitbox.contains(x, y) && offlinestate == BUTTON_PRESSED) {
		offlinestate = BUTTON_PERFORMED;
		offliney -= 2;
		root->setCurrentCanvas(new gCanvas(root));
	}

	else if(shophitbox.contains(x, y) && shopstate == BUTTON_PRESSED) {
		shopstate = BUTTON_PERFORMED;
		shopy -= 2;
		root->setCurrentCanvas(new ShopCanvas(root));
	}

	else if(optionhitbox.contains(x, y) && optionstate == BUTTON_PRESSED) {
		optionstate = BUTTON_PERFORMED;
		optiony -=2;
		root->setCurrentCanvas(new OptionsCanvas(root));
	}

	else if(credithitbox.contains(x, y) && creditstate == BUTTON_PRESSED) {
		creditstate = BUTTON_PERFORMED;
		credity -= 2;
		root->setCurrentCanvas(new CreditsCanvas(root));
	}

	else if(exithitbox.contains(x, y) && exitstate == BUTTON_PRESSED) {
		exitstate = BUTTON_PERFORMED;
		exity -= 2;
		exit(0);
		}
	else if(helphitbox.contains(x,y) && helpstate == BUTTON_PRESSED) {
		helpstate = BUTTON_PERFORMED;
		helpy -= 2;
		if(helphitbox.contains(x, y)) {
			root->setCurrentCanvas(new HelpMenu(root));
		}
	}

	else {
		startstate = BUTTON_CANCELED;
		offlinestate = BUTTON_CANCELED;
		shopstate = BUTTON_CANCELED;
		optionstate = BUTTON_CANCELED;
		creditstate = BUTTON_CANCELED;
		exitstate = BUTTON_CANCELED;
		helpstate = BUTTON_CANCELED;
	}
}
