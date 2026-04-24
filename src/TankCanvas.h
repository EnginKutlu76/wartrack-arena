/*
 * TankCanvas.h
 *
 *  Created on: 13 Nis 2026
 *      Author: Engin
 */

#ifndef SRC_TANKCANVAS_H_
#define SRC_TANKCANVAS_H_

#include <gBaseCanvas.h>
#include "gApp.h"

class TankCanvas: public gBaseCanvas {
public:
	TankCanvas(gApp* root);
	virtual ~TankCanvas();

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

	void returnSetup();
	void returnDraw();

	void updateButtonState(int x, int y);
	void checkButtonPressed(int x, int y, int button);
	void checkButtonReleased(int x, int y, int button);

	void colorSetup();

	gColor pressedcolor, normalcolor, focuscolor, inactivecolor;

	int returnx, returny, returnw, returnh;
	std::string returntext;
	gRect returnhitbox;
	int returnbuttonstate;
};

#endif /* SRC_TANKCANVAS_H_ */
