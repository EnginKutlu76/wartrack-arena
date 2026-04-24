/*
 * gApp.h
 *
 *  Created on: May 6, 2020
 *      Author: Noyan Culum
 */

#ifndef GAPP_H_
#define GAPP_H_

#include "gBaseApp.h"
#include "gLocalization.h"
#include "gSound.h"
#include "gDatabase.h"

class gApp : public gBaseApp {
public:
	gApp();
	gApp(int argc, char **argv);
	~gApp();

	void setup();
	void update();

	//gSound intromusic;
	///gSound menumusic;
	//gSound getmusic;

	gFont menutitlefont;

	static const int GAME_NONE = 0, GAME_PLAY = 1, GAME_PAUSE = 2, GAME_LOAD = 3, GAME_OPTION = 4;
	static const int MAINMENU_BACKGROUND = 0, ESC_BACKGROUND = 1;
	int gamestate;
	int currentbackground;

	std::string titlekey = "WarTrack: Arena", languagekey = "language", sensivitykey = "sensivity", brightnesskey = "brightness", invertmousekey = "invertmouse",
			showfpskey = "showfps", resolutionkey = "resolution", windowmodekey = "windowmode", qualitykey = "quality", fovkey = "fov",
			vsynckey = "vsync", soundvolumekey = "soundvolume", musicvolumekey = "musicvolume", soundkey = "sound", musickey = "music",
			forwardkey = "forward", backwardkey = "backward", rightkey = "right", leftkey = "left", runkey = "run", firekey = "fire", interactkey = "interact",
			offlinekey = "offline", startkey = "start", shopkey = "store", optionskey = "options", creditskey = "credits", exitkey = "exit", tankkey = "tank",
			fullscreenkey = "fullscreen", windowedkey = "windowed", lowkey = "low", normalkey = "normal", highkey = "high", returnkey = "return",
			generalkey = "general", videokey = "video", audiokey = "audio", controlskey = "controls", applykey = "apply", resetkey = "reset", helpkey = "help",
			generallabelkey = "Here, general information is provided. You can view the sections using the Bolumler button, check the items in the Esyalar section, and see the controls by clicking the Kontroller button. Congratulations";

	void drawMenuBackground(int w, int h);
	std::string localizeWord(std::string word);

	void saveGeneralSettings(int language, int sensivity, int brightness, int invertmouse, int showfps);
	void saveVideoSettings(int resolution, int windowmode, int quality, int fov, int vsync);
	void saveAudioSettings(int soundvolume, int musicvolume, int sound, int music);
	void saveControlsSettings(int forward, int backward, int right, int left, int run, int fire, int interact);

	void loadGeneralSettings();
	void loadVideoSettings();
	void loadAudioSettings();
	void loadControlsSettings();

	void applyGeneralSettings();
	void applyVideoSettings();
	void applyAudioSettings();
	void applyControlsSettings();

	void resetGeneralSettings();
	void resetVideoSettings();
	void resetAudioSettings();
	void resetControlsSettings();

	void playMenuMusic();
	void stopMenuMusic();
	void toggleMusic();
	void setMusicEnabled(bool enabled);
	bool getMusicEnabled() const { return musicenabled; }

	int getLanguage();
	int getSensivity();
	int getBrightness();
	int getInvertMouse();
	int getShowFps();
	int getResolution();
	int getWindowMode();
	int getQuality();
	int getFov();
	int getVsync();
	int getSoundVolume();
	int getMusicVolume();
	int getSound();
	int getMusic();
	int getForwardKey();
	int getBackwardKey();
	int getRightKey();
	int getLeftKey();
	int getRunKey();
	int getFireKey();
	int getInteractKey();


private:
	void loadAssets();

	bool musicenabled = true;

	gImage* background;
//	gDatabase optionsdb;
	int language, sensivity, brightness, invertmouse, showfps, resolution, windowmode, quality, fov, vsync, soundvolume,
	musicvolume, sound, music, forward, backward, right, left, run, fire, interact;
	std::string temp;
	gLocalization localization;
};

#endif /* GAPP_H_ */
