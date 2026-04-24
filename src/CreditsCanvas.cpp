#include "CreditsCanvas.h"
#include "MainMenu.h"
#include "gFont.h"

CreditsCanvas::CreditsCanvas(gApp* root): gBaseCanvas(root) {
	this->root = root;
}

CreditsCanvas::~CreditsCanvas() {
}

void CreditsCanvas::setup() {
	setupTexts();
	setupButton();

	normalcolor.set(255,255,255);
	focuscolor.set(200,200,200);
	pressedcolor.set(180,180,180);
}

void CreditsCanvas::update() {
}

void CreditsCanvas::draw() {
	drawTexts();
	drawButton();
}

void CreditsCanvas::setupTexts() {
	line1 = "Developed By";
	line2 = "Engin Kutlu";
	line3 = "Game Studio: Tengri Games";
	line4 = "Programming & Design: Engin Kutlu";
	line5 = "Special Thanks: glistEngine, GameLab Istanbul";
	line6 = "Assets & Fonts Licensed (dafont)";
	line7 = "(c) 2026";

	centerx = getWidth() / 2;
	linegap = 30;

	starty = getHeight() / 2 - 3 * linegap;
	title = "CREDITS";
	titley = getHeight() * 15 / 100;
}

void CreditsCanvas::drawTexts() {
	int y = starty;

	std::vector<std::string> lines = {
		line1, line2, line3, line4, line5, line6, line7
	};

	for(int i = 0; i < lines.size(); i++) {
		int w = root->menutitlefont.getStringWidth(lines[i]);
		root->menutitlefont.drawText(lines[i], centerx - w / 2, y);
		y += linegap;
	}

	int titlew = root->menutitlefont.getStringWidth(title);
	root->menutitlefont.drawText(title, centerx - titlew / 2, titley);
}

void CreditsCanvas::setupButton() {
	returntext = root->localizeWord(root->returnkey);

	returnw = root->menutitlefont.getStringWidth(returntext);
	returnh = root->menutitlefont.getStringHeight(returntext);

	returnx = getWidth() * 5 / 100;
	returny = getHeight() * 95 / 100;

	returnhitbox.set(returnx, returny - returnh, returnx + returnw, returny);
	returnstate = 0;
}

void CreditsCanvas::drawButton() {
	if(returnstate == 1) setColor(focuscolor);
	else if(returnstate == 2) setColor(pressedcolor);
	else setColor(normalcolor);

	root->menutitlefont.drawText(returntext, returnx, returny);
	setColor(255,255,255);
}

void CreditsCanvas::updateButtonState(int x, int y) {
	if(returnstate != 2) {
		if(returnhitbox.contains(x,y)) returnstate = 1;
		else returnstate = 0;
	}
}

void CreditsCanvas::checkButtonPressed(int x, int y) {
	if(returnhitbox.contains(x,y)) {
		returnstate = 2;
		returny += 2;
	}
}

void CreditsCanvas::checkButtonReleased(int x, int y) {
	if(returnhitbox.contains(x,y) && returnstate == 2) {
		returny -= 2;
		root->setCurrentCanvas(new mainMenu(root));
	}
	returnstate = 0;
}

void CreditsCanvas::mouseMoved(int x, int y) {
	updateButtonState(x,y);
}

void CreditsCanvas::mousePressed(int x, int y, int button) {
	checkButtonPressed(x,y);
}

void CreditsCanvas::mouseReleased(int x, int y, int button) {
	checkButtonReleased(x,y);
}
