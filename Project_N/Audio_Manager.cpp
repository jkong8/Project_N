#include "Audio_Manager.h"
//Singleton
Audio_Manager& Audio_Manager::getInstance()
{
	static Audio_Manager *instance = new Audio_Manager();
	return *instance;
}

//Constructor
Audio_Manager::Audio_Manager()
{
	//Loads all music/sound files
	battle_music_.openFromFile("./Sounds/birth_of_a_wish.wav");
	main_music_.openFromFile("./Sounds/city_of_ruin2.wav");

	loadSound(ui_confirmation_, ui_confirmationSB_, "./Sounds/ui_confirmation.wav");
	loadSound(basic_damage_, basic_damageSB_, "./Sounds/basic_damage.wav");
}

//Method to load sound easier
void Audio_Manager::loadSound(sf::Sound& sound, sf::SoundBuffer& buffer, std::string filepath)
{
	if (buffer.loadFromFile(filepath))
	{
		sound.setBuffer(buffer);
	}
}