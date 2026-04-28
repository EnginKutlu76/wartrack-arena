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
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('language','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('sensivity','50')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('brightness','50')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('invert','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('showfps','0')");
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('vsync','1')");
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
	optionsdb.execute("INSERT OR IGNORE INTO options (key,value) VALUES ('interactkey','0')");

	// LOCALIZATION DB
	gDatabase locdb;
	locdb.loadDatabase("localization.db");
	locdb.execute("CREATE TABLE IF NOT EXISTS WORDS (Key TEXT PRIMARY KEY, en TEXT, tr TEXT)");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('play','Play','Oyna')");
	locdb.execute("INSERT OR IGNORE INTO WORDS VALUES ('exit','Exit','Çýkýþ')");
	locdb.close();

	localization.loadDatabase("localization.db", "WORDS");

	loadGeneralSettings();
	loadVideoSettings();
	loadAudioSettings();
	loadControlsSettings();
}

int safeGetInt(std::string data) {
	auto parts = gSplitString(data, "|");
	if(parts.size() > 1) return gToInt(parts[1]);
	return 0;
}

void gApp::saveGeneralSettings(int language, int sensivity, int brightness, int invertmouse, int showfps) {
	this->language = language;
	this->sensivity = sensivity;
	this->brightness = brightness;
	this->invertmouse = invertmouse;
	this->showfps = showfps;

	optionsdb.execute("UPDATE options SET value=" + gToStr(language) + " WHERE key='language'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(sensivity) + " WHERE key='sensivity'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(brightness) + " WHERE key='brightness'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(invertmouse) + " WHERE key='invert'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(showfps) + " WHERE key='showfps'");
}

void gApp::saveVideoSettings(int resolution, int windowmode, int quality, int fov, int vsync) {
	this->resolution = resolution;
	this->windowmode = windowmode;
	this->quality = quality;
	this->fov = fov;
	this->vsync = vsync;

	optionsdb.execute("UPDATE options SET value=" + gToStr(resolution) + " WHERE key='resolution'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(windowmode) + " WHERE key='windowmode'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(quality) + " WHERE key='quality'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(fov) + " WHERE key='fov'");
	optionsdb.execute("UPDATE options SET value=" + gToStr(vsync) + " WHERE key='vsync'");
}

void gApp::loadGeneralSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='language'");
	language = safeGetInt(optionsdb.getSelectData());
	if(language < 0 || language >= localization.getAvailableLanguages().size()) language = 0;
	localization.setCurrentLanguage(language);

	optionsdb.execute("SELECT value FROM options WHERE key='sensivity'");
	sensivity = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='brightness'");
	brightness = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='invert'");
	invertmouse = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='showfps'");
	showfps = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadVideoSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='resolution'");
	resolution = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='windowmode'");
	windowmode = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='quality'");
	quality = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='fov'");
	fov = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='vsync'");
	vsync = safeGetInt(optionsdb.getSelectData());
}

void gApp::loadAudioSettings() {
}

void gApp::loadControlsSettings() {
	optionsdb.execute("SELECT value FROM options WHERE key='forwardkey'");
	forward = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='backwardkey'");
	backward = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='rightkey'");
	right = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='leftkey'");
	left = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='runkey'");
	run = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='firekey'");
	fire = safeGetInt(optionsdb.getSelectData());

	optionsdb.execute("SELECT value FROM options WHERE key='interactkey'");
	interact = safeGetInt(optionsdb.getSelectData());
}

void gApp::applyGeneralSettings() {
	localization.setCurrentLanguage(language);
}

void gApp::applyVideoSettings() {
}

void gApp::applyAudioSettings() {
}

void gApp::applyControlsSettings() {


}

void gApp::resetGeneralSettings() {
}

void gApp::resetVideoSettings() {
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

int gApp::getSensivity() {
	return sensivity;
}

int gApp::getBrightness() {
	return brightness;
}

int gApp::getInvertMouse() {
	return invertmouse;
}

int gApp::getShowFps() {
	return showfps;
}

int gApp::getResolution() {
	return resolution;
}

int gApp::getWindowMode() {
	return windowmode;
}

int gApp::getQuality() {
	return quality;
}

int gApp::getFov() {
	return fov;
}

int gApp::getVsync() {
	return vsync;
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
