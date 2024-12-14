#pragma once

#include "../model/pong.hpp"

class paddlecontroller {

	protected:
		pong::paddle_commands up_command;
		pong::paddle_commands down_command;
		pong::paddle_commands none_command;

	public:
		paddlecontroller(pong::paddle_commands up_command, pong::paddle_commands down_command, pong::paddle_commands none_command) : up_command(up_command), down_command(down_command), none_command(none_command) {}
		
	public:
		virtual void process_input() = 0;

};
