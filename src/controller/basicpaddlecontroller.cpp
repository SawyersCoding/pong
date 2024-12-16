#include "basicpaddlecontroller.hpp"

basicpaddlecontroller::basicpaddlecontroller(pong *pong_model, float *by, float *py, pong::paddle_commands up_command, pong::paddle_commands down_command, pong::paddle_commands none_command) : paddlecontroller(up_command, down_command, none_command), by(by), py(py), pong_model(pong_model)
{
	
}

void basicpaddlecontroller::process_input()
{
	if(fabs(*by - *py) < distance_tol){
		pong_model->paddle_command(none_command);
	}
	else if(*by < *py){
		pong_model->paddle_command(down_command);
	}
	else{
		pong_model->paddle_command(up_command);
	}
}
