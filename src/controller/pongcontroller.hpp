#pragma once

#include <iostream>
#include "../model/pong.hpp"
#include "../model/pongsettings.hpp"
#include "../model/scorechangelistener.hpp"
#include "../view/pongview.hpp"
#include "../view/audio/audioplayer.hpp"

class pongcontroller : public scorechangelistener, public collisionlistener{

	private:
		// pong state variables
		int score_left;
		int score_right;
		float bx, by, lx, ly, rx, ry;
		pong *pong_model;
		pongsettings *settings;
		pongview *view;
		audioplayer *audio;

	public:
		pongcontroller();
		~pongcontroller();

	public:
		void play();
		void process_input(GLFWwindow *window);
		void on_score_changed() override;
		void on_collision() override;

};