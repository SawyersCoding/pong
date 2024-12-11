#pragma once

#include <cmath>
#include <vector>
#include "pongentity.hpp"
#include "pongsettings.hpp"
#include "scorechangelistener.hpp"

class pong{

	enum gamestate{
		PLAYING,
		GAMEOVER
	};

	enum paddle_commands{
		NONE_LEFT,
		UP_LEFT,
		DOWN_LEFT,
		NONE_RIGHT,
		UP_RIGHT,
		DOWN_RIGHT
	};

	private:
		int score_left;
		int score_right;
		float width;
		float height;
		float scoreboard_height;
		gamestate state;
		pongentity ball;
		pongentity paddle_left;
		pongentity paddle_right;
		pongsettings settings;
		std::vector<scorechangelistener*> listeners;

	public:
		pong(pongsettings settings, float width = 20.0f, float height = 12.0f, float scoreboard_height = 2.0f);

	public:
		void paddle_command(paddle_commands command);
		void update(float dt);
		int get_score_left();
		int get_score_right();
		gamestate get_state();
		void get_positions(float &ball_x, float &ball_y, float &paddle_left_x, float &paddle_left_y, float &paddle_right_x, float &paddle_right_y);
		void add_scorechangelistener(scorechangelistener *listener);
		void clear_scorechangelisteners();

	private:
		void update_positions(float dt);
		void check_collisions();
		void check_paddle_collision(pongentity &paddle);
		void check_score();
		void notify_scorechangelisteners();

};