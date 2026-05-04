/*
* gCanvas.cpp
*
*  Created on: May 6, 2020
*      Author: noyan
*/


#include <MainMenu.h>
#include "gCanvas.h"


gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

gCanvas::~gCanvas() {
}

void gCanvas::setup() {
	map.loadImage("haritalar/arkaplan1.jpg");
	tank1.loadImage("oyun/PNG/Hulls_Color_A/Hull_01.png");
	for(int i = 0; i < trackframenum; i++) {
		track[i].loadImage("oyun/PNG/Tracks/Track_1_" + gToStr(i) + ".png");
	}
	gun.loadImage("oyun/PNG/Weapon_Color_A/Gun_01.png");
	bulletimage.loadImage("oyun/PNG/Effects/Exhaust_Fire.png");
	enemy.loadImage("oyun/PNG/Hulls_Color_B/Hull_01.png");
	minimap.loadImage("haritalar/radar1.png");
	minimapradarsign1.loadImage("haritalar/radarisaret1.png");
	minimapradarsign2.loadImage("haritalar/radarisaret2.png");

	gui_charactericon.loadImage("gui/erkekikon.png");
	gui_healthicon.loadImage("gui/element_0098_Layer-100.png");
	gui_bulleticon.loadImage("PNG/bulleticon.png");
	gui_barframe.loadImage("gui/element_0092_Layer-94.png");
	gui_barbackground.loadImage("gui/element_0077_Layer-79.png");
	gui_healthbar.loadImage("gui/element_0076_Layer-78.png");

	gui_gameoverdialogue.loadImage("gui/dialogue_gameover.png");
	gui_pausedialogue.loadImage("gui/dialogue_pause.png");
	gui_windialogue.loadImage("gui/dialogue_youwin.png");
	replaybutton.loadImage("gui/button_replay.png");
	mainmbutton.loadImage("gui/button_mainmenu.png");
	continuebutton.loadImage("gui/button_continue.png");
	nextlevelbutton.loadImage("gui/button_nextlevel.png");

	namefont.loadFont("FreeSans.ttf", 20);

	keystate = KEY_NONE;
	cx = 0;
	cy = 0;
	cw = tank1.getWidth() * 0.4;
	ch = tank1.getHeight() * 0.4;
	cwh = cw / 2;
	chh = ch / 2;
	cdx = 0.0f;
	cdy = 0.0f;
	cangle = 0.0f;
	cangletr = 0.0f;
	canglegun = 0.0f;
	cspeed = 4.0f;

	tx = 0;
	ty = 0;
	tw = track[0].getWidth() * 0.4;
	th = track[0].getHeight() * 0.4;
	twh = tw / 2;
	thh = th / 2;
	tdx = 0.0f;
	tdy = 0.0f;

	gx = 0;
	gy = 0;
	gw = gun.getWidth() * 0.4;
	gh = gun.getHeight() * 0.4;
	gwh = gw / 2;
	ghh = gh / 2;
	gdx = 0.0f;
	gdy = 0.0f;

	camx = 0.0f;
	camy = 0.0f;
	camw = getWidth();
	camh = getHeight();
	camleftlimit = (float)getWidth() / 4.0f;
	camrightlimit = (float)getScreenWidth() * 3.0f / 4.0f;
	camtoplimit = (float)getHeight() / 4.0f;
	cambottomlimit = (float)getHeight() * 3.0f / 4.0f;
	mapw = map.getWidth();
	maph = map.getHeight();
	trackframecounter = 0;
	trackframeno = 0;
	trackframecounterlimit = 2;

	fontx = cwh;
	fonty = chh;

	minimapw = minimap.getWidth();
	minimaph = minimap.getHeight();
	minimapx = getWidth() - minimapw - minimapw / 4;
	minimapy = minimapw / 4;

	ex = 0;
	ey = 0;
	ew = enemy.getWidth() * 0.4;
	eh = enemy.getHeight() * 0.4;
	ewh = enemy.getWidth() / 2;
	ehh = enemy.getHeight() / 2;

	gcix = gui_charactericon.getWidth() / 4;
	gciy = gcix;
	ghix = gui_charactericon.getWidth() + 2 * gcix;
	ghiy = gciy + gui_charactericon.getHeight() / 2 - 5 - gui_healthicon.getHeight();
	gbix = ghix;
	gbiy = gciy + gui_charactericon.getHeight() / 2 + 5;
	gbiw = gui_bulleticon.getWidth() * 0.1;
	gbih = gui_bulleticon.getHeight() * 0.1;
	ghbfx = ghix + gui_healthicon.getWidth() + gcix;
	ghbfy = ghiy + (gui_healthicon.getHeight() - gui_barframe.getHeight()) / 2;
	gbbfx = ghbfx;
	gbbfy = gbiy + (gui_bulleticon.getHeight() - gui_barframe.getHeight()) / 2;
	ghbbx = ghbfx + 4;
	ghbby = ghbfy + 8;
	gbbbx = gbbfx + 4;
	gbbby = gbbfy + 8;
	gbw = gui_healthbar.getWidth();
	gbh = gui_healthbar.getHeight();
	chealth = 100;
	bulletamt = 5;

	dialoguew = gui_gameoverdialogue.getWidth();
	dialogueh = gui_gameoverdialogue.getHeight();
	dialoguewidthhalf = dialoguew / 2;
	dialogueheighthalf = dialogueh / 2;
	dialoguex = (getWidth() - dialoguew) / 2.0f;
	dialoguey = (getHeight() - dialogueh) / 2.0f;
	score = 0;
	leftbw = replaybutton.getWidth();
	leftbh = replaybutton.getHeight();
	leftbx = dialoguex + dialoguewidthhalf - leftbw * 5 / 4;
	leftby = dialoguey + dialogueh - leftbh * 5 / 2;
	rightbw = mainmbutton.getWidth();
	rightbh = mainmbutton.getHeight();
	rightbx = dialoguex + dialoguewidthhalf + leftbw / 4;
	rightby = leftby;
	scorey = dialoguey + dialogueh * 60 / 100;
	scorex = dialoguex + dialoguewidthhalf - namefont.getStringWidth("0") / 2;
	scoretitley = scorey - namefont.getSize() * 9 / 8;
	scoretitlex = dialoguex + dialoguewidthhalf - namefont.getStringWidth("SCORE") / 2;

	fpscounterx = minimapx + 20.0f;
	fpscountery = minimapy + minimaph + 30.0f;

}

void gCanvas::update() {
	moveCharacter();
	moveCamera();
	playAnimations();
	moveBullets();
}

void gCanvas::drawCharacter() {
	float pivotoffset = ch * 0.6f;

	track[trackframeno].draw(cx + 15, cy, tw, th, cwh - 15, pivotoffset, cangle);
	track[trackframeno].draw(cx + 70, cy, tw, th, cwh - 70, pivotoffset, cangle);

	tank1.draw(cx, cy, cw, ch, cwh, pivotoffset, cangle);

	gun.draw(cx + 40, cy, gw, gh, gwh, gh * 0.85f, canglegun);
}

void gCanvas::draw() {
	drawMap();
	drawBullets();
	drawCharacter();
	setColor(255, 255, 255);
	if(root->getMinimap() == 1) drawMinimap();
	//drawEnemies();
	namefont.drawText("Name", cx + cwh, cy + chh);
	//namefont.drawText(gToStr(bulletamt), gbbbx, gbbby);
	drawGui();
	drawDialogues();

	if(root->getShowFps() == 1) {
	char fpsBuffer[32];
	sprintf(fpsBuffer, "%d FPS", root->getFramerate());
	root->menutitlefont.drawText(fpsBuffer, fpscounterx, fpscountery);
	}
}

void gCanvas::moveCharacter() {
    cdx = 0.0f;
    cdy = 0.0f;

    if(keystate & KEY_A) {
        cangle -= 2.0f;
    }
    if(keystate & KEY_D) {
        cangle += 2.0f;
    }

    if(keystate & KEY_W) {
        cdx = std::sin(gDegToRad(cangle)) * cspeed;
        cdy = -std::cos(gDegToRad(cangle)) * cspeed;
    }
    if(keystate & KEY_S) {
        cdx = -std::sin(gDegToRad(cangle)) * cspeed;
        cdy = std::cos(gDegToRad(cangle)) * cspeed;
    }

	if(keystate == KEY_ESC) {
		gamestate = GAMESTATE_PAUSE;
		gLogi("gCanvas") << "aaa";
	}

    cx += cdx;
    cy += cdy;
}

void gCanvas::playAnimations() {
    if(cdx != 0.0f || cdy != 0.0f) {
        trackframecounter++;
        if(trackframecounter >= trackframecounterlimit) {
            trackframeno = (trackframeno + 1) % trackframenum;
            trackframecounter = 0;
        }
    }
}

void gCanvas::moveCamera() {
	camleftlimit = (float)getWidth() / 4.0f;
	if(camx <= 0.0f) camleftlimit = 0.0f;
	camrightlimit = (float)getWidth() * 3.0f / 4.0f;
	if(camx + camw >= mapw) camrightlimit = getWidth();
	if(cx < camleftlimit || cx + cw > camrightlimit) {
		cx -= cdx;
		camx += cdx;
		if(camx < 0.0f) {
			camx = 0.0f;
		}
		if(camx + camw > mapw) {
			camx = mapw - camw;
		}
	}

	camtoplimit = (float)getHeight() / 4.0f;
	if(camy <= 0.0f) camtoplimit = 0.0f;
	cambottomlimit = (float)getHeight() * 3.0f / 4.0f;
	if(camy + camh >= maph) cambottomlimit = getHeight();
	if(cy < camtoplimit || cy + ch > cambottomlimit) {
		cy -= cdy;
		camy += cdy;
		if(camy < 0.0f) {
			camy = 0.0f;
		}
		if(camy + camh > maph) {
			camy = maph - camh;
		}
	}
}

void gCanvas::drawMap() {
	map.drawSub(0, 0, getWidth(), getHeight(), camx, camy, camw, camh);
}

void gCanvas::moveBullets() {
    for(int i = bullets.size() - 1; i >= 0; i--) {
        bullets[i][0] += bullets[i][2];
        bullets[i][1] += bullets[i][3];
        if(bullets[i][0] < camx + 3 || bullets[i][0] >= camx + camw + 3 ||
           bullets[i][1] < camy + 3 || bullets[i][1] >= camy + camh + 3) {
            bullets.erase(bullets.begin() + i);
            continue;
        }

        float bx = bullets[i][0];
        float by = bullets[i][1];
        float bx2 = bx + bulletimage.getWidth();
        float by2 = by + bulletimage.getHeight();
     }
    if(bulletamt < 0) bulletamt = 0;
}

void gCanvas::drawBullets() {
	for(int i = 0; i < bullets.size(); i++) {
		bulletimage.draw(bullets[i][0] - camx, bullets[i][1] - camy, bulletimage.getWidth(), bulletimage.getHeight()/*, bulletimage.getWidth() / 2, bulletimage.getHeight() / 2*/, bullets[i][4]);
	}
}
void gCanvas::generateBullet(float bulletX, float bulletY, float bulletDx, float bulletDy, float bulletRotation, int bulletSender) {
	std::vector<float> newbullet;
	newbullet.push_back(bulletX);
	newbullet.push_back(bulletY);
	newbullet.push_back(bulletDx);
	newbullet.push_back(bulletDy);
	newbullet.push_back(bulletRotation);
	newbullet.push_back((float)bulletSender);
	bullets.push_back(newbullet);
}

void gCanvas::drawMinimap() {
	minimap.draw(minimapx, minimapy);

	float emx = minimapx + 2 + ex / 32;
	float emy = minimapy + 2 + ey / 32;
	minimapradarsign2.draw(emx, emy);

	float pmx = minimapx + 2 + (cx + camx) / 32;
	float pmy = minimapy + 2 + (cy + camy) / 32;
	minimapradarsign1.draw(pmx, pmy);
}

void gCanvas::drawEnemies() {
	enemy.draw(ex, ey, ew, eh);
}

void gCanvas::drawGui() {
	gui_charactericon.draw(gcix, gciy);
	gui_healthicon.draw(ghix, ghiy);
	gui_bulleticon.draw(gbix, gbiy, gbiw, gbih);
	gui_barbackground.draw(ghbbx, ghbby);
	gui_healthbar.drawSub(ghbbx, ghbby, gbw * chealth / 100, gbh, gbw - (gbw * chealth / 100), 0, gbw, gbh);
	gui_barframe.draw(ghbfx, ghbfy);
	namefont.drawText(gToStr(bulletamt), gbix * 1.4, gbiy * 1.4);
}

void gCanvas::drawDialogues() {

	if(gamestate == GAMESTATE_PAUSE) {
		dialogueshown = true;
		gui_pausedialogue.draw(dialoguex, dialoguey);
		setColor(0, 0, 0, 228);
		namefont.drawText("SCORE", scoretitlex + 4, scoretitley + 4);
		namefont.drawText(gToStr(score), scorex + 6, scorey + 6);
		setColor(212, 212, 212);
		namefont.drawText("SCORE", scoretitlex, scoretitley);
		namefont.drawText(gToStr(score), scorex, scorey);
		setColor(255, 255, 255);
		continuebutton.draw(leftbx, leftby);
		mainmbutton.draw(rightbx, rightby);
	}

	if(gamestate == GAMESTATE_WIN) {
		dialogueshown = true;
		gui_windialogue.draw(dialoguex, dialoguey);
		setColor(0, 0, 0, 228);
		namefont.drawText("SCORE", scoretitlex + 4, scoretitley + 4);
		namefont.drawText(gToStr(score), scorex + 6, scorey + 6);
		setColor(212, 212, 212);
		namefont.drawText("SCORE", scoretitlex, scoretitley);
		namefont.drawText(gToStr(score), scorex, scorey);
		setColor(255, 255, 255);
		nextlevelbutton.draw(leftbx, leftby);
		mainmbutton.draw(rightbx, rightby);
	}

	if(gamestate == GAMESTATE_PLAY) {
		dialogueshown = false;
	}

	if(!dialogueshown) return;
	if(gamestate == GAMESTATE_GAMEOVER) {
		gui_gameoverdialogue.draw(dialoguex, dialoguey);
		setColor(0, 0, 0, 228);
		namefont.drawText("SCORE", scoretitlex + 4, scoretitley + 4);
		namefont.drawText(gToStr(score), scorex + 6, scorey + 6);
		setColor(212, 212, 212);
		namefont.drawText("SCORE", scoretitlex, scoretitley);
		namefont.drawText(gToStr(score), scorex, scorey);
		setColor(255, 255, 255);
		replaybutton.draw(leftbx, leftby);
		mainmbutton.draw(rightbx, rightby);
	}
}

void gCanvas::keyPressed(int key) {
//	gLogi("gCanvas") << "keyPressed:" << key;
	int pressedkey = KEY_NONE;
	switch(key) {
		case G_KEY_W:
			pressedkey = KEY_W;
			break;
		case G_KEY_S:
			pressedkey = KEY_S;
			break;
		case G_KEY_D:
			pressedkey = KEY_D;
			break;
		case G_KEY_A:
			pressedkey = KEY_A;
			break;
		case G_KEY_ESC:
			pressedkey = KEY_ESC;
			break;
		default:
			break;
	}
	keystate |= pressedkey;
}

void gCanvas::keyReleased(int key) {
//	gLogi("gCanvas") << "keyReleased:" << key;
	int pressedkey;
	switch(key) {
		case G_KEY_W:
			pressedkey = KEY_W;
			break;
		case G_KEY_S:
			pressedkey = KEY_S;
			break;
		case G_KEY_D:
			pressedkey = KEY_D;
			break;
		case G_KEY_A:
			pressedkey = KEY_A;
			break;
		case G_KEY_ESC:
			pressedkey = KEY_ESC;
			break;
		default:
			break;
	}
	keystate &= ~pressedkey;
}

void gCanvas::charPressed(unsigned int codepoint) {
//	gLogi("gCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void gCanvas::mouseMoved(int x, int y) {
	//applySensitivity();

    canglegun = (int)(
        gRadToDeg(
            std::atan2(
                y - (cy + chh),
                x - (cx + cwh)
            )
        ) + 90.0f + 360.0f
    ) % 360;
}

void gCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mousePressed(int x, int y, int button) {
//	gLogi("gCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseReleased" << ", button:" << button;

	if(gamestate == GAMESTATE_GAMEOVER) {
		if(x >= leftbx && x < leftbx + leftbw && y >= leftby && y < leftby + leftbh) {
			gCanvas* cnv = new gCanvas(root);
			root->setCurrentCanvas(cnv);
			return;
		}
	}
	if(gamestate == GAMESTATE_PAUSE) {
		if(x >= leftbx && x < leftbx + leftbw && y >= leftby && y < leftby + leftbh) {
			gamestate = GAMESTATE_PLAY;
		}
	}

	if(gamestate == GAMESTATE_GAMEOVER || gamestate == GAMESTATE_WIN || gamestate == GAMESTATE_PAUSE) {
		if(x >= rightbx && x < rightbx + rightbw && y >= rightby && y < rightby + rightbh) {
			mainMenu* cnv = new mainMenu(root);
			root->setCurrentCanvas(cnv);
			return;
		}
	}
	if(dialogueshown) return;

	float px = (cx + 40) + camx + gwh;
	float py = cy + camy + gh * 0.85;
	float br = canglegun;
	float bx = px + std::sin(gDegToRad(br + muzzleangle)) * muzzledistance - bulletimage.getHeight() / 2;
	float by = py - std::cos(gDegToRad(br + muzzleangle)) * muzzledistance - bulletimage.getWidth() / 2;
	float bdx = std::sin(gDegToRad(br)) * 8.0f;
	float bdy = -std::cos(gDegToRad(br)) * 8.0f;
	int bs = 0; //0:character, 1:enemy
	bulletamt--;
	if(bulletamt >= 0)
	generateBullet(bx, by, bdx, bdy, br, bs);

}

void gCanvas::mouseScrolled(int x, int y) {
//	gLogi("gCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseEntered() {

}

void gCanvas::mouseExited() {

}

void gCanvas::windowResized(int w, int h) {

}

void gCanvas::showNotify() {

}

void gCanvas::hideNotify() {

}

void gCanvas::applySensitivity() {
	if(root->getSensitivity() > 0)	applysensivity = (root->getSensitivity() * 0.25);
	else applysensivity = 0.012;
}

