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
	selectedSetup();
	hullSetup();
	weaponSetup();
	trackSetup();
	camSetup();
	guiSetup();
	mapSetup();
	enemySetup();
	keyControls();
	fpsSetup();
	skillsguiSetup();
	skillsSetup();
}

void gCanvas::update() {
	moveCharacter();
	moveCamera();
	playAnimations();
	moveBullets();

	//updateSkills();
	checkSkillPickup();
	updateSkillTimers();
}

void gCanvas::draw() {
	drawMap();
	drawBullets();
	drawCharacter();
	setColor(255, 255, 255);
	if(root->getMinimap() == 1) drawMinimap();
	//drawEnemies();
	namefont.drawText(root->getName(), hx + hwh, hy + hhh);
	//namefont.drawText(gToStr(bulletamt), gbbbx, gbbby);
	drawGui();
	drawDialogues();
	fpsDraw();
	drawWorldSkills();
	drawSkillGui();
}

void gCanvas::skillsSetup() {
	skills.clear();

	SkillItem poisonskill;
	poisonskill.type = 0;

	poisonskill.w = poison.getWidth() * 0.5f;
	poisonskill.h = poison.getHeight() * 0.5f;

	poisonskill.x = (gRandomf() + 1.0f) * 0.1f * (mapw - poisonskill.w);
	poisonskill.y = (gRandomf() + 1.0f) * 0.1f * (maph - poisonskill.h);

	poisonskill.spawned = true;
	poisonskill.owned = false;
	poisonskill.respawnTimer = 0.0f;
	poisonskill.activeTimer = 0.0f;
	poisonskill.guiAlpha = 80;

	SkillItem bombskill;
	bombskill.type = 1;

	bombskill.w = bomb.getWidth() * 0.5f;
	bombskill.h = bomb.getHeight() * 0.5f;

	bombskill.x = (gRandomf() + 1.0f) * 0.1f * (mapw - bombskill.w);
	bombskill.y = (gRandomf() + 1.0f) * 0.1f * (maph - bombskill.h);

	bombskill.spawned = true;
	bombskill.owned = false;
	bombskill.respawnTimer = 0.0f;
	bombskill.activeTimer = 0.0f;
	bombskill.guiAlpha = 80;

	SkillItem healingskill;
	healingskill.type = 2;

	healingskill.w = healing.getWidth() * 0.5f;
	healingskill.h = healing.getHeight() * 0.5f;

	healingskill.x = (gRandomf() + 1.0f) * 0.1f * (mapw - healingskill.w);
	healingskill.y = (gRandomf() + 1.0f) * 0.1f * (maph - healingskill.h);

	healingskill.spawned = true;
	healingskill.owned = false;
	healingskill.respawnTimer = 0.0f;
	healingskill.activeTimer = 0.0f;
	healingskill.guiAlpha = 80;

	SkillItem piercingbulletskill;
	piercingbulletskill.type = 3;

	piercingbulletskill.w = piercingbullet.getWidth() * 0.5f;
	piercingbulletskill.h = piercingbullet.getHeight() * 0.5f;

	piercingbulletskill.x = (gRandomf() + 1.0f) * 0.1f * (mapw - piercingbulletskill.w);
	piercingbulletskill.y = (gRandomf() + 1.0f) * 0.1f * (maph - piercingbulletskill.h);

	piercingbulletskill.spawned = true;
	piercingbulletskill.owned = false;
	piercingbulletskill.respawnTimer = 0.0f;
	piercingbulletskill.activeTimer = 0.0f;
	piercingbulletskill.guiAlpha = 80;

	SkillItem speedboostskill;
	speedboostskill.type = 4;

	speedboostskill.w = speedboost.getWidth() * 0.5f;
	speedboostskill.h = speedboost.getHeight() * 0.5f;

	speedboostskill.x = (gRandomf() + 1.0f) * 0.1f * (mapw - speedboostskill.w);
	speedboostskill.y = (gRandomf() + 1.0f) * 0.1f * (maph - speedboostskill.h);

	speedboostskill.spawned = true;
	speedboostskill.owned = false;
	speedboostskill.respawnTimer = 0.0f;
	speedboostskill.activeTimer = 0.0f;
	speedboostskill.guiAlpha = 80;

	skills.push_back(poisonskill);
	skills.push_back(bombskill);
	skills.push_back(healingskill);
	skills.push_back(piercingbulletskill);
	skills.push_back(speedboostskill);

	gLogi("x") << poisonskill.x;
	gLogi("y") << poisonskill.y;

	gLogi("x") << bombskill.x;
	gLogi("y") << bombskill.y;
}

void gCanvas::drawWorldSkills() {
	for(int i = 0; i < skills.size(); i++) {

		if(!skills[i].spawned) continue;

		switch(skills[i].type) {

		case 0:
			poison.draw(
				skills[i].x - camx,
				skills[i].y - camy,
				skills[i].w,
				skills[i].h
			);
			break;
		case 1:
			bomb.draw(
				skills[i].x - camx,
				skills[i].y - camy,
				skills[i].w,
				skills[i].h
			);
			break;
		case 2:
			healing.draw(
				skills[i].x - camx,
				skills[i].y - camy,
				skills[i].w,
				skills[i].h
			);
			break;
		case 3:
			piercingbullet.draw(
				skills[i].x - camx,
				skills[i].y - camy,
				skills[i].w,
				skills[i].h
			);
			break;
		case 4:
			speedboost.draw(
				skills[i].x - camx,
				skills[i].y - camy,
				skills[i].w,
				skills[i].h
			);
			break;
		}
	}
}

void gCanvas::drawSkillGui() {

	for(int i = 0; i < skills.size(); i++) {

		setColor(255, 255, 255, skills[i].guiAlpha);

		switch(skills[i].type) {

		case 0:
			poison.draw(skillguix, skillguiy);
			break;
		case 1:
			bomb.draw(skillguix + skillguiw, skillguiy);
			break;
		case 2:
			healing.draw(skillguix + skillguiw * 2, skillguiy);
			break;
		case 3:
			piercingbullet.draw(skillguix + skillguiw * 3, skillguiy);
			break;
		case 4:
			speedboost.draw(skillguix + skillguiw * 4, skillguiy);
			break;
		}
	}

	setColor(255,255,255);
}

void gCanvas::checkSkillPickup() {

	for(int i = 0; i < skills.size(); i++) {

		if(!skills[i].spawned) continue;

		bool collision =
			hx < skills[i].x + skills[i].w &&
			hx + hw > skills[i].x &&
			hy < skills[i].y + skills[i].h &&
			hy + hh > skills[i].y;

		if(collision) {

			skills[i].spawned = false;

			skills[i].owned = true;

			skills[i].guiAlpha = 230;

			skills[i].respawnTimer = 600.0f;
		}
	}
}

void gCanvas::updateSkillTimers() {
	for(int i = 0; i < skills.size(); i++) {
		if(skills[i].spawned) continue;

		if(skills[i].respawnTimer > 0.0f) {
			skills[i].respawnTimer--;
		}

		if(skills[i].respawnTimer <= 0.0f && !skills[i].owned) {
			skills[i].x =(gRandomf() + 1.0f) * (mapw - skills[i].w);
			skills[i].y = (gRandomf() + 1.0f) * (maph - skills[i].h);
			skills[i].spawned = true;
			skills[i].guiAlpha = 80;
			skills[i].activeTimer = 0.0f;
		}
	}
}

void gCanvas::skillsguiSetup() {
	poison.loadImage("PNG/ICONS/poison.png");
	bomb.loadImage("PNG/ICONS/bomb.png");
	healing.loadImage("PNG/ICONS/healing.png");
	speedboost.loadImage("PNG/ICONS/speedboost.png");
	piercingbullet.loadImage("PNG/ICONS/piercingbullet.png");

	skillspace = 100;
	skillguiw = poison.getWidth();
	skillguih = poison.getHeight();
	skillguix = skillguiw - (skillspace / 2);
	skillguiy = getHeight() - skillguih - (skillspace / 4);
}

void gCanvas::skillsguiDraw() {
	setColor(255, 255, 255, 110);
	poison.draw(skillguix, skillguiy);
	setColor(255, 255, 255, 230);
	bomb.draw(skillguix + skillspace, skillguiy);
	healing.draw(skillguix + skillspace * 2, skillguiy);
	speedboost.draw(skillguix + skillspace * 3, skillguiy , skillguiw * 1.1, skillguih * 1.1);
	piercingbullet.draw(skillguix + skillspace * 4, skillguiy);
}

void gCanvas::selectedSetup() {
	selectedhull = root->getHull();
	selectedweapon = root->getWeapon();
	selectedtrack = root->getTrack();
	selectedhullcolor = root->getHullColor();
	selectedweaponcolor = root->getWeaponColor();
}

void gCanvas::hullSetup() {
	hull.loadImage("oyun/PNG/Hulls_Color_" + gToStr(selectedhullcolor) + "/Hull_0" + gToStr(selectedhull) + ".png");
	hx = 0;
	hy = 0;
	hw = hull.getWidth() * 0.4;
	hh = hull.getHeight() * 0.4;
	hwh = hw / 2;
	hhh = hh / 2;
	hdx = 0.0f;
	hdy = 0.0f;
	cangle = 0.0f;
	cangletr = 0.0f;
	canglegun = 0.0f;
	hspeed = selectedtrack + 3;
	hhealth = (selectedhull * 20 ) + 100;
	keystate = KEY_NONE;
}

void gCanvas::weaponSetup() {
	weapon.loadImage("oyun/PNG/Weapon_Color_" + gToStr(selectedweaponcolor) + "/Gun_0" + gToStr(selectedweapon) + ".png");
	bulletimage.loadImage("oyun/PNG/Effects/Exhaust_Fire.png");
	wx = 0;
	wy = 0;
	ww = weapon.getWidth() * 0.4;
	wh = weapon.getHeight() * 0.4;
	wwh = ww / 2;
	whh = wh / 2;
	wdx = 0.0f;
	wdy = 0.0f;
	bulletamt = 5;
}

void gCanvas::trackSetup() {
	for(int i = 0; i < trackframenum; i++) {
		track[i].loadImage("oyun/PNG/Tracks/Track_" + gToStr(selectedtrack) + "_" + gToStr(i) + ".png");
	}
	tx = 0;
	ty = 0;
	tw = track[0].getWidth() * 0.4;
	th = track[0].getHeight() * 0.4;
	twh = tw / 2;
	thh = th / 2;
	tdx = 0.0f;
	tdy = 0.0f;

	trackframecounter = 0;
	trackframeno = 0;
	trackframecounterlimit = 2;

}

void gCanvas::camSetup() {
	camx = 0.0f;
	camy = 0.0f;
	camw = getWidth();
	camh = getHeight();
	camleftlimit = (float)getWidth() / 4.0f;
	camrightlimit = (float)getScreenWidth() * 3.0f / 4.0f;
	camtoplimit = (float)getHeight() / 4.0f;
	cambottomlimit = (float)getHeight() * 3.0f / 4.0f;

}

void gCanvas::mapSetup() {
	map.loadImage("haritalar/arkaplan1.jpg");
	//map.loadImage("haritalar/aa.png");
	minimap.loadImage("haritalar/radar1.png");
	minimapradarsign1.loadImage("haritalar/radarisaret1.png");
	minimapradarsign2.loadImage("haritalar/radarisaret2.png");
	mapw = map.getWidth();
	maph = map.getHeight();
	minimapw = minimap.getWidth();
	minimaph = minimap.getHeight();
	minimapx = getWidth() - minimapw - minimapw / 4;
	minimapy = minimapw / 4;

}

void gCanvas::enemySetup() {
	enemy.loadImage("oyun/PNG/Hulls_Color_3/Hull_01.png");
	ex = 0;
	ey = 0;
	ew = enemy.getWidth() * 0.4;
	eh = enemy.getHeight() * 0.4;
	ewh = enemy.getWidth() / 2;
	ehh = enemy.getHeight() / 2;
}

void gCanvas::guiSetup() {
	namefont.loadFont("FreeSans.ttf", 20);
	fontx = hwh;
	fonty = hhh;
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

}

void gCanvas::fpsSetup() {
	fpscounterx = minimapx + 20.0f;
	fpscountery = minimapy + minimaph + 30.0f;
}

void gCanvas::fpsDraw() {
	if(root->getShowFps() == 1) {
	char fpsBuffer[32];
	sprintf(fpsBuffer, "%d FPS", root->getFramerate());
	root->menutitlefont.drawText(fpsBuffer, fpscounterx, fpscountery);
	}
}

void gCanvas::drawCharacter() {
	float pivotoffset = hh * 0.6f;

	track[trackframeno].draw(hx + 15, hy, tw, th, hwh - 15, pivotoffset, cangle);
	track[trackframeno].draw(hx + 70, hy, tw, th, hwh - 70, pivotoffset, cangle);

	hull.draw(hx, hy, hw, hh, hwh, pivotoffset, cangle);

	weapon.draw(hx + 40, hy, ww, wh, wwh, wh * 0.85f, canglegun);
}

void gCanvas::moveCharacter() {
    hdx = 0.0f;
    hdy = 0.0f;

    if(keystate & KEY_A) {
        cangle -= 2.0f;
    }
    if(keystate & KEY_D) {
        cangle += 2.0f;
    }

    if(keystate & KEY_W) {
        hdx = std::sin(gDegToRad(cangle)) * hspeed;
        hdy = -std::cos(gDegToRad(cangle)) * hspeed;
    }
    if(keystate & KEY_S) {
        hdx = -std::sin(gDegToRad(cangle)) * hspeed;
        hdy = std::cos(gDegToRad(cangle)) * hspeed;
    }

	if(keystate == KEY_ESC) {
		gamestate = GAMESTATE_PAUSE;
	}

    hx += hdx;
    hy += hdy;
}

void gCanvas::playAnimations() {
    if(hdx != 0.0f || hdy != 0.0f) {
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
	if(hx < camleftlimit || hx + hw > camrightlimit) {
		hx -= hdx;
		camx += hdx;
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
	if(hy < camtoplimit || hy + hh > cambottomlimit) {
		hy -= hdy;
		camy += hdy;
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

	float pmx = minimapx + 2 + (hx + camx) / 32;
	float pmy = minimapy + 2 + (hy + camy) / 32;
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
	gui_healthbar.drawSub(ghbbx, ghbby, gbw * hhealth / 100, gbh, gbw - (gbw * hhealth / 100), 0, gbw, gbh);
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

	if(key == fkey)pressedkey = KEY_W;

	if(key == backkey)pressedkey = KEY_S;

	if(key == leftkey)pressedkey = KEY_A;

	if(key == rightkey)pressedkey = KEY_D;

	if(key == runkey){
		gLogi("asd") << "asd";
	}

	switch(key) {
		case G_KEY_ESC:
			pressedkey = KEY_ESC;
			root->gamestate = root->GAME_PAUSE;
			break;
		default:
			break;
	}

	if(key == G_KEY_ESC) {
		if(root->gamestate == root->GAME_PAUSE) {
			root->gamestate = root->GAME_PLAY;
//			root->getAppManager()->setCursorMode(CURSORMODE_DISABLED);
		}
		else if(root->gamestate == root->GAME_OPTION) {
			root->gamestate = root->GAME_PAUSE;
		}
	}

	if(key == G_KEY_Z) {
		if(!skills.empty() && skills[0].owned) {
			skills[0].owned = false;
			skills[0].guiAlpha = 80;
			skills[0].respawnTimer = 600.0f;
			gLogi("skill") << "poison used";
		}
	}
	if(key == G_KEY_X) {
		if(!skills.empty() && skills[1].owned) {
			skills[1].owned = false;
			skills[1].guiAlpha = 80;
			skills[1].respawnTimer = 600.0f;
			gLogi("skill") << "bomb used";
		}
	}
	if(key == G_KEY_C) {
		if(!skills.empty() && skills[2].owned) {
			skills[2].owned = false;
			skills[2].guiAlpha = 80;
			skills[2].respawnTimer = 600.0f;
			gLogi("skill") << "Healing used";
		}
	}
	if(key == G_KEY_V) {
		if(!skills.empty() && skills[3].owned) {
			skills[3].owned = false;
			skills[3].guiAlpha = 80;
			skills[3].respawnTimer = 600.0f;
			gLogi("skill") << "PB used";
		}
	}
	if(key == G_KEY_B) {
		if(!skills.empty() && skills[4].owned) {
			skills[4].owned = false;
			skills[4].guiAlpha = 80;
			skills[4].respawnTimer = 600.0f;
			gLogi("skill") << "SB used";
		}
	}

	keystate |= pressedkey;
}

void gCanvas::keyReleased(int key) {
//	gLogi("gCanvas") << "keyReleased:" << key;
	int pressedkey = KEY_NONE;

	if(key == fkey) pressedkey = KEY_W;

	if(key == backkey) pressedkey = KEY_S;

	if(key == leftkey)pressedkey = KEY_A;

	if(key == rightkey)pressedkey = KEY_D;

	if(key == runkey){
			gLogi("bbb") << "aaa";
	}

	switch(key) {
	case G_KEY_R:
		break; }

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
                y - (hy + hhh),
                x - (hx + hwh)
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

	float px = (hx + 40) + camx + wwh;
	float py = hy + camy + wh * 0.85;
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

void gCanvas::keyControls() {
	fkey = root->getForwardKey();
	backkey = root->getBackwardKey();
	rightkey = root->getRightKey();
	leftkey = root->getLeftKey();
	runkey = root->getRunKey();
}
