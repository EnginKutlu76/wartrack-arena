/*
 * mainMenu.h
 *
 *  Created on: 13 Mar 2026
 *      Author: Engin Kutlu
 */

#ifndef SRC_MAINMENU_H_
#define SRC_MAINMENU_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gFont.h"
#include "gImage.h"
#include "gFont.h"

//#include "Fade.h"

class mainMenu: public gBaseCanvas {
public:
	mainMenu(gApp* root);
	virtual ~mainMenu();

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

	void menuSetup();
	void menuDraw();
	void menuPressed(int x, int y);
	void menuReleased(int x, int y);
	void menuFocus(int x, int y);

	//std::unique_ptr<Fade> fadeeffect;

private:
	static const int  BUTTON_NONE = 0, BUTTON_PRESSED = 1, BUTTON_CANCELED = -1, BUTTON_PERFORMED = 2, BUTTON_FOCUS = 3;

	gApp* root;

	void logoSetup();
	void startSetup();
	void offlineSetup();
	void optionSetup();
	void shopSetup();
	void helpSetup();
	void creditSetup();
	void exitSetup();
	void colorSetup();

	void updateButtonState(int x, int y);
	void checkButtonPressed(int x, int y, int button);
	void checkButtonReleased(int x, int y, int button);

	void backgroundDraw();
	void logoDraw();
	void startDraw();
	void offlineDraw();
	void shopDraw();
	void optionDraw();
	void creditDraw();
	void helpDraw();
	void exitDraw();
	void fadeEffectDraw();

	void moneyExpSetup();
	void moneyExpDraw();

	void nameSetup();
	void nameDraw();

	void selectedSetup();
	void hullSetup();
	void weaponSetup();
	void trackSetup();
	void drawCharacter();

	void containerSetup();
	void containerDraw();

	gImage background;
	std::string starttext, offlinetext, shoptext, optiontext, credittext, exittext, helptext;
	gImage glistlogo;
	int glistlogox, glistlogoy, glistlogow, glistlogoh;
	int nitralogox, nitralogoy, nitralogow, nitralogoh;
	int startx, starty, startw, starth;
	int offlinex, offliney, offlinew, offlineh;
	int shopx, shopy, shopw, shoph;
	int optionx, optiony, optionw, optionh;
	int helpx, helpy, helpw, helph;
	int creditx, credity, creditw, credith;
	int exitx, exity, exitw, exith;
	int titlex, titley;
	gRect starthitbox, offlinehitbox, shophitbox, optionhitbox, credithitbox, exithitbox, helphitbox;
	int startstate, offlinestate, shopstate, optionstate, creditstate, exitstate, helpstate;
	gColor pressedcolor, normalcolor, focuscolor;
	//std::unique_ptr<Fade> fadeeffect;

	gImage money, exp;
	std::string moneyname, expname;
	std::string moneytxt, exptxt;
	int moneyamt, expamt;
	int moneyx, moneyy;
	int expx, expy;

	std::string nametxt, name;
	int namex, namey;


	int selectedhull;
	int selectedweapon;
	int selectedtrack;
	int selectedhullcolor;
	int selectedweaponcolor;

	gImage hull;
	gImage weapon;
	gImage track;

	int hx, hy, hw, hh;
	int wx, wy, ww, wh;
	int tx, ty, tw, th;

	int containerx, containery, containerw, containerh;
	gColor containercolor;
};
#endif /* SRC_MAINMENU_H_ */
