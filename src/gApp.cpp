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
	std::string str = localization.localizeWord(word);
	str = str.substr(0, str.size());
	return str;
}

void gApp::loadAssets() {
	menutitlefont.loadFont("StrongStitch-Regular.otf", 18);
	background = new gImage();
	background->loadImage("black.png");

/*	intromusic.loadSound("intro.wav");
	optionsdb.loadDatabase("options.db");
	localization.loadDatabase("localization.db", "WORDS");
*/
	loadGeneralSettings();
	loadVideoSettings();
	loadAudioSettings();
	loadControlsSettings();
}

void gApp::saveGeneralSettings(int language, int sensivity, int brightness, int invertmouse, int showfps) {
	this->language = language;
	this->sensivity = sensivity;
	this->brightness = brightness;
	this->invertmouse = invertmouse;
	this->showfps = showfps;
/*	optionsdb.execute("UPDATE OPTIONS SET language=" + gToStr(this->language));
	optionsdb.execute("UPDATE OPTIONS SET sensivity=" + gToStr(this->sensivity));
	optionsdb.execute("UPDATE OPTIONS SET brightness=" + gToStr(this->brightness));
	optionsdb.execute("UPDATE OPTIONS SET invert=" + gToStr(this->invertmouse));
	optionsdb.execute("UPDATE OPTIONS SET showfps=" + gToStr(this->showfps));
*/}

void gApp::saveVideoSettings(int resolution, int windowmode, int quality, int fov, int vsync) {
	this->resolution = resolution;
	this->windowmode = windowmode;
	this->quality = quality;
	this->fov = fov;
	this->vsync = vsync;
/*	optionsdb.execute("UPDATE OPTIONS SET resolution=" + gToStr(this->resolution));
	optionsdb.execute("UPDATE OPTIONS SET windowmode=" + gToStr(this->windowmode));
	optionsdb.execute("UPDATE OPTIONS SET quality=" + gToStr(this->quality));
	optionsdb.execute("UPDATE OPTIONS SET fov=" + gToStr(this->fov));
	optionsdb.execute("UPDATE OPTIONS SET vsync=" + gToStr(this->vsync));
*/
}

void gApp::saveAudioSettings(int soundvolume, int musicvolume, int sound, int music) {
	this->soundvolume = soundvolume;
	this->musicvolume = musicvolume;
	this->sound = sound;
	this->music = music;
//	optionsdb.execute("UPDATE OPTIONS SET soundvolume=" + gToStr(this->soundvolume));
//	optionsdb.execute("UPDATE OPTIONS SET musicvolume=" + gToStr(this->musicvolume));
//	optionsdb.execute("UPDATE OPTIONS SET sound=" + gToStr(this->sound));
//	optionsdb.execute("UPDATE OPTIONS SET music=" + gToStr(this->music));
}

void gApp::saveControlsSettings(int forward, int backward, int right, int left, int run, int fire, int interact) {
	this->forward = forward;
	this->backward = backward;
	this->right = right;
	this->left = left;
	this->run = run;
	this->fire = fire;
	this->interact = interact;
//	optionsdb.execute("UPDATE OPTIONS SET forwardkey=" + gToStr(this->forward));
//	optionsdb.execute("UPDATE OPTIONS SET backwardkey=" + gToStr(this->backward));
//	optionsdb.execute("UPDATE OPTIONS SET rightkey=" + gToStr(this->right));
//	optionsdb.execute("UPDATE OPTIONS SET leftkey=" + gToStr(this->left));
//	optionsdb.execute("UPDATE OPTIONS SET runkey=" + gToStr(this->run));
//	optionsdb.execute("UPDATE OPTIONS SET firekey=" + gToStr(this->fire));
//	optionsdb.execute("UPDATE OPTIONS SET interactkey=" + gToStr(this->interact));
}

void gApp::loadGeneralSettings() {
/*	optionsdb.execute("SELECT language FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	language = gToInt(temp);
//	localization.setCurrentLanguage(language);

//	optionsdb.execute("SELECT sensivity FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size()- 1);
	sensivity = gToInt(temp);

//	optionsdb.execute("SELECT brightness FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	brightness = gToInt(temp);

	optionsdb.execute("SELECT invert FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	invertmouse = gToInt(temp);

	optionsdb.execute("SELECT showfps FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	showfps = gToInt(temp);
*/}

void gApp::loadVideoSettings() {
	/*optionsdb.execute("SELECT resolution FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	resolution = gToInt(temp);

	optionsdb.execute("SELECT windowmode FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	windowmode = gToInt(temp);

	optionsdb.execute("SELECT quality FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	quality = gToInt(temp);

	optionsdb.execute("SELECT fov FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	fov = gToInt(temp);

	optionsdb.execute("SELECT vsync FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	vsync = gToInt(temp);
*/}

void gApp::loadAudioSettings() {
/*	optionsdb.execute("SELECT soundvolume FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	soundvolume = gToInt(temp);

	optionsdb.execute("SELECT musicvolume FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	musicvolume = gToInt(temp);

	optionsdb.execute("SELECT sound FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	sound = gToInt(temp);

	optionsdb.execute("SELECT music FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	music = gToInt(temp);
*/}

void gApp::loadControlsSettings() {
/*	optionsdb.execute("SELECT forwardkey FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	forward = gToInt(temp);

	optionsdb.execute("SELECT backwardkey FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	backward = gToInt(temp);

	optionsdb.execute("SELECT rightkey FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	right = gToInt(temp);

	optionsdb.execute("SELECT leftkey FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	left = gToInt(temp);

	optionsdb.execute("SELECT runkey FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	run = gToInt(temp);

	optionsdb.execute("SELECT firekey FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	fire = gToInt(temp);

	optionsdb.execute("SELECT interactkey FROM OPTIONS");
	temp = optionsdb.getSelectData();
	temp = temp.substr(2, temp.size() - 1);
	interact = gToInt(temp);
*/
}

void gApp::applyGeneralSettings() {
//	localization.setCurrentLanguage(language);
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
