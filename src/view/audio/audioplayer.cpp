#include "audioplayer.hpp"
#include <iostream>

audioplayer::audioplayer()
{
	// Load sound buffers
	buffers[COUNT].loadFromFile("resources/audio/count.wav");
	buffers[GO].loadFromFile("resources/audio/go.wav");
	buffers[PING].loadFromFile("resources/audio/ping.wav");
	buffers[POINT].loadFromFile("resources/audio/point.wav");

	for(int i = 0; i < NSOUNDS; i++){
		sounds[i].setBuffer(buffers[i]);
		sounds[i].setVolume(50.0f);
	}
}

audioplayer::~audioplayer()
{

}

void audioplayer::play_sfx(SFX sfx)
{
	if(sfx == PING){
		// Randomize pitch for variety
		sounds[PING].setPitch(0.8f + 0.4f * ((float)rand() / (float)RAND_MAX));
	}
	sounds[sfx].play();
}
