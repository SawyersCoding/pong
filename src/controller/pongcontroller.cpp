
#include <thread>
#include "pongcontroller.hpp"
#include "paddlecontroller.hpp"
#include "playerpaddlecontroller.hpp"
#include "basicpaddlecontroller.hpp"

pongcontroller::pongcontroller()
{
	// Would be nice to load settings from file to avoid recompiles
	settings = new pongsettings();
	pong_model = new pong(*settings);
	pong_model->add_scorechangelistener(this);
	pong_model->add_collisionlistener(this);
	audio = new audioplayer();

	view = new pongview(pong_model->get_width(), 
						pong_model->get_height(), 
						pong_model->get_score_height(), 
						settings->paddle_width_left, 
						settings->paddle_height_left, 
						settings->paddle_width_right, 
						settings->paddle_height_right, 
						settings->ball_size);
}

pongcontroller::~pongcontroller()
{
	pong_model->clear_scorechangelisteners();
	delete settings;
	delete pong_model;
	delete view;
	delete audio;
}

void pongcontroller::play()
{
	int nplayers = 1;
	paddlecontroller *lp_controller, *rp_controller;

	GLFWwindow *window = view->get_window();

	while(glfwGetKey(window, GLFW_KEY_ENTER) != GLFW_PRESS && !glfwWindowShouldClose(window)){		
		if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS){
			nplayers = 1;
		}
		else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS){
			nplayers = 2;
		}

		pong_model->get_positions(bx, by, lx, ly, rx, ry);
		// Render pong view
		view->render_pong(nplayers, nplayers, bx, by, lx, ly, rx, ry);

		glfwPollEvents();
		check_exit(window);
	}

	lp_controller = new playerpaddlecontroller(GLFW_KEY_W, GLFW_KEY_S, window, pong_model, pong::LEFT_UP, pong::LEFT_DOWN, pong::LEFT_NONE);
	if(nplayers == 1){
		rp_controller = new basicpaddlecontroller(pong_model, &by, &ry, pong::RIGHT_UP, pong::RIGHT_DOWN, pong::RIGHT_NONE);
	}
	else {
		rp_controller = new playerpaddlecontroller(GLFW_KEY_UP, GLFW_KEY_DOWN, window, pong_model, pong::RIGHT_UP, pong::RIGHT_DOWN, pong::RIGHT_NONE);
	}

	// rp_controller = new playerpaddlecontroller(GLFW_KEY_UP, GLFW_KEY_DOWN, window, pong_model, pong::RIGHT_UP, pong::RIGHT_DOWN, pong::RIGHT_NONE);

	while(!glfwWindowShouldClose(window)){
		// Timing variables
		bool left_win = false;
		int countdown = 3;
		float current_time;
		float last_frame;
		float delta_time;

		// Countdown to start of game
		pong_model->update(0.0f);
		pong_model->get_positions(bx, by, lx, ly, rx, ry);
		for(int i = countdown; i > 0 && !glfwWindowShouldClose(window); i--){
			view->render_pong(i, i, bx, by, lx, ly, rx, ry);
			glfwPollEvents();

			// Wait for 1 second
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			audio->play_sfx(i > 1 ? audioplayer::COUNT : audioplayer::GO);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		last_frame = glfwGetTime();
		delta_time = 0.0f;
		pong_model->get_scores(score_left, score_right);
		// Game loop
		while(!glfwWindowShouldClose(window) && pong_model->get_state() != pong::GAMEOVER){
			// process input
			lp_controller->process_input();
			rp_controller->process_input();
			check_exit(window);

			// Get delta time
			current_time = glfwGetTime();
			delta_time = current_time - last_frame;
			last_frame = current_time;

			// Update pong model
			pong_model->update(delta_time);

			if(pong_model->get_state() != pong::GAMEOVER){
				pong_model->get_positions(bx, by, lx, ly, rx, ry);
				// Render pong view
				view->render_pong(score_left, score_right, bx, by, lx, ly, rx, ry);
			}
			
			glfwPollEvents();
		}

		left_win = score_left > score_right;

		if(left_win) score_right = score_left + 1;
		else score_left = score_right + 1;

		// Blink the winner's score
		for(int i = 0; i < 3 && !glfwWindowShouldClose(window); i++){
			if(i == 0){
				audio->play_sfx(audioplayer::GAMEOVER);
			}
			view->render_pong(left_win ? -1 : score_left, !left_win ? -1 : score_right, bx, by, lx, ly, rx, ry);
			std::this_thread::sleep_for(std::chrono::seconds(1));
			glfwPollEvents();

			view->render_pong(score_left, score_right, bx, by, lx, ly, rx, ry);
			std::this_thread::sleep_for(std::chrono::seconds(1));
			glfwPollEvents();
		}

		if(!glfwWindowShouldClose(window)){
			std::this_thread::sleep_for(std::chrono::seconds(1));
			glfwPollEvents();
			pong_model->reset();
		}
	}

	std::cout << "Goodbye!" << std::endl;
}

void pongcontroller::check_exit(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
}

void pongcontroller::on_score_changed()
{
	pong_model->get_scores(score_left, score_right);
	audio->play_sfx(audioplayer::POINT);
}

void pongcontroller::on_collision()
{
	audio->play_sfx(audioplayer::PING);
}
