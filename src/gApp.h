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

	void saveGameSettings(int language, int minimap, int vsync, int showfps);
	void saveControlsSettings(int forward, int backward, int right, int left, int run, int fire, int interact);
	void saveGraphicsSettings(int brightness, int resolution, int windowmode, int quality);
	void saveAudioSettings(int soundvolume, int musicvolume, int sound, int music);

	void loadGameSettings();
	void loadControlsSettings();
	void loadGraphicsSettings();
	void loadAudioSettings();

	void applyGameSettings();
	void applyControlsSettings();
	void applyGraphicsSettings();
	void applyAudioSettings();

	void resetGameSettings();
	void resetControlsSettings();
	void resetGraphicsSettings();
	void resetAudioSettings();

	void playMenuMusic();
	void stopMenuMusic();
	void toggleMusic();
	void setMusicEnabled(bool enabled);
	bool getMusicEnabled() const { return musicenabled; }

	int getLanguage();
	int getMinimap();
	int getShowFps();
	int getVsync();
	int getResolution();
	int getSensivity();
	int getBrightness();
	int getWindowMode();
	int getInvertMouse();
	int getQuality();
	int getFov();
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
	gDatabase optionsdb;
	int language, sensivity, brightness, invertmouse, minimap, showfps, vsync, resolution, windowmode, quality, fov, soundvolume,
	musicvolume, sound, music, forward, backward, right, left, run, fire, interact;
	std::string temp;
	gLocalization localization;
};

#endif /* GAPP_H_ */
