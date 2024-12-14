#pragma once

#include "paddlecontroller.hpp"
#include "../model/pong.hpp"

class basicpaddlecontroller : public paddlecontroller {

	private:
		constexpr static float distance_tol = 0.05f;

		int glfw_key_up;
		int glfw_key_down;
		float *by;
		float *py;
		pong *pong_model;

	public:
		basicpaddlecontroller(pong *pong_model, float *by, float *py, pong::paddle_commands up_command, pong::paddle_commands down_command, pong::paddle_commands none_command);

	public:
		void process_input() override;
};