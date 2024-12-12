#include "pongcontroller.hpp"

pongcontroller::pongcontroller()
{
	// Would be nice to load settings from file to avoid recompiles
	settings = new pongsettings();
	pong_model = new pong(*settings);
	pong_model->add_scorechangelistener(this);

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
}

void pongcontroller::play()
{
	// Timing variables
	float current_time;
	float last_frame;
	float delta_time;

	GLFWwindow *window = view->get_window();

	last_frame = glfwGetTime();
	delta_time = 0.0f;
	// Game loop
	while(!glfwWindowShouldClose(window)){
		// std::cout << "RENDERING..." << std::endl;
		// process input
		process_input(window);

		// Get delta time
		current_time = glfwGetTime();
		delta_time = current_time - last_frame;
		last_frame = current_time;

		// Update pong model
		pong_model->update(delta_time);
		pong_model->get_positions(bx, by, lx, ly, rx, ry);

		// Render pong view
		view->render_pong(0, 0, bx, by, lx, ly, rx, ry);
		
		glfwPollEvents();
	}
	
	std::cout << "Goodbye!" << std::endl;
}

void pongcontroller::process_input(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}

	// WASD for left paddle
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		pong_model->paddle_command(pong::LEFT_UP);
	}	
	else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		pong_model->paddle_command(pong::LEFT_DOWN);
	}
	else{
		pong_model->paddle_command(pong::LEFT_NONE);
	}

	// arrow keys for right paddle
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		pong_model->paddle_command(pong::RIGHT_UP);
	}
	else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		pong_model->paddle_command(pong::RIGHT_DOWN);
	}
	else{
		pong_model->paddle_command(pong::RIGHT_NONE);
	}
}

void pongcontroller::on_score_changed()
{
	pong_model->get_scores(score_left, score_right);

	std::cout << "Score: " << score_left << "-" << score_right << std::endl;
}