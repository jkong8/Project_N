#pragma once
#include <SFML/Audio.hpp>
//Singleton Pattern for Audio
class Audio_Manager
{
public:
	//Get Instance
	static Audio_Manager& getInstance();
	
	//Music
	sf::Music battle_music_;
	sf::Music main_music_;

	//Sounds
	sf::Sound ui_confirmation_;
	sf::Sound basic_damage_;

	//Sound Buffers
	sf::SoundBuffer ui_confirmationSB_;
	sf::SoundBuffer basic_damageSB_;

private:
	//Constructor
	Audio_Manager();

	//helper functions
	void loadSound(sf::Sound&, sf::SoundBuffer&, std::string filepath);
};

