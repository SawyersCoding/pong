#pragma once

#include <SFML/Audio.hpp>

class audioplayer{

	public:
		enum SFX{
			COUNT = 0,
			GO = 1,
			PING = 2,
			POINT = 3,
			GAMEOVER = 4
		};

	private:
		const static int NSOUNDS = 5;
		sf::SoundBuffer buffers[NSOUNDS];
		sf::Sound sounds[NSOUNDS];

	public:
		audioplayer();
		~audioplayer();
		
	public:	
		void play_sfx(SFX sfx);

};