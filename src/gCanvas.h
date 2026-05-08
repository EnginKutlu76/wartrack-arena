 /*
 * gCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef GCANVAS_H_
#define GCANVAS_H_

#include "gBaseCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gFont.h"


class gCanvas : public gBaseCanvas {
public:
	gCanvas(gApp* root);
	virtual ~gCanvas();

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

	enum {
		GAMESTATE_LOAD, GAMESTATE_PLAY, GAMESTATE_GAMEOVER, GAMESTATE_PAUSE, GAMESTATE_WIN
	};

	static const int KEY_NONE = 0, KEY_W = 1, KEY_S = 2, KEY_D = 4, KEY_A = 8, KEY_ESC = 16;
	static const int trackframenum = 2;

	void moveCharacter();
	void moveCamera();
	void drawCharacter();
	void drawMap();
	void trackAnimation();
	void playAnimations();
	void moveBullets();
	void drawBullets();
	void generateBullet(float bulletX, float bulletY, float bulletDx, float bulletDy, float bulletRotation, int bulletSender);
	void drawMinimap();
	void drawEnemies();
	void drawGui();
	void drawDialogues();
	void applySensitivity();

	void keyControls();
	int fkey;
	int backkey;
	int leftkey;
	int rightkey;
	int runkey;

	gApp* root;

	int gamestate;

	gImage map;
	gImage tank1;
	gImage track[trackframenum];
	gImage gun;
	gImage bulletimage;
	gImage enemy;
	gImage minimap;
	gImage minimapradarsign1, minimapradarsign2;

	gImage gui_charactericon;
	gImage gui_healthicon, gui_bulleticon;
	gImage gui_barframe, gui_barbackground;
	gImage gui_healthbar;

	gImage gui_gameoverdialogue;
	gImage gui_pausedialogue;
	gImage gui_windialogue;
	gImage replaybutton;
	gImage mainmbutton;
	gImage continuebutton;
	gImage nextlevelbutton;


	gFont namefont;

	//tank
	float cx, cy;
	int cw, ch;
	int cwh, chh;
	float cdx, cdy;
	float cspeed;
	int chealth;

	float cangle;
	float cangletr;
	float canglegun;

	int keystate;

	//camera
	float camx, camy;
	float camw, camh;
	float camleftlimit, camrightlimit, camtoplimit, cambottomlimit;

	//maps
	int mapw, maph;
	int minimapx, minimaph;
	int minimapw, minimapy;

	//track
	float tx, ty;
	int tw, th;
	int twh, thh;
	float tdx, tdy;
	int trackframeno;
	int trackframecounter, trackframecounterlimit;

	//gun
	float gx, gy;
	int gw, gh;
	int gwh, ghh;
	float gdx, gdy;

	//bullet
	std::vector<std::vector<float>> bullets;
	float muzzleangle, muzzledistance;
	int bulletamt;

	//font
	int fontx, fonty;
	std::string name;
	int bamtx, bamty;

	//enemy
	int ex, ey;
	int ew, eh;
	int ewh, ehh;

	//gui
	int gcix, gciy;
	int ghix, ghiy, gbix, gbiy;
	int gbiw, gbih;
	int ghbfx, ghbfy, gbbfx, gbbfy;
	int ghbbx, ghbby, gbbbx, gbbby;
	int gbw, gbh;

	int dialoguew, dialogueh;
	int dialoguex, dialoguey;
	bool dialogueshown;
	int score;
	int leftbx, leftby;
	int leftbw, leftbh;
	int rightbx, rightby;
	int rightbw, rightbh;
	int dialoguewidthhalf, dialogueheighthalf;
	int scorex, scorey;
	int scoretitlex, scoretitley;

	float fpscounterx, fpscountery;

	float applysensivity;

	int selectedhull;
	int selectedweapon;
	int selectedtrack;
	int selectedhullcolor;
	int selectedweaponcolor;
};

#endif /* GCANVAS_H_ */
