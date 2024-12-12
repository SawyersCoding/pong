#pragma once

#include <iostream>
#include "../model/pong.hpp"
#include "../model/pongsettings.hpp"
#include "../model/scorechangelistener.hpp"
#include "../view/pongview.hpp"

class pongcontroller : public scorechangelistener {

	private:
		// pong state variables
		int score_left;
		int score_right;
		float bx, by, lx, ly, rx, ry;
		pong *pong_model;
		pongsettings *settings;
		pongview *view;

	public:
		pongcontroller();
		~pongcontroller();

	public:
		void play();
		void process_input(GLFWwindow *window);
		void on_score_changed() override;

};