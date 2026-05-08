/*
 * ShopCanvas.h
 *
 *  Created on: 13 Nis 2026
 *      Author: Engin
 */

#ifndef SRC_SHOPCANVAS_H_
#define SRC_SHOPCANVAS_H_

#include <gBaseCanvas.h>
#include "gApp.h"
#include "gRect.h"

class ShopCanvas: public gBaseCanvas {
public:
	ShopCanvas(gApp* root);
	virtual ~ShopCanvas();

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
	static const int TAB_NONE = 0, TAB_HULL = 1, TAB_WEAPON = 2, TAB_TRACK = 3, TAB_BACK = 4;
	static const int LANG_EN = 1, LANG_TR = 2;
	static const int HULL_ONE = 0, HULL_TWO = 1, HULL_THREE = 2, HULL_FOUR = 3, HULL_FIVE = 4, HULL_SIX = 5, HULL_SEVEN = 6, HULL_EIGHT = 7;
	static const int WEAPON_ONE = 0, WEAPON_TWO = 1, WEAPON_THREE = 2, WEAPON_FOUR = 3, WEAPON_FIVE = 4, WEAPON_SIX = 5, WEAPON_SEVEN = 6, WEAPON_EIGHT = 7;
	static const int TRACK_ONE = 0, TRACK_TWO = 1, TRACK_THREE = 2, TRACK_FOUR = 3;
	static const int COLOR_ONE = 0, COLOR_TWO = 1, COLOR_THREE = 2, COLOR_FOUR = 3;

	void returnSetup();
	void fullTankSetup();
	void backgroundSetup();

	void backgroundDraw();
	void returnDraw();
	void fullTankDraw();

	void tabSetup();
	void hullTabSetup();
	void weaponTabSetup();
	void trackTabSetup();

	void containerSetup();
	void hullSettingsSetup();
	void weaponSettingsSetup();
	void trackSettingsSetup();

	void tabDraw();
	void hullTabButtonDraw();
	void weaponTabButtonDraw();
	void trackTabButtonDraw();

	void containerDraw();
	void hullSettingsDraw();
	void weaponSettingsDraw();
	void trackSettingsDraw();

	void tabButtonPressed(int x, int y);
	void tabButtonReleased(int x, int y);
	void tabButtonFocus(int x, int y);

	void containerButtonPressed(int x, int y);
	void containerButtonReleased(int x, int y);
	void containerButtonFocus(int x, int y);

	void hullSettingsPressed(int x, int y);
	void hullSettingsReleased(int x, int y);
	void hullSettingsFocus(int x, int y);

	void weaponSettingsPressed(int x, int y);
	void weaponSettingsReleased(int x, int y);
	void weaponSettingsFocus(int x, int y);

	void trackSettingsPressed(int x, int y);
	void trackSettingsReleased(int x, int y);
	void trackSettingsFocus(int x, int y);

	void updateButtonState(int x, int y);
	void checkButtonPressed(int x, int y, int button);
	void checkButtonReleased(int x, int y, int button);

	void colorSetup();

	void informationsSetup();
	void informationsDraw();

	void colorPickTextSetup();
	void colorPickTextDraw();

	void colorPickSetup();
	void colorPickDraw();

	void buyEnabledSetup();
	void buyEnabledDraw();

	void moneySetup();
	void moneyDraw();

	void refreshInformations();
	void buyTank();
	void refreshTankPreview();
	void lockSetup();

	//tabs
	gRect hulltabbutton, weapontabbutton, tracktabbutton, effecttabbutton;
	std::string hulltabtext, weapontabtext, tracktabtext, effecttabtext;
	int hulltabbuttonstate, weapontabbuttonstate, tracktabbuttonstate, effecttabbuttonstate;

	//container
	int containerx, containery, containerw, containerh;
	gColor containercolor;

	//hull settings
	std::string hulllabeltext, hulldisplaytext[3];
	int hulllabelx, hulllabely, hulllabelw, hulllabelh;
	int hulldisplayx, hulldisplayy, hulldisplayw, hulldisplayh;
	std::vector<std::string> hulllabellines;

	//weapon settings
	std::string weaponlabeltext;
	std::string weapononelabeltext;
	std::string weapontwolabeltext;
	gRect resolutionprev, resolutionnext;
	int resolutionprevstate, resolutionnextstate;
	int resolution;
	int weaponlabelx, weaponlabely, weaponlabelw, weaponlabelh;
	int resolutiondisplayx, resolutiondisplayy, resolutiondisplayw, resolutiondisplayh;
	int resolutionprevx, resolutionprevy, resolutionprevw, resolutionprevh;
	int resolutionnextx, resolutionnexty, resolutionnextw, resolutionnexth;

	//track settings
	std::string tracklabeltext[5];
	int tracklabelx[5], tracklabely[5], tracklabelw[5], tracklabelh[5];

	//effect settings
	bool ischangingkey;
	int selectedkey;
//	int keyboardcontrols[keynum];

	int hulltabbuttonx, hulltabbuttony, hulltabbuttonw, hulltabbuttonh;
	int weapontabbuttonx, weapontabbuttony, weapontabbuttonw, weapontabbuttonh;
	int tracktabbuttonx, tracktabbuttony, tracktabbuttonw, tracktabbuttonh;
	int effecttabbuttonx, effecttabbuttony, effecttabbuttonw, effecttabbuttonh;
	int tabfontx, tabfonty, tabfontw, tabfonth;
	int tabx, taby, tabw, tabh;
	gColor tabcolor, pressedcolor, focuscolor, normalcolor;

	int returnx, returny, returnw, returnh;
	std::string returntext;
	gRect returnhitbox;
	int returnbuttonstate;

	gImage tank;
	gImage weapon;
	gImage track;
	int tankx, tanky, tankw, tankh;
	int weaponx, weapony, weaponw, weaponh;
	int trackx, tracky, trackw, trackh;
	int titlex, titley, titlew;
	int activetab;

	//info
	std::string infotext;
	int infox, infoy;
	gImage infoline;
	int infolinex, infoliney, infolinew, infolineh;

	//colors
	std::string colortext;
	int colortextx, colortexty, colortextw, colortexth;
	gImage colorline;
	int colorlinex, colorliney, colorlinew, colorlineh;
	gImage colors[4];
	int colorx, colory, colorw, colorh;
	int colorspace;
	gRect colorshitbox[4];
	int colorstate[4];
	int activehullcolor;
	int activeweaponcolor;
	gImage* currenthullcolor;
	gImage* currentweaponcolor;
	std::string colorname;

	//hulls images
	gImage hulls[8];
	int hlabelx, hlabely, hlabelw, hlabelh;
	int hullimgw, hullimgh;
	float hulltextsx[8];
	float hulltextsy[8];
	std::string hulltexts[8];

	int hx[8];
	int hy[8];

	//hull buttons
	int activehull;

	gRect hullbuttons[8];
	int hullbuttonstates[8];
	gImage* currenthull;

	//weapon images
	gImage weapons[8];
	int wlabelx, wlabely, wlabelw, wlabelh;
	int weaponimgw, weaponimgh;
	float weapontextsx[8];
	float weapontextsy[8];
	std::string weapontexts[8];

	int wx[8];
	int wy[8];

	//weapon buttons
	int activeweapon;

	gRect weaponbuttons[8];
	int weaponbuttonstates[8];
	gImage* currentweapon;

	//track images
	gImage tracks[4];
	int tlabelx, tlabely, tlabelw, tlabelh;
	int trackimgw, trackimgh;
	float tracktextsx[4];
	float tracktextsy[4];
	std::string tracktexts[4];

	int tx[4];
	int ty[4];

	//track buttons
	int activetrack;

	gRect trackbuttons[4];
	int trackbuttonstates[4];
	gImage* currenttrack;

	//informations
	std::string speedtxt, durabilitytxt, healthtxt, attacktxt, bulletspeedtxt;
	int speedx, speedy;
	float values[5];
	std::string valuetxt[5];
	int trackspeed[4];
	int hulldurability[8];
	int hullhealth[8];
	int weaponattack[8];
	int weaponbulletspeed[8];
	//int speed, durability, health, attack, bulletspeed;
	int infogapx, infogapy;

	//Money
	gImage moneyimg;
	int moneyamt;
	std::string moneyamttxt;
	int moneyx, moneyy;
	int moneyh;
	int moneytextx, moneytexty;

	//Buy&enabled
	std::string buy, enabled;
	int buyx, buyy;
	int buyw, buyh;
	int buystate;
	gRect buyhitbox;
	bool buyed;
	int pricehull[8];
	int priceweapon[8];
	int pricetrack[4];
	std::string pricetxt;

	//lock
	gImage lock;
	int lockx, locky, lockw, lockh;
};

#endif /* SRC_SHOPCANVAS_H_ */
