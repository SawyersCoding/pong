#pragma once

#include <cmath>
#include <vector>
#include "pongentity.hpp"
#include "pongsettings.hpp"
#include "scorechangelistener.hpp"
#include "collisionlistener.hpp"

class pong{
	private:
		constexpr static float WIDTH_DEFAULT = 60.0f;
		constexpr static float HEIGHT_DEFAULT = 30.0f;
		constexpr static float SCORE_HEIGHT_DEFAULT = 4.0f;

	public:
		enum gamestate{
			PLAYING,
			GAMEOVER
		};
	
		enum paddle_commands{
			LEFT_NONE,
			LEFT_UP,
			LEFT_DOWN,
			RIGHT_NONE,
			RIGHT_UP,
			RIGHT_DOWN
		};

	private:
		int score_left;
		int score_right;
		float width;
		float height;
		float score_height;
		gamestate state;
		pongentity ball;
		pongentity paddle_left;
		pongentity paddle_right;
		pongsettings settings;
		std::vector<scorechangelistener*> score_change_listeners;
		std::vector<collisionlistener*> collision_listeners;


	public:
		pong(pongsettings settings, float width = WIDTH_DEFAULT, float height = HEIGHT_DEFAULT, float score_height = SCORE_HEIGHT_DEFAULT);

	public:
		void paddle_command(paddle_commands command);
		void update(float dt);
		void reset();
		int get_width();
		int get_height();
		int get_score_height();
		void get_scores(int &score_left, int &score_right);
		gamestate get_state();
		void get_positions(float &ball_x, float &ball_y, float &paddle_left_x, float &paddle_left_y, float &paddle_right_x, float &paddle_right_y);
		void add_scorechangelistener(scorechangelistener *listener);
		void clear_scorechangelisteners();
		void add_collisionlistener(collisionlistener *listener);
		void clear_collisionlisteners();

	private:
		void update_positions(float dt);
		void check_collisions();
		void check_paddle_collision(pongentity &paddle);
		void check_score();
		void notify_scorechangelisteners();
		void notify_collisionlisteners();

};