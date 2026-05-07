/*
 * ShopCanvas.cpp
 *
 *  Created on: 13 Nis 2026
 *      Author: Engin
 */

#include <ShopCanvas.h>
#include "gBaseCanvas.h"
#include "gApp.h"
#include "MainMenu.h"
#include "gFont.h"
#include "gImage.h"
#include "gFont.h"

ShopCanvas::ShopCanvas(gApp* root): gBaseCanvas(root) {
	this->root = root;
}

ShopCanvas::~ShopCanvas() {

}

void ShopCanvas::setup() {
	currenthull = &hulls[activehull];
	currentweapon = &weapons[activeweapon];
	currenttrack = &tracks[activetrack];
	currentcolor = &colors[activecolor];
	fullTankSetup();
	backgroundSetup();
	tabSetup();
	containerSetup();
	informationsSetup();
	colorPickTextSetup();
	buyEnabledSetup();
	moneySetup();
	colorPickSetup();
	refreshInformations();
}

void ShopCanvas::update() {

}

void ShopCanvas::draw() {
	backgroundDraw();
	fullTankDraw();
	tabDraw();
	containerDraw();
	informationsDraw();
	colorPickTextDraw();
	buyEnabledDraw();
	moneyDraw();
	colorPickDraw();

	gLogi("activecolor") << activecolor;
}

void ShopCanvas::refreshInformations() {
	values[0] = trackspeed[activetrack];
	values[1] = hulldurability[activehull];
	values[2] = hullhealth[activehull];
	values[3] = weaponattack[activeweapon];
	values[4] = weaponbulletspeed[activeweapon];

	for(int i = 0; i < 5; i++) {
		valuetxt[i] = gToStr(values[i]);
	}
}

void ShopCanvas::moneySetup() {
	moneyimg.loadImage("Png/Icons/money.png");
	moneyamt = 100;
	moneyamttxt = gToStr(moneyamt);
	moneyh = moneyimg.getHeight();
	moneyx = infolinex;
	moneyy = infoliney + 350;
	moneytextx = moneyx + 100;
	moneytexty = infoliney + 400;
}

void ShopCanvas::moneyDraw() {
	moneyimg.draw(moneyx, moneyy);
	setColor(240, 240, 0);
	root->menutitlefont.drawText(moneyamttxt, moneytextx, moneytexty);
	setColor(255, 255, 255);
}

void ShopCanvas::buyEnabledSetup() {
	buy = "BUY: ";
	enabled = "ENABLED";
	buyh = root->menutitlefont.getStringHeight(buy);
	buyw = root->menutitlefont.getStringWidth(buy);
	buyx = infolinex;
	buyy = infoliney + 600;
	buyhitbox.set(buyx, buyy - buyh, buyx + buyw, buyy);
	buystate = BUTTON_NONE;
}

void ShopCanvas::buyEnabledDraw() {
	setColor(255, 255, 255, 255);
	if(buystate == BUTTON_FOCUS) setColor(focuscolor);
	if(buystate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(buy, buyx, buyy);
	setColor(255, 255, 255);
}

void ShopCanvas::colorPickTextSetup() {
    colortext = "Choose a color";

    colorline.loadImage("PNG/button.png");

    colorlinew = colorline.getWidth() * 1.2;
    colorlineh = colorline.getHeight() / 8;

    colorlinex = tankx - 25;
    colorliney = tanky + tankh + 20;

    colortextw = root->menutitlefont.getStringWidth(colortext);
    colortexth = root->menutitlefont.getStringHeight(colortext);

    colortextx = colorlinex + (colorlinew / 2) - (colortextw / 2);
    colortexty = colorliney + (colorlineh / 2) - (colortexth / 2);
}

void ShopCanvas::colorPickTextDraw() {
	root->menutitlefont.drawText(colortext, colortextx, colortexty + 50);
	colorline.draw(colorlinex, colorliney + 50, colorlinew, colorlineh);
}

void ShopCanvas::colorPickSetup() {
	colors[0].loadImage("PNG/color1.png");
	colors[1].loadImage("PNG/color2.png");
	colors[2].loadImage("PNG/color3.png");
	colors[3].loadImage("PNG/color4.png");

	colorw = colors[0].getWidth();
	colorh = colors[0].getHeight();
	colorx = colorlinex;
	colory = colorliney + 100;
	colorspace = colorw * 2;

	colorshitbox[0].set(colorx + colorspace * 0, colory - colorh, colorx + colorw, colory);
	colorshitbox[1].set(colorx + colorspace * 1, colory - colorh, colorx + colorspace * 1 + colorw, colory);
	colorshitbox[2].set(colorx + colorspace * 2, colory - colorh, colorx + colorspace * 2 + colorw, colory);
	colorshitbox[3].set(colorx + colorspace * 3, colory - colorh, colorx + colorspace * 3 + colorw, colory);

	for(int i = 0; i < 4; i++) {
	    colorstate[i] = BUTTON_NONE;
	}
}

void ShopCanvas::colorPickDraw() {
    for(int i = 0; i < 4; i++) {
    	int x = colorshitbox[i].left();
    	int y = colorshitbox[i].top();

    	if(activecolor == i) setColor(200, 200, 255);
    	else setColor(normalcolor);

    	setColor(255, 255, 255);
    	colors[i].draw(x, y, colorw, colorh);
    }
//	for(int i = 0; i < 4; i++) {
//		colors[i].draw(colorx + (colorspace * i), colory);
//	}
}

void ShopCanvas::informationsSetup() {
	infotext = "Informations";
	infox = 80;
	infoy = 80;
	infoline.loadImage("PNG/button.png");
	infolinew = infoline.getWidth() * 1.2;
	infolineh = infoline.getHeight() / 8;
	infolinex = infox;
	infoliney = infoy + infolineh;

	speedtxt = "Speed: ";
	durabilitytxt = "Durability: ";
	healthtxt = "Health: ";
	attacktxt = "Attack: ";
	bulletspeedtxt = "Bullet Speed: ";

	speedx = infolinex;
	speedy = infoliney + 50;


	infogapy = 50;
	infogapx = infolinex + root->menutitlefont.getStringWidth(bulletspeedtxt) + 50;

	trackspeed[0] = 4;
	trackspeed[1] = 5;
	trackspeed[2] = 6;
	trackspeed[3] = 7;

	hulldurability[0] = 5;
	hulldurability[1] = 7;
	hulldurability[2] = 9;
	hulldurability[3] = 11;
	hulldurability[4] = 13;
	hulldurability[5] = 15;
	hulldurability[6] = 16;
	hulldurability[7] = 17;

	hullhealth[0] = 100;
	hullhealth[1] = 120;
	hullhealth[2] = 140;
	hullhealth[3] = 150;
	hullhealth[4] = 160;
	hullhealth[5] = 170;
	hullhealth[6] = 180;
	hullhealth[7] = 200;

	weaponattack[0] = 6;
	weaponattack[1] = 8;
	weaponattack[2] = 10;
	weaponattack[3] = 12;
	weaponattack[4] = 14;
	weaponattack[5] = 16;
	weaponattack[6] = 18;
	weaponattack[7] = 20;

	weaponbulletspeed[0] = 1;
	weaponbulletspeed[1] = 2;
	weaponbulletspeed[2] = 3;
	weaponbulletspeed[3] = 4;
	weaponbulletspeed[4] = 5;
	weaponbulletspeed[5] = 6;
	weaponbulletspeed[6] = 7;
	weaponbulletspeed[7] = 8;

	values[0] = trackspeed[0];
	values[1] = hulldurability[0];
	values[2] = hullhealth[0];
	values[3] = weaponattack[0];
	values[4] = weaponbulletspeed[0];

	valuetxt[0] = gToStr(values[0]);
	valuetxt[1] = gToStr(values[1]);
	valuetxt[2] = gToStr(values[2]);
	valuetxt[3] = gToStr(values[3]);
	valuetxt[4] = gToStr(values[4]);
}

void ShopCanvas::informationsDraw() {
	setColor(255, 255, 255);
	root->menutitlefont.drawText(infotext, infox, infoy);
	infoline.draw(infolinex, infoliney, infolinew, infolineh);
	root->menutitlefont.drawText(speedtxt, speedx, speedy);
	root->menutitlefont.drawText(durabilitytxt, speedx, speedy + 50);
	root->menutitlefont.drawText(healthtxt, speedx, speedy + 100);
	root->menutitlefont.drawText(attacktxt, speedx, speedy + 150);
	root->menutitlefont.drawText(bulletspeedtxt, speedx, speedy + 200);

    for(int i = 0; i < 5; i++) {
    	root->menutitlefont.drawText(valuetxt[i], infogapx, speedy + (i * infogapy));
    }
}

void ShopCanvas::backgroundSetup() {
	titlew = root->menutitlefont.getStringWidth(root->shopkey);
	titlex = tankx + (tankw / 2) - (titlew / 2);
	titley = getHeight() / 10;
}

void ShopCanvas::backgroundDraw() {
	root->drawMenuBackground(getWidth(), getHeight());
	setColor(165, 55, 55);
	root->menutitlefont.drawText(root->shopkey, titlex, titley);
	setColor(255, 255, 255);
}

void ShopCanvas::fullTankSetup() {
	tank.loadImage("oyun/PNG/Hulls_Color_A/Hull_0" + gToStr(activehull + 1) + ".png");
	weapon.loadImage("oyun/PNG/Weapon_Color_A/Gun_0" + gToStr(activeweapon + 1) + ".png");
	track.loadImage("oyun/PNG/Tracks/Track_1_" + gToStr(activetrack + 1) + ".png");
	tankx = (getWidth() - tank.getWidth()) / 2;
	tanky = (getHeight() - tank.getHeight()) / 2;
	tankw = tank.getWidth();
	tankh = tank.getHeight();

	trackx = tankx +  track.getWidth();
	tracky = tanky;
	trackw = track.getWidth();
	trackh = track.getHeight();

	weaponx = tankx + (tank.getWidth() - weapon.getWidth()) / 2;
	weapony = tanky;
	weaponw = weapon.getWidth();
	weaponh = weapon.getHeight();
}

void ShopCanvas::fullTankDraw() {
	tankx = (getWidth() - currenthull->getWidth()) / 2;
	tanky = (getHeight() - currenthull->getHeight()) / 2;

	tankw = currenthull->getWidth();
	tankh = currenthull->getHeight();

	trackx = tankx + currenttrack->getWidth();
	tracky = tanky;

	weaponx = tankx + (currenthull->getWidth() - currentweapon->getWidth()) / 2;
	weapony = tanky;

	currenttrack->draw(trackx, tracky, currenttrack->getWidth(), currenttrack->getHeight());
	currenttrack->draw(trackx + (tankw / 2) + 2, tracky, currenttrack->getWidth(), currenttrack->getHeight());

	currenthull->draw(tankx, tanky, tankw, tankh);

	currentweapon->draw(
	    weaponx,
	    weapony,
	    currentweapon->getWidth(),
	    currentweapon->getHeight(),
	    currentweapon->getWidth() / 2,
	    currentweapon->getHeight(),
	    0
	);
}

void ShopCanvas::returnSetup() {
	returntext = root->localizeWord(root->returnkey);
	returnh = root->menutitlefont.getStringHeight(returntext);
	returnw = root->menutitlefont.getStringWidth(returntext);
	returnx = getWidth() * 5/100;
	returny = getHeight() * 95/100;

	returnhitbox.set(returnx, returny - returnh, returnx + returnw, returny);
	returnbuttonstate = BUTTON_NONE;
}

void ShopCanvas::returnDraw() {
	setColor(255, 255, 255, 255);
	if(returnbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(returnbuttonstate == BUTTON_PRESSED) setColor(pressedcolor);
	root->menutitlefont.drawText(returntext, returnx, returny);
	setColor(255, 255, 255);
}

void ShopCanvas::updateButtonState(int x, int y) {
	if(returnbuttonstate != BUTTON_PRESSED) {
		if(returnhitbox.contains(x, y)) {
			returnbuttonstate = BUTTON_FOCUS;
		}
		else {
			returnbuttonstate = BUTTON_NONE;
		}
	}
	if(buystate != BUTTON_PRESSED) {
		if(buyhitbox.contains(x, y)) {
			buystate = BUTTON_FOCUS;
		}
		else {
			buystate = BUTTON_NONE;
		}
	}

	if(colorstate[0] != BUTTON_PRESSED) {
		if(colorshitbox[0].contains(x, y)) {
			colorstate[0] = BUTTON_FOCUS;
		}
		else {
			colorstate[0] = BUTTON_NONE;
		}
	}

	if(colorstate[1] != BUTTON_PRESSED) {
		if(colorshitbox[1].contains(x, y)) {
			colorstate[1] = BUTTON_FOCUS;
		}
		else {
			colorstate[1] = BUTTON_NONE;
		}
	}

	if(colorstate[2] != BUTTON_PRESSED) {
		if(colorshitbox[2].contains(x, y)) {
			colorstate[2] = BUTTON_FOCUS;
		}
		else {
			colorstate[2] = BUTTON_NONE;
		}
	}

	if(colorstate[3] != BUTTON_PRESSED) {
		if(colorshitbox[3].contains(x, y)) {
			colorstate[3] = BUTTON_FOCUS;
		}
		else {
			colorstate[3] = BUTTON_NONE;
		}
	}
}

void ShopCanvas::checkButtonPressed(int x, int y, int button) {
	if(returnhitbox.contains(x, y)) {
		returnbuttonstate = BUTTON_PRESSED;
		returny += 2;
	}

	if(colorshitbox[0].contains(x, y)) {
		colorstate[0] = BUTTON_PRESSED;
	}

	if(colorshitbox[1].contains(x, y)) {
		colorstate[1] = BUTTON_PRESSED;
	}

	if(colorshitbox[2].contains(x, y)) {
		colorstate[2] = BUTTON_PRESSED;
	}

	if(colorshitbox[3].contains(x, y)) {
		colorstate[3] = BUTTON_PRESSED;
	}
}

void ShopCanvas::checkButtonReleased(int x, int y, int button) {
	if(returnhitbox.contains(x, y) && returnbuttonstate == BUTTON_PRESSED) {
		returnbuttonstate = BUTTON_PERFORMED;
		returny -= 2;
		//root->gamestate = root->GAME_LOAD;
		root->setCurrentCanvas(new mainMenu(root));
	}

	else if(colorshitbox[0].contains(x, y) && colorstate[0] == BUTTON_PRESSED) {
		colorstate[0] = BUTTON_PERFORMED;
		activecolor = COLOR_ONE;
		gLogi("aktif") << 1;
		//currentcolor = &colors[0];
	}
	else if(colorshitbox[1].contains(x, y) && colorstate[1] == BUTTON_PRESSED) {
		colorstate[1] = BUTTON_PERFORMED;
		activecolor = COLOR_TWO;
		//currentcolor = &colors[1];
		gLogi("aktif") << 2;
	}
	else if(colorshitbox[2].contains(x, y) && colorstate[2] == BUTTON_PRESSED) {
		colorstate[2] = BUTTON_PERFORMED;
		activecolor = COLOR_THREE;
		//currentcolor = &colors[2];
		gLogi("aktif") << 3;
	}
	else if(colorshitbox[3].contains(x, y) && colorstate[3] == BUTTON_PRESSED) {
		colorstate[3] = BUTTON_PERFORMED;
		activecolor = COLOR_FOUR;
		//currentcolor = &colors[3];
		gLogi("aktif") << 4;
	}
	else {
		colorstate[0] = BUTTON_CANCELED;
		colorstate[1] = BUTTON_CANCELED;
		colorstate[2] = BUTTON_CANCELED;
		colorstate[3] = BUTTON_CANCELED;
	}
}

void ShopCanvas::colorSetup() {
	pressedcolor.set(190, 190, 190);
	normalcolor.set(255, 255, 255);
	focuscolor.set(200, 200, 200);
}

void ShopCanvas::tabSetup() {
	tabw = getWidth() / 3;
	tabh = getHeight() / 8;
	tabx = (getWidth() - tabw);
	taby = tabh - 110;
	tabcolor.set(255, 255, 255);
	normalcolor.set(45, 50, 70);
	pressedcolor.set(65, 70, 90);
	focuscolor.set(55, 60, 80);
	hullTabSetup();
	weaponTabSetup();
	trackTabSetup();
	effectTabSetup();
	returnSetup();

	activetab = TAB_GENERAL;
}

void ShopCanvas::hullTabSetup() {
	hulltabtext = root->localizeWord(root->generalkey);
	hulltabbuttonstate = BUTTON_NONE;
	hulltabbuttonw = tabw / 4;
	hulltabbuttonh = tabh;
	hulltabbuttonx = tabx;
	hulltabbuttony = taby;
	hulltabbutton.set(hulltabbuttonx, hulltabbuttony, hulltabbuttonx + hulltabbuttonw, hulltabbuttony + hulltabbuttonh);
}

void ShopCanvas::weaponTabSetup() {
	weapontabtext = "Silahlar";
	weapontabbuttonstate = BUTTON_NONE;
	weapontabbuttonw = tabw / 4;
	weapontabbuttonh = tabh;
	weapontabbuttonx = tabx + hulltabbuttonw;
	weapontabbuttony = taby;
	weapontabbutton.set(weapontabbuttonx, weapontabbuttony, weapontabbuttonx + weapontabbuttonw, weapontabbuttony + weapontabbuttonh);
}

void ShopCanvas::trackTabSetup() {
	tracktabtext = "Tekerlek";
	tracktabbuttonstate = BUTTON_NONE;
	tracktabbuttonw = tabw / 4;
	tracktabbuttonh = tabh;
	tracktabbuttonx = tabx + hulltabbuttonw + weapontabbuttonw;
	tracktabbuttony = taby;
	tracktabbutton.set(tracktabbuttonx, tracktabbuttony, tracktabbuttonx + tracktabbuttonw, tracktabbuttony + tracktabbuttonh);
}

void ShopCanvas::effectTabSetup() {
	effecttabtext = root->localizeWord(root->skillskey);
	effecttabbuttonstate = BUTTON_NONE;
	effecttabbuttonw = tabw / 4;
	effecttabbuttonh = tabh;
	effecttabbuttonx = tabx + hulltabbuttonw + weapontabbuttonw + tracktabbuttonw;
	effecttabbuttony = taby;
	effecttabbutton.set(effecttabbuttonx, effecttabbuttony, effecttabbuttonx + effecttabbuttonw, effecttabbuttony + effecttabbuttonh);
}

void ShopCanvas::containerSetup() {
	containerw = tabw;
	containerh = tabh * 7;
	containerx = tabx;
	containery = taby + tabh;
	containercolor.set(25, 25, 112);
	hullSettingsSetup();
	weaponSettingsSetup();
	trackSettingsSetup();
	effectSettingsSetup();
}

void ShopCanvas::hullSettingsSetup() {
    hulls[0].loadImage("oyun/PNG/Hulls_Color_A/Hull_01.png");
    hulls[1].loadImage("oyun/PNG/Hulls_Color_A/Hull_02.png");
    hulls[2].loadImage("oyun/PNG/Hulls_Color_A/Hull_03.png");
    hulls[3].loadImage("oyun/PNG/Hulls_Color_A/Hull_04.png");
    hulls[4].loadImage("oyun/PNG/Hulls_Color_A/Hull_05.png");
    hulls[5].loadImage("oyun/PNG/Hulls_Color_A/Hull_06.png");
    hulls[6].loadImage("oyun/PNG/Hulls_Color_A/Hull_07.png");
    hulls[7].loadImage("oyun/PNG/Hulls_Color_A/Hull_08.png");

    hulltexts[0] = "HULL 1";
    hulltexts[1] = "HULL 2";
    hulltexts[2] = "HULL 3";
    hulltexts[3] = "HULL 4";
    hulltexts[4] = "HULL 5";
    hulltexts[5] = "HULL 6";
    hulltexts[6] = "HULL 7";
    hulltexts[7] = "HULL 8";

    hullimgw = hulls[0].getWidth() / 1.5;
    hullimgh = hulls[0].getHeight() / 1.5;
 	hlabelw = root->menutitlefont.getStringWidth(hulltexts[0]);
	hlabelh = root->menutitlefont.getStringHeight("y");
	hlabelx = containerx ;
	hlabely = containery + hullimgh / 5;

	hx[0] = hlabelx;
	hy[0] = hlabely;
	hx[1] = hx[0] + (hullimgw * 1.350);
	hy[1] = hlabely;
	hx[2] = hx[0];
	hy[2] = hlabely + hullimgh;
	hx[3] = hx[1];
	hy[3] = hy[2];
	hx[4] = hx[0];
	hy[4] = hy[2] + hullimgh;
	hx[5] = hx[1];
	hy[5] = hy[3] + hullimgh;
	hx[6] = hx[0];
	hy[6] = hy[4] + hullimgh;
	hx[7] = hx[1];
	hy[7] = hy[5] + hullimgh;

	hullbuttons[0].set(hx[0], hy[0], hx[0] + hullimgw, hy[0] + hullimgh);
	hullbuttons[1].set(hx[1], hy[1], hx[1] + hullimgw, hy[1] + hullimgh);
	hullbuttons[2].set(hx[2], hy[2], hx[2] + hullimgw, hy[2] + hullimgh);
	hullbuttons[3].set(hx[3], hy[3], hx[3] + hullimgw, hy[3] + hullimgh);
	hullbuttons[4].set(hx[4], hy[4], hx[4] + hullimgw, hy[4] + hullimgh);
	hullbuttons[5].set(hx[5], hy[5], hx[5] + hullimgw, hy[5] + hullimgh);
	hullbuttons[6].set(hx[6], hy[6], hx[6] + hullimgw, hy[6] + hullimgh);
	hullbuttons[7].set(hx[7], hy[7], hx[7] + hullimgw, hy[7] + hullimgh);
}

void ShopCanvas::hullSettingsDraw() {
	setColor(255, 255, 255);
    for(int i = 0; i < 8; i++) {
    	int x = hullbuttons[i].left();
    	int y = hullbuttons[i].top();

    	if(activehull == i) setColor(200, 200, 255);
    	//else if(hullButtonStates[i] == BUTTON_FOCUS) setColor(focuscolor);
    	else setColor(normalcolor);

   // 	gDrawRectangle(x, y, hullimgw, hullimgh, true);
    	//setColor(255, 255, 255);


    	hulls[i].draw(x, y, hullimgw, hullimgh);
    	setColor(255, 255, 255);
    	root->menutitlefont.drawText(hulltexts[i], hx[i] + hullbuttons[i].getWidth() / 1.15f, hy[i] + hullbuttons[i].getHeight() / 4);
   }
}

void ShopCanvas::weaponSettingsSetup() {
    weapons[0].loadImage("oyun/PNG/Weapon_Color_A/Gun_01.png");
    weapons[1].loadImage("oyun/PNG/Weapon_Color_A/Gun_02.png");
    weapons[2].loadImage("oyun/PNG/Weapon_Color_A/Gun_03.png");
    weapons[3].loadImage("oyun/PNG/Weapon_Color_A/Gun_04.png");
    weapons[4].loadImage("oyun/PNG/Weapon_Color_A/Gun_05.png");
    weapons[5].loadImage("oyun/PNG/Weapon_Color_A/Gun_06.png");
    weapons[6].loadImage("oyun/PNG/Weapon_Color_A/Gun_07.png");
    weapons[7].loadImage("oyun/PNG/Weapon_Color_A/Gun_08.png");

    weapontexts[0] = "Gun 1";
    weapontexts[1] = "Gun 2";
    weapontexts[2] = "Gun 3";
    weapontexts[3] = "Gun 4";
    weapontexts[4] = "Gun 5";
    weapontexts[5] = "Gun 6";
    weapontexts[6] = "Gun 7";
    weapontexts[7] = "Gun 8";

    weaponimgw = weapons[0].getWidth();
    weaponimgh = weapons[0].getHeight();
 	wlabelw = root->menutitlefont.getStringWidth(weapontexts[0]);
	wlabelh = root->menutitlefont.getStringHeight("y");
	wlabelx = containerx ;
	wlabely = containery + weaponimgh / 5;

	wx[0] = wlabelx;
	wy[0] = wlabely;
	wx[1] = wx[0] + (weaponimgw * 3);
	wy[1] = wlabely;
	wx[2] = wx[0];
	wy[2] = wlabely + (weaponimgh * 1.10);
	wx[3] = wx[1];
	wy[3] = wy[2];
	wx[4] = wx[0];
	wy[4] = wy[2] + weaponimgh;
	wx[5] = wx[1];
	wy[5] = wy[3] + weaponimgh;
	wx[6] = wx[0];
	wy[6] = wy[4] + weaponimgh;
	wx[7] = wx[1];
	wy[7] = wy[5] + weaponimgh;

	weaponbuttons[0].set(wx[0], wy[0], wx[0] + weaponimgw, wy[0] + weaponimgh);
	weaponbuttons[1].set(wx[1], wy[1], wx[1] + weaponimgw, wy[1] + weaponimgh);
	weaponbuttons[2].set(wx[2], wy[2], wx[2] + weaponimgw, wy[2] + weaponimgh);
	weaponbuttons[3].set(wx[3], wy[3], wx[3] + weaponimgw, wy[3] + weaponimgh);
	weaponbuttons[4].set(wx[4], wy[4], wx[4] + weaponimgw, wy[4] + weaponimgh);
	weaponbuttons[5].set(wx[5], wy[5], wx[5] + weaponimgw, wy[5] + weaponimgh);
	weaponbuttons[6].set(wx[6], wy[6], wx[6] + weaponimgw, wy[6] + weaponimgh);
	weaponbuttons[7].set(wx[7], wy[7], wx[7] + weaponimgw, wy[7] + weaponimgh);
}

void ShopCanvas::trackSettingsSetup() {
    tracks[0].loadImage("oyun/PNG/Tracks/Track_1_0.png");
    tracks[1].loadImage("oyun/PNG/Tracks/Track_2_0.png");
    tracks[2].loadImage("oyun/PNG/Tracks/Track_3_0.png");
    tracks[3].loadImage("oyun/PNG/Tracks/Track_4_0.png");

    tracktexts[0] = "Track 1";
    tracktexts[1] = "Track 2";
    tracktexts[2] = "Track 3";
    tracktexts[3] = "Track 4";

    trackimgw = tracks[0].getWidth();
    trackimgh = tracks[0].getHeight();
 	tlabelw = root->menutitlefont.getStringWidth(tracktexts[0]);
	tlabelh = root->menutitlefont.getStringHeight("y");
	tlabelx = containerx ;
	tlabely = containery + weaponimgh / 5;

	tx[0] = tlabelx;
	ty[0] = tlabely;
	tx[1] = tx[0] + (trackimgw * 5.5);
	ty[1] = tlabely;
	tx[2] = tx[0];
	ty[2] = tlabely + (trackimgh * 1.25);
	tx[3] = tx[1];
	ty[3] = ty[2];

	trackbuttons[0].set(tx[0], ty[0], tx[0] + trackimgw, ty[0] + trackimgh);
	trackbuttons[1].set(tx[1], ty[1], tx[1] + trackimgw, ty[1] + trackimgh);
	trackbuttons[2].set(tx[2], ty[2], tx[2] + trackimgw, ty[2] + trackimgh);
	trackbuttons[3].set(tx[3], ty[3], tx[3] + trackimgw, ty[3] + trackimgh);
}

void ShopCanvas::effectSettingsSetup() {
	//////////////////////////////////////////
}

void ShopCanvas::tabDraw() {
	setColor(tabcolor);
	gDrawRectangle(tabx, taby, tabw, tabh, true);
	setColor(normalcolor);
	hullTabButtonDraw();
	weaponTabButtonDraw();
	trackTabButtonDraw();
	effectTabButtonDraw();
	returnDraw();
}

void ShopCanvas::hullTabButtonDraw() {
	if(hulltabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(hulltabbuttonstate == BUTTON_PRESSED || hulltabbuttonstate == BUTTON_PERFORMED || activetab == TAB_GENERAL) setColor(pressedcolor);
	gDrawRectangle(hulltabbuttonx, hulltabbuttony, hulltabbuttonw, hulltabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(hulltabtext);
	tabfonth = root->menutitlefont.getStringHeight(hulltabtext);
	tabfontx = hulltabbuttonx + (hulltabbuttonw - tabfontw) / 2;
	tabfonty = hulltabbuttony + (hulltabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(hulltabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void ShopCanvas::weaponTabButtonDraw() {
	if(weapontabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(weapontabbuttonstate == BUTTON_PRESSED || weapontabbuttonstate == BUTTON_PERFORMED || activetab == TAB_LEVEL) setColor(pressedcolor);
	gDrawRectangle(weapontabbuttonx, weapontabbuttony, weapontabbuttonw, weapontabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(weapontabtext);
	tabfonth = root->menutitlefont.getStringHeight(weapontabtext);
	tabfontx = weapontabbuttonx + (weapontabbuttonw - tabfontw) / 2;
	tabfonty = weapontabbuttony + (weapontabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(weapontabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void ShopCanvas::trackTabButtonDraw() {
	if(tracktabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(tracktabbuttonstate == BUTTON_PRESSED || tracktabbuttonstate == BUTTON_PERFORMED || activetab == TAB_ITEMS) setColor(pressedcolor);
	gDrawRectangle(tracktabbuttonx, tracktabbuttony, tracktabbuttonw, tracktabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(tracktabtext);
	tabfonth = root->menutitlefont.getStringHeight(tracktabtext);
	tabfontx = tracktabbuttonx + (tracktabbuttonw - tabfontw) / 2;
	tabfonty = tracktabbuttony + (tracktabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(tracktabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void ShopCanvas::effectTabButtonDraw() {
	if(effecttabbuttonstate == BUTTON_FOCUS) setColor(focuscolor);
	if(effecttabbuttonstate == BUTTON_PRESSED || effecttabbuttonstate == BUTTON_PERFORMED || activetab == TAB_CONTROLS) setColor(pressedcolor);
	gDrawRectangle(effecttabbuttonx, effecttabbuttony, effecttabbuttonw, effecttabbuttonh, true);
	tabfontw = root->menutitlefont.getStringWidth(effecttabtext);
	tabfonth = root->menutitlefont.getStringHeight(effecttabtext);
	tabfontx = effecttabbuttonx + (effecttabbuttonw - tabfontw) / 2;
	tabfonty = effecttabbuttony + (effecttabbuttonh + tabfonth) / 2;
	setColor(255, 255, 255);
	root->menutitlefont.drawText(effecttabtext, tabfontx, tabfonty);
	setColor(normalcolor);
}

void ShopCanvas::containerDraw() {
	setColor(containercolor);
	gDrawRectangle(containerx, containery, containerw, containerh, true);
	if(activetab == TAB_GENERAL) hullSettingsDraw();
	else if(activetab == TAB_LEVEL) weaponSettingsDraw();
	else if(activetab == TAB_ITEMS) trackSettingsDraw();
	else if(activetab == TAB_CONTROLS) effectSettingsDraw();
}

void ShopCanvas::weaponSettingsDraw() {
	setColor(255, 255, 255);
	for(int i = 0; i < 8; i++) {
		int x = weaponbuttons[i].left();
		int y = weaponbuttons[i].top();

		if(activeweapon == i) setColor(200, 200, 255);
		//else if(hullButtonStates[i] == BUTTON_FOCUS) setColor(focuscolor);
		else setColor(normalcolor);
	    //gDrawRectangle(x, y, hullimgw, hullimgh, true);
		//setColor(255, 255, 255);
	    weapons[i].draw(x, y, weaponimgw, weaponimgh);
	    setColor(255, 255, 255);
	    root->menutitlefont.drawText(weapontexts[i], wx[i] + weaponbuttons[i].getWidth() / 1.15f, wy[i] + weaponbuttons[i].getHeight() / 4);
	    }

    setColor(255, 255, 255);
}

void ShopCanvas::trackSettingsDraw() {
	setColor(255, 255, 255);
    for(int i = 0; i < 4; i++) {
    	int x = trackbuttons[i].left();
    	int y = trackbuttons[i].top();

    	if(activetrack == i) setColor(200, 200, 255);
    	//else if(hullButtonStates[i] == BUTTON_FOCUS) setColor(focuscolor);
    	else setColor(normalcolor);
   // 	gDrawRectangle(x, y, hullimgw, hullimgh, true);
    	//setColor(255, 255, 255);
    	tracks[i].draw(x, y, trackimgw, trackimgh);
    	setColor(255, 255, 255);
    	root->menutitlefont.drawText(tracktexts[i], tx[i] + trackbuttons[i].getWidth() / 1.15f, ty[i] + trackbuttons[i].getHeight() / 4);
    }
	setColor(255, 255, 255);
}

void ShopCanvas::effectSettingsDraw() {
//////////////////////////////
}

void ShopCanvas::tabButtonPressed(int x, int y) {
	if(hulltabbutton.contains(x, y)) {
		hulltabbuttonstate = BUTTON_PRESSED;
	}

	if(weapontabbutton.contains(x, y)) {
		weapontabbuttonstate = BUTTON_PRESSED;
	}

	if(tracktabbutton.contains(x, y)) {
		tracktabbuttonstate = BUTTON_PRESSED;
	}

	if(effecttabbutton.contains(x, y)) {
		effecttabbuttonstate = BUTTON_PRESSED;
	}
}

void ShopCanvas::tabButtonReleased(int x, int y) {
	if(hulltabbutton.contains(x, y) && hulltabbuttonstate == BUTTON_PRESSED) {
		hulltabbuttonstate = BUTTON_PERFORMED;
		activetab = TAB_GENERAL;
	}

	else if(weapontabbutton.contains(x, y) && weapontabbuttonstate == BUTTON_PRESSED) {
		weapontabbuttonstate = BUTTON_PERFORMED;
		activetab = TAB_LEVEL;
	}

	else if(tracktabbutton.contains(x, y) && tracktabbuttonstate == BUTTON_PRESSED) {
		tracktabbuttonstate = BUTTON_PERFORMED;
		activetab = TAB_ITEMS;
	}

	else if(effecttabbutton.contains(x, y) && effecttabbuttonstate == BUTTON_PRESSED) {
		effecttabbuttonstate = BUTTON_PERFORMED;
		activetab = TAB_CONTROLS;
	}

	else {
		hulltabbuttonstate = BUTTON_CANCELED;
		weapontabbuttonstate = BUTTON_CANCELED;
		tracktabbuttonstate = BUTTON_CANCELED;
		effecttabbuttonstate = BUTTON_CANCELED;
	}
}

void ShopCanvas::tabButtonFocus(int x, int y) {
	if(hulltabbuttonstate != BUTTON_PRESSED) {
		if(hulltabbutton.contains(x, y)) {
			hulltabbuttonstate = BUTTON_FOCUS;
		}
		else {
			hulltabbuttonstate = BUTTON_NONE;
		}
	}

	if(weapontabbuttonstate != BUTTON_PRESSED) {
		if(weapontabbutton.contains(x, y)) {
			weapontabbuttonstate = BUTTON_FOCUS;
		}
		else {
			weapontabbuttonstate = BUTTON_NONE;
		}
	}

	if(tracktabbuttonstate != BUTTON_PRESSED) {
		if(tracktabbutton.contains(x, y)) {
			tracktabbuttonstate = BUTTON_FOCUS;
		}
		else {
			tracktabbuttonstate = BUTTON_NONE;
		}
	}

	if(effecttabbuttonstate != BUTTON_PRESSED) {
		if(effecttabbutton.contains(x, y)) {
			effecttabbuttonstate = BUTTON_FOCUS;
		}
		else {
			effecttabbuttonstate = BUTTON_NONE;
		}
	}
}

void ShopCanvas::containerButtonPressed(int x, int y) {
	if(activetab == TAB_GENERAL) {
		hullSettingsPressed(x, y);
	}
	else if(activetab == TAB_LEVEL) {
		weaponSettingsPressed(x, y);
	}
	else if(activetab == TAB_ITEMS) {
		trackSettingsPressed(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		effectSettingsPressed(x, y);
	}
}

void ShopCanvas::containerButtonReleased(int x, int y) {
	if(activetab == TAB_GENERAL) {
		hullSettingsReleased(x, y);
	}
	else if(activetab == TAB_LEVEL) {
		weaponSettingsReleased(x, y);
	}
	else if(activetab == TAB_ITEMS) {
		trackSettingsReleased(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		effectSettingsReleased(x, y);
	}
}

void ShopCanvas::containerButtonFocus(int x, int y) {
	if(activetab == TAB_GENERAL) {
		hullSettingsFocus(x, y);
	}
	else if(activetab == TAB_LEVEL) {
		weaponSettingsFocus(x, y);
	}
	else if(activetab == TAB_ITEMS) {
		trackSettingsFocus(x, y);
	}
	else if(activetab == TAB_CONTROLS) {
		effectSettingsFocus(x, y);
	}
}

void ShopCanvas::hullSettingsPressed(int x, int y) {
	if(hullbuttons[0].contains(x, y)) {
		hullbuttonstates[0] = BUTTON_PRESSED;
	}

	if(hullbuttons[1].contains(x, y)) {
		hullbuttonstates[1] = BUTTON_PRESSED;
	}

	if(hullbuttons[2].contains(x, y)) {
		hullbuttonstates[2] = BUTTON_PRESSED;
	}

	if(hullbuttons[3].contains(x, y)) {
		hullbuttonstates[3] = BUTTON_PRESSED;
	}

	if(hullbuttons[4].contains(x, y)) {
		hullbuttonstates[4] = BUTTON_PRESSED;
	}

	if(hullbuttons[5].contains(x, y)) {
		hullbuttonstates[5] = BUTTON_PRESSED;
	}

	if(hullbuttons[6].contains(x, y)) {
		hullbuttonstates[6] = BUTTON_PRESSED;
	}

	if(hullbuttons[7].contains(x, y)) {
		hullbuttonstates[7] = BUTTON_PRESSED;
	}
}

void ShopCanvas::hullSettingsReleased(int x, int y) {
	if(hullbuttons[0].contains(x, y) && hullbuttonstates[0] == BUTTON_PRESSED) {
		hullbuttonstates[0] = BUTTON_PERFORMED;
		activehull = HULL_ONE;
		currenthull = &hulls[0];
		refreshInformations();
	}

	else if(hullbuttons[1].contains(x, y) && hullbuttonstates[1] == BUTTON_PRESSED) {
		hullbuttonstates[1] = BUTTON_PERFORMED;
		activehull = HULL_TWO;
		currenthull = &hulls[1];
		refreshInformations();
	}

	else if(hullbuttons[2].contains(x, y) && hullbuttonstates[2] == BUTTON_PRESSED) {
		hullbuttonstates[2] = BUTTON_PERFORMED;
		activehull = HULL_THREE;
		currenthull = &hulls[2];
		refreshInformations();
	}

	else if(hullbuttons[3].contains(x, y) && hullbuttonstates[3] == BUTTON_PRESSED) {
		hullbuttonstates[3] = BUTTON_PERFORMED;
		activehull = HULL_FOUR;
		currenthull = &hulls[3];
		refreshInformations();
	}

	else if(hullbuttons[4].contains(x, y) && hullbuttonstates[4] == BUTTON_PRESSED) {
		hullbuttonstates[4] = BUTTON_PERFORMED;
		activehull = HULL_FIVE;
		currenthull = &hulls[4];
		refreshInformations();
	}

	else if(hullbuttons[5].contains(x, y) && hullbuttonstates[5] == BUTTON_PRESSED) {
		hullbuttonstates[5] = BUTTON_PERFORMED;
		activehull = HULL_SIX;
		currenthull = &hulls[5];
		refreshInformations();
	}

	else if(hullbuttons[6].contains(x, y) && hullbuttonstates[6] == BUTTON_PRESSED) {
		hullbuttonstates[6] = BUTTON_PERFORMED;
		activehull = HULL_SEVEN;
		currenthull = &hulls[6];
		refreshInformations();
	}

	else if(hullbuttons[7].contains(x, y) && hullbuttonstates[7] == BUTTON_PRESSED) {
		hullbuttonstates[7] = BUTTON_PERFORMED;
		activehull = HULL_EIGHT;
		currenthull = &hulls[7];
		refreshInformations();
	}
	else {
		hullbuttonstates[0] = BUTTON_CANCELED;
		hullbuttonstates[1] = BUTTON_CANCELED;
		hullbuttonstates[2] = BUTTON_CANCELED;
		hullbuttonstates[3] = BUTTON_CANCELED;
		hullbuttonstates[4] = BUTTON_CANCELED;
		hullbuttonstates[5] = BUTTON_CANCELED;
		hullbuttonstates[6] = BUTTON_CANCELED;
		hullbuttonstates[7] = BUTTON_CANCELED;
	}
}

void ShopCanvas::hullSettingsFocus(int x, int y) {
	if(hullbuttonstates[0] != BUTTON_PRESSED) {
		if(hullbuttons[0].contains(x, y)) {
			hullbuttonstates[0] = BUTTON_FOCUS;
		}
		else {
			hullbuttonstates[0] = BUTTON_NONE;
		}
	}

	if(hullbuttonstates[1] != BUTTON_PRESSED) {
		if(hullbuttons[1].contains(x, y)) {
			hullbuttonstates[1] = BUTTON_FOCUS;
		}
		else {
			hullbuttonstates[1] = BUTTON_NONE;
		}
	}

	if(hullbuttonstates[2] != BUTTON_PRESSED) {
		if(hullbuttons[2].contains(x, y)) {
			hullbuttonstates[2] = BUTTON_FOCUS;
		}
		else {
			hullbuttonstates[2] = BUTTON_NONE;
		}
	}

	if(hullbuttonstates[3] != BUTTON_PRESSED) {
		if(hullbuttons[3].contains(x, y)) {
			hullbuttonstates[3] = BUTTON_FOCUS;
		}
		else {
			hullbuttonstates[3] = BUTTON_NONE;
		}
	}

	if(hullbuttonstates[4] != BUTTON_PRESSED) {
		if(hullbuttons[4].contains(x, y)) {
			hullbuttonstates[4] = BUTTON_FOCUS;
		}
		else {
			hullbuttonstates[4] = BUTTON_NONE;
		}
	}

	if(hullbuttonstates[5] != BUTTON_PRESSED) {
		if(hullbuttons[5].contains(x, y)) {
			hullbuttonstates[5] = BUTTON_FOCUS;
		}
		else {
			hullbuttonstates[5] = BUTTON_NONE;
		}
	}

	if(hullbuttonstates[6] != BUTTON_PRESSED) {
		if(hullbuttons[6].contains(x, y)) {
			hullbuttonstates[6] = BUTTON_FOCUS;
		}
		else {
			hullbuttonstates[6] = BUTTON_NONE;
		}
	}

	if(hullbuttonstates[7] != BUTTON_PRESSED) {
		if(hullbuttons[7].contains(x, y)) {
			hullbuttonstates[7] = BUTTON_FOCUS;
		}
		else {
			hullbuttonstates[7] = BUTTON_NONE;
		}
	}
}

void ShopCanvas::weaponSettingsPressed(int x, int y) {
	if(weaponbuttons[0].contains(x, y)) {
		weaponbuttonstates[0] = BUTTON_PRESSED;
	}

	if(weaponbuttons[1].contains(x, y)) {
		weaponbuttonstates[1] = BUTTON_PRESSED;
	}

	if(weaponbuttons[2].contains(x, y)) {
		weaponbuttonstates[2] = BUTTON_PRESSED;
	}

	if(weaponbuttons[3].contains(x, y)) {
		weaponbuttonstates[3] = BUTTON_PRESSED;
	}

	if(weaponbuttons[4].contains(x, y)) {
		weaponbuttonstates[4] = BUTTON_PRESSED;
	}

	if(weaponbuttons[5].contains(x, y)) {
		weaponbuttonstates[5] = BUTTON_PRESSED;
	}

	if(weaponbuttons[6].contains(x, y)) {
		weaponbuttonstates[6] = BUTTON_PRESSED;
	}

	if(weaponbuttons[7].contains(x, y)) {
		weaponbuttonstates[7] = BUTTON_PRESSED;
	}
}

void ShopCanvas::weaponSettingsReleased(int x, int y) {
	if(weaponbuttons[0].contains(x, y) && weaponbuttonstates[0] == BUTTON_PRESSED) {
		weaponbuttonstates[0] = BUTTON_PERFORMED;
		activeweapon = WEAPON_ONE;
		currentweapon = &weapons[0];
		refreshInformations();
	}

	else if(weaponbuttons[1].contains(x, y) && weaponbuttonstates[1] == BUTTON_PRESSED) {
		weaponbuttonstates[1] = BUTTON_PERFORMED;
		activeweapon = WEAPON_TWO;
		currentweapon = &weapons[1];
		refreshInformations();
	}

	else if(weaponbuttons[2].contains(x, y) && weaponbuttonstates[2] == BUTTON_PRESSED) {
		weaponbuttonstates[2] = BUTTON_PERFORMED;
		activeweapon = WEAPON_THREE;
		currentweapon = &weapons[2];
		refreshInformations();
	}

	else if(weaponbuttons[3].contains(x, y) && weaponbuttonstates[3] == BUTTON_PRESSED) {
		weaponbuttonstates[3] = BUTTON_PERFORMED;
		activeweapon = WEAPON_FOUR;
		currentweapon = &weapons[3];
		refreshInformations();
	}

	else if(weaponbuttons[4].contains(x, y) && weaponbuttonstates[4] == BUTTON_PRESSED) {
		weaponbuttonstates[4] = BUTTON_PERFORMED;
		activeweapon = WEAPON_FIVE;
		currentweapon = &weapons[4];
		refreshInformations();
	}

	else if(weaponbuttons[5].contains(x, y) && weaponbuttonstates[5] == BUTTON_PRESSED) {
		weaponbuttonstates[5] = BUTTON_PERFORMED;
		activeweapon = WEAPON_SIX;
		currentweapon = &weapons[5];
		refreshInformations();
	}

	else if(weaponbuttons[6].contains(x, y) && weaponbuttonstates[6] == BUTTON_PRESSED) {
		weaponbuttonstates[6] = BUTTON_PERFORMED;
		activeweapon = WEAPON_SEVEN;
		currentweapon = &weapons[6];
		refreshInformations();
	}

	else if(weaponbuttons[7].contains(x, y) && weaponbuttonstates[7] == BUTTON_PRESSED) {
		weaponbuttonstates[7] = BUTTON_PERFORMED;
		activeweapon = WEAPON_EIGHT;
		currentweapon = &weapons[7];
		refreshInformations();
	}
	else {
		weaponbuttonstates[0] = BUTTON_CANCELED;
		weaponbuttonstates[1] = BUTTON_CANCELED;
		weaponbuttonstates[2] = BUTTON_CANCELED;
		weaponbuttonstates[3] = BUTTON_CANCELED;
		weaponbuttonstates[4] = BUTTON_CANCELED;
		weaponbuttonstates[5] = BUTTON_CANCELED;
		weaponbuttonstates[6] = BUTTON_CANCELED;
		weaponbuttonstates[7] = BUTTON_CANCELED;
	}
}

void ShopCanvas::weaponSettingsFocus(int x, int y) {
	if(weaponbuttonstates[0] != BUTTON_PRESSED) {
		if(weaponbuttons[0].contains(x, y)) {
			weaponbuttonstates[0] = BUTTON_FOCUS;
		}
		else {
			weaponbuttonstates[0] = BUTTON_NONE;
		}
	}

	if(weaponbuttonstates[1] != BUTTON_PRESSED) {
		if(weaponbuttons[1].contains(x, y)) {
			weaponbuttonstates[1] = BUTTON_FOCUS;
		}
		else {
			weaponbuttonstates[1] = BUTTON_NONE;
		}
	}

	if(weaponbuttonstates[2] != BUTTON_PRESSED) {
		if(weaponbuttons[2].contains(x, y)) {
			weaponbuttonstates[2] = BUTTON_FOCUS;
		}
		else {
			weaponbuttonstates[2] = BUTTON_NONE;
		}
	}

	if(weaponbuttonstates[3] != BUTTON_PRESSED) {
		if(weaponbuttons[3].contains(x, y)) {
			weaponbuttonstates[3] = BUTTON_FOCUS;
		}
		else {
			weaponbuttonstates[3] = BUTTON_NONE;
		}
	}

	if(weaponbuttonstates[4] != BUTTON_PRESSED) {
		if(weaponbuttons[4].contains(x, y)) {
			weaponbuttonstates[4] = BUTTON_FOCUS;
		}
		else {
			weaponbuttonstates[4] = BUTTON_NONE;
		}
	}

	if(weaponbuttonstates[5] != BUTTON_PRESSED) {
		if(weaponbuttons[5].contains(x, y)) {
			weaponbuttonstates[5] = BUTTON_FOCUS;
		}
		else {
			weaponbuttonstates[5] = BUTTON_NONE;
		}
	}

	if(weaponbuttonstates[6] != BUTTON_PRESSED) {
		if(weaponbuttons[6].contains(x, y)) {
			weaponbuttonstates[6] = BUTTON_FOCUS;
		}
		else {
			weaponbuttonstates[6] = BUTTON_NONE;
		}
	}

	if(weaponbuttonstates[7] != BUTTON_PRESSED) {
		if(weaponbuttons[7].contains(x, y)) {
			weaponbuttonstates[7] = BUTTON_FOCUS;
		}
		else {
			weaponbuttonstates[7] = BUTTON_NONE;
		}
	}
}

void ShopCanvas::trackSettingsPressed(int x, int y) {
	if(trackbuttons[0].contains(x, y)) {
		trackbuttonstates[0] = BUTTON_PRESSED;
	}

	if(trackbuttons[1].contains(x, y)) {
		trackbuttonstates[1] = BUTTON_PRESSED;
	}

	if(trackbuttons[2].contains(x, y)) {
		trackbuttonstates[2] = BUTTON_PRESSED;
	}

	if(trackbuttons[3].contains(x, y)) {
		trackbuttonstates[3] = BUTTON_PRESSED;
	}
}

void ShopCanvas::trackSettingsReleased(int x, int y) {
	if(trackbuttons[0].contains(x, y) && trackbuttonstates[0] == BUTTON_PRESSED) {
		trackbuttonstates[0] = BUTTON_PERFORMED;
		activetrack = TRACK_ONE;
		currenttrack = &tracks[0];
		refreshInformations();
	}

	else if(trackbuttons[1].contains(x, y) && trackbuttonstates[1] == BUTTON_PRESSED) {
		trackbuttonstates[1] = BUTTON_PERFORMED;
		activetrack = TRACK_TWO;
		currenttrack = &tracks[1];
		refreshInformations();
	}

	else if(trackbuttons[2].contains(x, y) && trackbuttonstates[2] == BUTTON_PRESSED) {
		trackbuttonstates[2] = BUTTON_PERFORMED;
		activetrack = TRACK_THREE;
		currenttrack = &tracks[2];
		refreshInformations();
	}

	else if(trackbuttons[3].contains(x, y) && trackbuttonstates[3] == BUTTON_PRESSED) {
		trackbuttonstates[3] = BUTTON_PERFORMED;
		activetrack = TRACK_FOUR;
		currenttrack = &tracks[3];
		refreshInformations();
	}
	else {
		trackbuttonstates[0] = BUTTON_CANCELED;
		trackbuttonstates[1] = BUTTON_CANCELED;
		trackbuttonstates[2] = BUTTON_CANCELED;
		trackbuttonstates[3] = BUTTON_CANCELED;
	}
}

void ShopCanvas::trackSettingsFocus(int x, int y) {
	if(trackbuttonstates[0] != BUTTON_PRESSED) {
		if(trackbuttons[0].contains(x, y)) {
			trackbuttonstates[0] = BUTTON_FOCUS;
		}
		else {
			trackbuttonstates[0] = BUTTON_NONE;
		}
	}

	if(trackbuttonstates[1] != BUTTON_PRESSED) {
		if(trackbuttons[1].contains(x, y)) {
			trackbuttonstates[1] = BUTTON_FOCUS;
		}
		else {
			trackbuttonstates[1] = BUTTON_NONE;
		}
	}

	if(trackbuttonstates[2] != BUTTON_PRESSED) {
		if(trackbuttons[2].contains(x, y)) {
			trackbuttonstates[2] = BUTTON_FOCUS;
		}
		else {
			trackbuttonstates[2] = BUTTON_NONE;
		}
	}

	if(trackbuttonstates[3] != BUTTON_PRESSED) {
		if(trackbuttons[3].contains(x, y)) {
			trackbuttonstates[3] = BUTTON_FOCUS;
		}
		else {
			trackbuttonstates[3] = BUTTON_NONE;
		}
	}
}

void ShopCanvas::effectSettingsPressed(int x, int y) {

}

void ShopCanvas::effectSettingsReleased(int x, int y) {

}

void ShopCanvas::effectSettingsFocus(int x, int y) {

}

void ShopCanvas::keyPressed(int key) {
//	gLogi("ShopCanvas") << "keyPressed:" << key;
}

void ShopCanvas::keyReleased(int key) {
//	gLogi("ShopCanvas") << "keyReleased:" << key;
}

void ShopCanvas::charPressed(unsigned int codepoint) {
//	gLogi("ShopCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void ShopCanvas::mouseMoved(int x, int y) {
//	gLogi("ShopCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
	tabButtonFocus(x, y);
	updateButtonState(x, y);
	containerButtonFocus(x, y);
}

void ShopCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("ShopCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void ShopCanvas::mousePressed(int x, int y, int button) {
//	gLogi("ShopCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
	checkButtonPressed(x, y, button);
	containerButtonPressed(x, y);
	tabButtonPressed(x, y);
}

void ShopCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("ShopCanvas") << "mouseReleased" << ", button:" << button;
	checkButtonReleased(x, y, button);
	containerButtonReleased(x, y);
	tabButtonReleased(x, y);
}

void ShopCanvas::mouseScrolled(int x, int y) {
//	gLogi("ShopCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void ShopCanvas::mouseEntered() {

}

void ShopCanvas::mouseExited() {

}

void ShopCanvas::windowResized(int w, int h) {

}

void ShopCanvas::showNotify() {

}

void ShopCanvas::hideNotify() {

}
