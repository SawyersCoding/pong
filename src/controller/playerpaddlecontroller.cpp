#include "playerpaddlecontroller.hpp"

playerpaddlecontroller::playerpaddlecontroller(int glfw_key_up, int glfw_key_down, GLFWwindow *window, pong *pong_model, pong::paddle_commands up_command, pong::paddle_commands down_command, pong::paddle_commands none_command) : paddlecontroller(up_command, down_command, none_command), glfw_key_up(glfw_key_up), glfw_key_down(glfw_key_down), window(window), pong_model(pong_model)
{
	
}

void playerpaddlecontroller::process_input()
{
	if(glfwGetKey(window, glfw_key_up) == GLFW_PRESS){
		pong_model->paddle_command(up_command);
	}	
	else if(glfwGetKey(window, glfw_key_down) == GLFW_PRESS){
		pong_model->paddle_command(down_command);
	}
	else{
		pong_model->paddle_command(none_command);
	}
}
