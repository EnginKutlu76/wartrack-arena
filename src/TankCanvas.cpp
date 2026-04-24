/*
 * TankCanvas.cpp
 *
 *  Created on: 13 Nis 2026
 *      Author: Engin
 */

#include <TankCanvas.h>
#include "gBaseCanvas.h"
#include "gApp.h"
#include "MainMenu.h"
#include "gFont.h"
#include "gImage.h"
#include "gFont.h"

TankCanvas::TankCanvas(gApp* root): gBaseCanvas(root) {
	this->root = root;
}

TankCanvas::~TankCanvas() {
	// TODO Auto-generated destructor stub
}

void TankCanvas::setup() {
	colorSetup();
	returnSetup();
}

void TankCanvas::update() {

}

void TankCanvas::draw() {
	returnDraw();
}

void TankCanvas::returnSetup() {
	returntext = root->localizeWord(root->returnkey);
	returnh = root->menutitlefont.getStringHeight(returntext);
	returnw = root->menutitlefont.getStringWidth(returntext);
	returnx = getWidth() * 5/100;
	returny = getHeight() * 95/100;

	returnhitbox.set(returnx, returny - returnh, returnx + returnw, returny);
	returnbuttonstate = BUTTON_NONE;
}
void TankCanvas::returnDraw() {
	setColor(255, 255, 255, 255);
	if(returnbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(returnbuttonstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(returntext, returnx, returny);
	setColor(255, 255, 255);
}

void TankCanvas::updateButtonState(int x, int y) {
	if(returnbuttonstate != BUTTON_PRESSED) {
		if(returnhitbox.contains(x, y)) {
			returnbuttonstate = BUTTON_FOCUS;
		}
		else {
			returnbuttonstate = BUTTON_NONE;
		}
	}
}

void TankCanvas::checkButtonPressed(int x, int y, int button) {
	if(returnhitbox.contains(x, y)) {
		returnbuttonstate = BUTTON_PRESSED;
		returny += 2;
	}
}

void TankCanvas::checkButtonReleased(int x, int y, int button) {
	if(returnhitbox.contains(x, y) && returnbuttonstate == BUTTON_PRESSED) {
		returnbuttonstate = BUTTON_PERFORMED;
		returny -= 2;
		//root->gamestate = root->GAME_LOAD;
		root->setCurrentCanvas(new mainMenu(root));
	}
}

void TankCanvas::colorSetup() {
	pressedcolor.set(190, 190, 190);
	normalcolor.set(255, 255, 255);
	focuscolor.set(200, 200, 200);
}

void TankCanvas::keyPressed(int key) {
//	gLogi("TankCanvas") << "keyPressed:" << key;
}

void TankCanvas::keyReleased(int key) {
//	gLogi("TankCanvas") << "keyReleased:" << key;
}

void TankCanvas::charPressed(unsigned int codepoint) {
//	gLogi("TankCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void TankCanvas::mouseMoved(int x, int y) {
//	gLogi("TankCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
	updateButtonState(x, y);
}

void TankCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("TankCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void TankCanvas::mousePressed(int x, int y, int button) {
//	gLogi("TankCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	checkButtonPressed(x, y, button);
}

void TankCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("TankCanvas") << "mouseReleased" << ", button:" << button;
	checkButtonReleased(x, y, button);
}

void TankCanvas::mouseScrolled(int x, int y) {
//	gLogi("TankCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void TankCanvas::mouseEntered() {

}

void TankCanvas::mouseExited() {

}

void TankCanvas::windowResized(int w, int h) {

}

void TankCanvas::showNotify() {

}

void TankCanvas::hideNotify() {

}
