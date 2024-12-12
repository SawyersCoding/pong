#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "model/pong.hpp"
#include "model/pongsettings.hpp"

#include "view/pongview.hpp"

// Function prototype for process_input
void process_input(GLFWwindow* window, pong& p);

int main(){
	
	// Initialize pong model
	int pscore_left, score_left, pscore_right, score_right;
	float bx, by, lx, ly, rx, ry;
	float current_time;
	float last_frame;
	float delta_time;
	pongsettings settings;
	settings.paddle_width_left = 0.5f;
	settings.paddle_width_right = 0.5f;
	pong p(settings, 60.0f, 30.0f, 4.0f);

	// Initialize pong controller

	// Initialize pong view
	pongview view(p.get_width(), p.get_height(), p.get_score_height(), settings.paddle_width_left, settings.paddle_height_left, settings.paddle_width_right, settings.paddle_height_right, settings.ball_size);

	GLFWwindow *window = view.get_window();

	last_frame = glfwGetTime();
	delta_time = 0.0f;
	// Render loop
	while(!glfwWindowShouldClose(window)){

		// process input
		process_input(window, p);

		// Get delta time
		current_time = glfwGetTime();
		delta_time = current_time - last_frame;
		last_frame = current_time;

		// Update pong model
		p.update(delta_time);
		p.get_positions(bx, by, lx, ly, rx, ry);
		pscore_left = score_left;
		pscore_right = score_right;
		p.get_scores(score_left, score_right);
		if(pscore_left != score_left){
			std::cout << "LEFT SCORES!!" << std::endl;
			std::cout << score_left << "-" << score_right << std::endl;
		}
		if(pscore_right != score_right){
			std::cout << "RIGHT SCORES!!" << std::endl;
			std::cout << score_left << "-" << score_right << std::endl;
		}
		// Render pong view
		view.render_pong(0, 0, bx, by, lx, ly, rx, ry);
		
		glfwPollEvents();
	}

	std::cout << "Goodbye!" << std::endl;

	return 0;
}

void process_input(GLFWwindow *window, pong &p)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}

	// Left controls WASD
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		p.paddle_command(pong::LEFT_UP);
	}
	else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		p.paddle_command(pong::LEFT_DOWN);
	}
	else{
		p.paddle_command(pong::LEFT_NONE);
	}

	// Right controls arrow keys
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		p.paddle_command(pong::RIGHT_UP);
	}
	else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		p.paddle_command(pong::RIGHT_DOWN);
	}
	else{
		p.paddle_command(pong::RIGHT_NONE);
	}
}
