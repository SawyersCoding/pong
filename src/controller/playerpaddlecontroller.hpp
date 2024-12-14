#pragma once

#include <GLFW/glfw3.h>
#include "paddlecontroller.hpp"
#include "../model/pong.hpp"

class playerpaddlecontroller : public paddlecontroller {

	private:
		int glfw_key_up;
		int glfw_key_down;
		GLFWwindow *window;
		pong *pong_model;

	public:
		playerpaddlecontroller(int glfw_key_up, int glfw_key_down, GLFWwindow *window, pong *pong_model, pong::paddle_commands up_command, pong::paddle_commands down_command, pong::paddle_commands none_command);

	public:
		void process_input() override;
};