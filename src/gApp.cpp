/*
 * gApp.cpp
 *
 *  Created on: May 6, 2020
 *      Author: Noyan Culum
 */

#include "gApp.h"
#include "gCanvas.h"
#include "MainMenu.h"
#include "gImage.h"

gApp::gApp() {
}

gApp::gApp(int argc, char **argv) : gBaseApp(argc, argv) {
}

gApp::~gApp() {
}

void gApp::setup() {
	loadAssets();
	mainMenu* cnv = new mainMenu(this);
	appmanager->setCurrentCanvas(cnv);
}

void gApp::update() {
}

void gApp::drawMenuBackground(int w, int h) {
	background->draw(0, 0, w, h);
}

std::string gApp::localizeWord(std::string word) {
	return localization.localizeWord(word);
}

void gApp::loadAssets() {
	menutitlefont.loadFont("StrongStitch-Regular.otf", 18);

	background = new gImage();
	background->loadImage("black.png");

	// OPTIONS DB
	optionsdb.loadDatabase("options.db");
	optionsdb.execute("CREATE TABLE IF NOT EXISTS options (key TEXT PRIMARY KEY, value TEXT)");

	// DEFAULTS
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('invert','0')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('language','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('minimap','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('showfps','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('vsync','1')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('brightness','50')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('resolution','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('windowmode','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('quality','1')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('fov','90')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('forwardkey','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('backwardkey','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('rightkey','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('leftkey','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('runkey','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('firekey','0')");
	//optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('interactkey','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('interactkey','87')"); // W
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('sensitivity','50')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('soundvolume','50')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('musicvolume','50')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('sound','1')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('music','1')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('hull','1')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('weapon','1')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('track','1')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('hullcolor','2')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('weaponcolor','2')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('money','300')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('experience','1')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('name','Player')");

	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('hullowned','10000000')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('weaponowned','10000000')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('trackowned','1000')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('colorowned','1000')");

	// LOCALIZATION DB
	gDatabase locdb;
	locdb.loadDatabase("localization.db");
	locdb.execute("CREATE TABLE IF NOT EXISTS WORDS (Key TEXT PRIMARY KEY, en TEXT, tr TEXT)");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('start','Start','Basla')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('offline','Offline','Cevrimdisi')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('store','Store','Magaza')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('options','Options','Ayarlar')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('help','Help','Yardim')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('credits','Credits','Emegi Gecenler')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('exit','Exit','aaa')");
	locdb.close();

	localization.loadDatabase("localization.db", "WORDS");

	loadGameSettings();
	loadGraphicsSettings();
	loadAudioSettings();
	loadControlsSettings();
	loadMoney();
	loadExperience();
	loadTankSettings();
	loadName();
	loadColors();
	loadOwned();
}

int safeGetInt(std::string data) {
	auto parts = gSplitString(data, "|");
	if(parts.size() > 1) return gToInt(parts[1]);
	return 0;
}

bool gApp::isHullOwned(int index) {
	return hullowned[index] == '1';
}

bool gApp::isWeaponOwned(int index) {
	return weaponowned[index] == '1';
}

bool gApp::isTrackOwned(int index) {
	return trackowned[index] == '1';
}

bool gApp::isColorOwned(int index) {
	return colorowned[index] == '1';
}

void gApp::buyHull(int index) {
	hullowned[index] = '1';

	optionsdb.execute(
		"UPDATE options SET value='" +
		hullowned +
		"' WHERE key='hullowned'"
	);
}

void gApp::buyWeapon(int index) {
	weaponowned[index] = '1';

	optionsdb.execute(
		"UPDATE options SET value='" +
		weaponowned +
		"' WHERE key='weaponowned'"
	);
}

void gApp::buyTrack(int index) {
	trackowned[index] = '1';

	optionsdb.execute(
		"UPDATE options SET value='" +
		trackowned +
		"' WHERE key='trackowned'"
	);
}

void gApp::buyColor(int index) {
	colorowned[index] = '1';

	optionsdb.execute(
		"UPDATE options SET value='" +
		colorowned +
		"' WHERE key='colorowned'"
	);
}

std::string safeGetString(std::string data) {
	auto parts = gSplitString(data, "|");
	if(parts.size() > 1) return parts[1];
	return "Player";
}

void gApp::addMoney(int amount) {
	saveMoney(money + amount);
}

void gApp::addExperience(int amount) {
	saveExperience(experience + amount);
}

void gApp::saveName(std::string name) {
	this->name = name;
	optionsdb.execute("UPDATE options SET value=" + gToStr(name) + " WHERE key='name'");
}

void gApp::saveMoney(int money) {
	this->money = money;
	optionsdb.execute("UPDATE options SET value=" + gToStr(money) + " WHERE key='money'");
}

void gApp::saveExperience(int experience) {
	this->experience = experience;
	optionsdb.execute("UPDATE options SET value=" + gToStr(experience) + " WHERE key='experience'");
}

void gApp::saveGameSettings(int language, int minimap, int showfps, int vsync) {
	this->language = language;
	this->minimap = minimap;
	this->showfps = showfps;
	this->vsync = vsync;

	optionsdb.execute("UPDATE options SET value=" + gToStr(language) + " WHERE key='language'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(minimap) + " WHERE key='minimap'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(showfps) + " WHERE key='showfps'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(vsync) + " WHERE key='vsync'");
}

void gApp::saveControlsSettings(int forward, int backward, int right, int left, int run, int fire, int interact, int sensitivity) {
	this->forward = forward;
	this->backward = backward;
	this->right = right;
	this->left = left;
	this->run = run;
	this->fire = fire;
	this->interact = interact;
	this->sensitivity = sensitivity;

	optionsdb.execute("UPDATE options SET value=" + gToStr(forward) + " WHERE key='forwardkey'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(backward) + " WHERE key='backwardkey'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(right) + " WHERE key='rightkey'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(left) + " WHERE key='leftkey'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(run) + " WHERE key='runkey'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(fire) + " WHERE key='firekey'");
	//optionsdb.execute("UPDATE OPTIONS SET interactkey=" + gToStr(this->interact));
	optionsdb.execute("UPDATE options SET value=" + gToStr(interact) + " WHERE key='interactkey'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(sensitivity) + " WHERE key='sensitivity'");

}

void gApp::saveGraphicsSettings(int resolution, int windowmode) {
	this->resolution = resolution;
	this->windowmode = windowmode;

	//optionsdb.execute("UPDATE options SET value=" + gToStr(brightness) + " WHERE key='brightness'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(resolution) + " WHERE key='resolution'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(windowmode) + " WHERE key='windowmode'");
//	optionsdb.execute("UPDATE options SET value=" + gToStr(quality) + " WHERE key='quality'");
}

void gApp::saveAudioSettings(int soundvolume, int musicvolume, int sound, int music) {
	this->soundvolume = soundvolume;
	this->musicvolume = musicvolume;
	this->sound = sound;
	this->music = music;

	optionsdb.execute("UPDATE options SET value=" + gToStr(soundvolume) + " WHERE key='soundvolume'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(musicvolume) + " WHERE key='musicvolume'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(sound) + " WHERE key='sound'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(music) + " WHERE key='music'");
}

void gApp::saveTankColor(int hullcolor, int weaponcolor) {
	this->hullcolor = hullcolor;
	this->weaponcolor = weaponcolor;

	optionsdb.execute("UPDATE options SET value=" + gToStr(hullcolor) + " WHERE key='hullcolor'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(weaponcolor) + " WHERE key='weaponcolor'");
}

void gApp::saveTankSettings(int hull, int weapon, int track) {
	this->hull = hull;
	this->weapon = weapon;
	this->track = track;

	optionsdb.execute("UPDATE options SET value=" + gToStr(hull) + " WHERE key='hull'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(weapon) + " WHERE key='weapon'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(track) + " WHERE key='track'");
}

void gApp::loadName() {
	optionsdb.execute("SELECT value FROM options WHERE key='name'");
	name = safeGetString(optionsdb.getSelectData());
	//if(money < 1) money = 100;
}

void gApp::loadMoney() {
	optionsdb.execute("SELECT value FROM options WHERE key='money'");
	money = safeGetInt(optionsdb.getSelectData());
	//if(money < 1) money = 100;
}

void gApp::loadExperience() {
	optionsdb.execute("SELECT value FROM options WHERE key='experience'");
	experience = safeGetInt(optionsdb.getSelectData());
	if(experience < 1) experience = 1;
}

void gApp::loadGameSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='language'");
	language = safeGetInt(optionsdb.getSelectData());
	if(language < 0 || language >= localization.getAvailableLanguages().size()) language = 0;
	localization.setCurrentLanguage(language);

	optionsdb.execute("SELECT value FROM options WHERE key='minimap'");
	minimap = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='showfps'");
	showfps = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='vsync'");
	vsync = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadGraphicsSettings() {
	//brightness = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='resolution'");
	resolution = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='windowmode'");
	windowmode = safeGetInt(optionsdb.getSelectData());
	if(windowmode == NULL) windowmode = 1;

//	optionsdb.execute("SELECT value FROM options WHERE key='quality'");
//	quality = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadAudioSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='soundvolume'");
	soundvolume = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='musicvolume'");
	musicvolume = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='sound'");
	sound = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='music'");
	music = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadTankSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='hull'");
	hull = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='weapon'");
	weapon = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='track'");
	track = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadColors() {
	optionsdb.execute("SELECT value FROM options WHERE key='hullcolor'");
	hullcolor = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='weaponcolor'");
	weaponcolor = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadControlsSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='forwardkey'");
	forward = safeGetInt(optionsdb.getSelectData());
	if(forward == 0) forward = 87;

	optionsdb.execute("SELECT value FROM options WHERE key='backwardkey'");
	backward = safeGetInt(optionsdb.getSelectData());
	if(backward == 0) backward = 83;

	optionsdb.execute("SELECT value FROM options WHERE key='rightkey'");
	right = safeGetInt(optionsdb.getSelectData());
	if(right == 0) right = 68;

	optionsdb.execute("SELECT value FROM options WHERE key='leftkey'");
	left = safeGetInt(optionsdb.getSelectData());
	if(left == 0) left = 65;

	optionsdb.execute("SELECT value FROM options WHERE key='runkey'");
	run = safeGetInt(optionsdb.getSelectData());
	if(run == 0) run = 69;

	optionsdb.execute("SELECT value FROM options WHERE key='firekey'");
	fire = safeGetInt(optionsdb.getSelectData());
	if(fire == 0) fire = 70;

	optionsdb.execute("SELECT value FROM options WHERE key='interactkey'");
	interact = safeGetInt(optionsdb.getSelectData());
	if(interact == 0) interact = 90;

	optionsdb.execute("SELECT value FROM options WHERE key='sensitivity'");
	sensitivity = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadOwned() {
	optionsdb.execute("SELECT value FROM options WHERE key='hullowned'");
	hullowned = safeGetString(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='weaponowned'");
	weaponowned = safeGetString(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='trackowned'");
	trackowned = safeGetString(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='colorowned'");
	colorowned = safeGetString(optionsdb.getSelectData());
}

void gApp::applyGameSettings() {
	localization.setCurrentLanguage(language);
}

void gApp::applyGraphicsSettings() {
}

void gApp::applyAudioSettings() {
}

void gApp::applyControlsSettings() {


}

void gApp::resetGameSettings() {
}

void gApp::resetGraphicsSettings() {
}

void gApp::resetAudioSettings() {
}

void gApp::resetControlsSettings() {
}

void gApp::playMenuMusic() {
  /*  if (music == 1 && musicenabled) {
        int result = menumusic.load("assets/sounds/menu.wav");

        if (result != 0) {
            float vol = getMusicVolume() / 20.0f;
            if (vol <= 0.0f) vol = 0.05f;
            menumusic.setVolume(vol);
            menumusic.play();
        }
    }
*/}

void gApp::stopMenuMusic() {
    //menumusic.stop();
}

void gApp::toggleMusic() {
    musicenabled = !musicenabled;
    if (musicenabled) playMenuMusic();
    else stopMenuMusic();
}

void gApp::setMusicEnabled(bool enabled) {
    musicenabled = enabled;
    if (enabled) playMenuMusic();
    else stopMenuMusic();
}

int gApp::getLanguage() {
	return language;
}

int gApp::getMinimap() {
	return minimap;
}

int gApp::getShowFps() {
	return showfps;
}

int gApp::getVsync() {
	return vsync;
}

int gApp::getSensitivity() {
	return sensitivity;
}

int gApp::getInvertMouse() {
	return invertmouse;
}


int gApp::getResolution() {
	return resolution;
}

int gApp::getWindowMode() {
	return windowmode;
}

int gApp::getFov() {
	return fov;
}


int gApp::getSoundVolume() {
	return soundvolume;
}

int gApp::getMusicVolume() {
	return musicvolume;
}

int gApp::getSound() {
	return sound;
}

int gApp::getMusic() {
	return music;
}

int gApp::getForwardKey() {
	return forward;
}

int gApp::getBackwardKey() {
	return backward;
}

int gApp::getRightKey() {
	return right;
}

int gApp::getLeftKey() {
	return left;
}

int gApp::getRunKey() {
	return run;
}

int gApp::getFireKey() {
	return fire;
}

int gApp::getInteractKey() {
	return interact;
}

int gApp::getHull() {
	return hull;
}

int gApp::getWeapon() {
	return weapon;
}

int gApp::getTrack() {
	return track;
}

int gApp::getHullColor() {
	return hullcolor;
}

int gApp::getWeaponColor() {
	return weaponcolor;
}

int gApp::getMoney() {
	return money;
}

int gApp::getExperience() {
	return experience;
}

std::string gApp::getName() {
	return name;
}
