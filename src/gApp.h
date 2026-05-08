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

	std::string titlekey = "WarTrack: Arena", languagekey = "language", sensivitykey = "sensivity", invertmousekey = "invertmouse",
			showfpskey = "showfps", resolutionkey = "resolution", windowmodekey = "windowmode", fovkey = "fov",
			vsynckey = "vsync", soundvolumekey = "soundvolume", musicvolumekey = "musicvolume", soundkey = "sound", musickey = "music",
			forwardkey = "forward", backwardkey = "backward", rightkey = "right", leftkey = "left", runkey = "run", firekey = "fire", interactkey = "interact",
			offlinekey = "offline", startkey = "start", shopkey = "store", optionskey = "options", creditskey = "credits", exitkey = "exit", tankkey = "tank",
			fullscreenkey = "fullscreen", windowedkey = "windowed", lowkey = "low", normalkey = "normal", highkey = "high", returnkey = "return",
			generalkey = "general", videokey = "video", audiokey = "audio", controlskey = "controls", skillskey = "skills", applykey = "apply", resetkey = "reset", helpkey = "help",
			generallabelkey = "Summary: Tanks can move forward and backward, and rotate using the left and right controls, while the turret is aimed independently with the mouse. The game features two modes: Score Mode and Flag Mode. In Score Mode, teams compete to earn the highest score within a limited time, and the team with the most points at the end wins; however, if a team reaches 40 points, they win instantly. In Flag Mode, teams compete to capture flags within a limited time, and the team that collects all flags wins immediately; if time runs out, the team with the most flags wins. You can also practice in offline mode, and use in-game abilities to gain an advantage during matches.";

	void drawMenuBackground(int w, int h);
	std::string localizeWord(std::string word);

	void saveGameSettings(int language, int minimap, int vsync, int showfps);
	void saveControlsSettings(int forward, int backward, int right, int left, int run, int fire, int interact, int sensitivity);
	void saveGraphicsSettings(int resolution, int windowmode);
	void saveAudioSettings(int soundvolume, int musicvolume, int sound, int music);
	void saveTankSettings(int hull, int weapon, int track);
	void saveTankColor(int hullcolor, int weaponcolor);
	void saveMoney(int money);
	void saveExperience(int experience);
	void saveName(std::string name);

	void loadGameSettings();
	void loadControlsSettings();
	void loadGraphicsSettings();
	void loadAudioSettings();
	void loadTankSettings();
	void loadMoney();
	void loadExperience();
	void loadName();
	void loadColors();

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
	int getSensitivity();
	int getWindowMode();
	int getInvertMouse();
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
	int getHull();
	int getWeapon();
	int getTrack();
	int getHullColor();
	int getWeaponColor();
	int getMoney();
	int getExperience();
	std::string getName();

	void addMoney(int amount);
	void addExperience(int experience);

private:
	void loadAssets();

	bool musicenabled = true;

	gImage* background;
	gDatabase optionsdb;
	int language, sensitivity, invertmouse, minimap, showfps, vsync, resolution,
	 windowmode, fov, soundvolume, musicvolume, sound, music, forward, backward, right,
	 left, run, fire, interact, hull, weapon, track, hullcolor, weaponcolor, money, experience;
	std::string temp;
	std::string name;
	gLocalization localization;
};

#endif /* GAPP_H_ */
