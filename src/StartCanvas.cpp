/*
 * StartCanvas.cpp
 *
 *  Created on: 13 Nis 2026
 *      Author: Engin
 */

#include <StartCanvas.h>
#include "gBaseCanvas.h"
#include "gApp.h"
#include "MainMenu.h"
#include "gFont.h"
#include "gImage.h"
#include "gFont.h"

StartCanvas::StartCanvas(gApp* root): gBaseCanvas(root) {
	this->root = root;
}

StartCanvas::~StartCanvas() {
	// TODO Auto-generated destructor stub
}

void StartCanvas::setup() {
	colorSetup();
	returnSetup();
}

void StartCanvas::update() {

}

void StartCanvas::draw() {
	returnDraw();
}

void StartCanvas::returnSetup() {
	returntext = root->localizeWord(root->returnkey);
	returnh = root->menutitlefont.getStringHeight(returntext);
	returnw = root->menutitlefont.getStringWidth(returntext);
	returnx = getWidth() * 5/100;
	returny = getHeight() * 95/100;

	returnhitbox.set(returnx, returny - returnh, returnx + returnw, returny);
	returnbuttonstate = BUTTON_NONE;
}
void StartCanvas::returnDraw() {
	setColor(255, 255, 255, 255);
	if(returnbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(returnbuttonstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(returntext, returnx, returny);
	setColor(255, 255, 255);
}

void StartCanvas::updateButtonState(int x, int y) {
	if(returnbuttonstate != BUTTON_PRESSED) {
		if(returnhitbox.contains(x, y)) {
			returnbuttonstate = BUTTON_FOCUS;
		}
		else {
			returnbuttonstate = BUTTON_NONE;
		}
	}
}

void StartCanvas::checkButtonPressed(int x, int y, int button) {
	if(returnhitbox.contains(x, y)) {
		returnbuttonstate = BUTTON_PRESSED;
		returny += 2;
	}
}

void StartCanvas::checkButtonReleased(int x, int y, int button) {
	if(returnhitbox.contains(x, y) && returnbuttonstate == BUTTON_PRESSED) {
		returnbuttonstate = BUTTON_PERFORMED;
		returny -= 2;
		//root->gamestate = root->GAME_LOAD;
		root->setCurrentCanvas(new mainMenu(root));
	}
}

void StartCanvas::colorSetup() {
	pressedcolor.set(190, 190, 190);
	normalcolor.set(255, 255, 255);
	focuscolor.set(200, 200, 200);
}

void StartCanvas::keyPressed(int key) {
//	gLogi("StartCanvas") << "keyPressed:" << key;
}

void StartCanvas::keyReleased(int key) {
//	gLogi("StartCanvas") << "keyReleased:" << key;
}

void StartCanvas::charPressed(unsigned int codepoint) {
//	gLogi("StartCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void StartCanvas::mouseMoved(int x, int y) {
//	gLogi("StartCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
	updateButtonState(x, y);
}

void StartCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("StartCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void StartCanvas::mousePressed(int x, int y, int button) {
//	gLogi("StartCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	checkButtonPressed(x, y, button);
}

void StartCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("StartCanvas") << "mouseReleased" << ", button:" << button;
	checkButtonReleased(x, y, button);
}

void StartCanvas::mouseScrolled(int x, int y) {
//	gLogi("StartCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void StartCanvas::mouseEntered() {

}

void StartCanvas::mouseExited() {

}

void StartCanvas::windowResized(int w, int h) {

}

void StartCanvas::showNotify() {

}

void StartCanvas::hideNotify() {

}
