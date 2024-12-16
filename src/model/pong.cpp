#include "pong.hpp"

pong::pong(pongsettings settings, float width, float height, float score_height) : width(width), height(height), score_height(score_height)
{
	// Initialize scores
	this->settings = settings;
	score_left = 0;
	score_right = 0;

	// Create ball
	float ballx = width / 2.0f;
	float bally = height / 2.0f;
	float ballzrot_deg = 0.0f;
	float ballwidth = 1.0f;
	float ballheight = 1.0f;
	float ballxvelocity = -settings.ball_start_speed;
	float ballyvelocity = 0.0f;
	ball = pongentity("ball", transform2D(ballx, bally, ballzrot_deg, ballwidth, ballheight, ballxvelocity, ballyvelocity));
	

	// Create left paddle
	float paddleleftx = settings.paddle_width_left;
	float paddlelefty = height / 2.0f;
	float paddleleftzrot_deg = 0.0f;
	float paddleleftwidth = settings.paddle_width_left;
	float paddleleftheight = settings.paddle_height_left;
	float paddleleftxvelocity = 0.0f;
	float paddleleftyvelocity = 0.0f;
	paddle_left = pongentity("paddle_left", transform2D(paddleleftx, paddlelefty, paddleleftzrot_deg, paddleleftwidth, paddleleftheight, paddleleftxvelocity, paddleleftyvelocity));

	// Create right paddle
	float paddlerightx = width - settings.paddle_width_right;
	float paddlerighty = height / 2.0f;
	float paddlerightzrot_deg = 0.0f;
	float paddlerightwidth = settings.paddle_width_right;
	float paddlerightheight = settings.paddle_height_right;
	float paddlerightxvelocity = 0.0f;
	float paddlerightyvelocity = 0.0f;
	paddle_right = pongentity("paddle_right", transform2D(paddlerightx, paddlerighty, paddlerightzrot_deg, paddlerightwidth, paddlerightheight, paddlerightxvelocity, paddlerightyvelocity));
}

void pong::update(float dt)
{
	if(get_state() == GAMEOVER) return;

	check_score();
	check_collisions();
	update_positions(dt);
	// Check for game over
	if(score_left >= settings.winning_score || score_right >= settings.winning_score){
		state = GAMEOVER;
	}
}

void pong::reset()
{
	paddle_left.transform.y = height / 2.0f;
	paddle_right.transform.y = height / 2.0f;

	score_left = 0;
	score_right = 0;
	ball.transform.x = width / 2.0f;
	ball.transform.y = height / 2.0f;
	ball.transform.xvelocity = -settings.ball_start_speed;
	ball.transform.yvelocity = 0.0f;
	state = PLAYING;
}

int pong::get_width()
{
	return width;
}

int pong::get_height()
{
	return height;
}

int pong::get_score_height()
{
	return score_height;
}

void pong::get_scores(int &score_left, int &score_right)
{
	score_left = this->score_left;
	score_right = this->score_right;
}

pong::gamestate pong::get_state()
{
	return state;
}

void pong::get_positions(float &ball_x, float &ball_y, float &paddle_left_x, float &paddle_left_y, float &paddle_right_x, float &paddle_right_y)
{
	ball_x = ball.transform.x;
	ball_y = ball.transform.y;
	paddle_left_x = paddle_left.transform.x;
	paddle_left_y = paddle_left.transform.y;
	paddle_right_x = paddle_right.transform.x;
	paddle_right_y = paddle_right.transform.y;
}

void pong::add_scorechangelistener(scorechangelistener *listener)
{
	score_change_listeners.push_back(listener);
}

void pong::clear_scorechangelisteners()
{
	score_change_listeners.clear();
}

void pong::add_collisionlistener(collisionlistener *listener)
{
	collision_listeners.push_back(listener);
}

void pong::clear_collisionlisteners()
{
	collision_listeners.clear();
}

void pong::paddle_command(paddle_commands command)
{
	switch(command){
		case LEFT_UP:
			paddle_left.transform.yvelocity = settings.paddle_speed_left;
			break;
		case LEFT_DOWN:
			paddle_left.transform.yvelocity = -settings.paddle_speed_left;
			break;
		case LEFT_NONE:
			paddle_left.transform.yvelocity = 0.0f;
			break;
		case RIGHT_UP:
			paddle_right.transform.yvelocity = settings.paddle_speed_right;
			break;
		case RIGHT_DOWN:
			paddle_right.transform.yvelocity = -settings.paddle_speed_right;
			break;
		case RIGHT_NONE:
			paddle_right.transform.yvelocity = 0.0f;
			break;
	}
}

void pong::update_positions(float dt)
{
	// Update paddles
	paddle_left.transform.y += paddle_left.transform.yvelocity * dt;
	paddle_right.transform.y += paddle_right.transform.yvelocity * dt;

	// Clamp paddles
	// Left
	if(paddle_left.transform.y > height - paddle_left.transform.height / 2.0f) {
		paddle_left.transform.y = height - paddle_left.transform.height / 2.0f;
	}
	if(paddle_left.transform.y < paddle_left.transform.height / 2.0f) {
		paddle_left.transform.y = paddle_left.transform.height / 2.0f;
	}

	// Right
	if(paddle_right.transform.y > height - paddle_right.transform.height / 2.0f) {
		paddle_right.transform.y = height - paddle_right.transform.height / 2.0f;
	}
	if(paddle_right.transform.y < paddle_right.transform.height / 2.0f) {
		paddle_right.transform.y = paddle_right.transform.height / 2.0f;
	}

	// Update ball
	ball.transform.x += ball.transform.xvelocity * dt;
	ball.transform.y += ball.transform.yvelocity * dt;
}

void pong::check_collisions()
{
	// Check for collisions
	// Top/bottom wall collisions
	if((ball.transform.y + ball.transform.height / 2.0f > height && ball.transform.yvelocity > 0.0f) || (ball.transform.y - ball.transform.height / 2.0f < 0.0f && ball.transform.yvelocity < 0.0f)){
		ball.transform.yvelocity = -ball.transform.yvelocity;
		notify_collisionlisteners();
	}

	// Checking velocity direction helps avoid extra collisions with same paddle
	if(ball.transform.xvelocity > 0) check_paddle_collision(paddle_right);
	else check_paddle_collision(paddle_left);
}

void pong::check_paddle_collision(pongentity &paddle)
{
	bool paddle_can_reach_x;
	bool paddle_can_reach_y;
	bool is_negative_new_xvelocity;
	
	paddle_can_reach_x = fabs(ball.transform.x - paddle.transform.x) < paddle.transform.width / 2.0f;
	paddle_can_reach_y = fabs(ball.transform.y - paddle.transform.y) < (ball.transform.height + paddle.transform.height) / 2.0f;
	
	if(paddle_can_reach_x && paddle_can_reach_y){
		float speed = sqrt(ball.transform.xvelocity * ball.transform.xvelocity + ball.transform.yvelocity * ball.transform.yvelocity);
		float new_speed = speed + settings.ball_speed_increment;

		// Interpolate reflection angle based on paddle position
		float reflection_angle_deg = settings.paddle_max_reflection_angle_deg * ((ball.transform.y - paddle.transform.y) / ((ball.transform.height + paddle.transform.height) / 2.0f));

		// Reflect ball
		is_negative_new_xvelocity = ball.transform.xvelocity > 0.0f;
		ball.transform.xvelocity = new_speed * cos(reflection_angle_deg * M_PI / 180.0f);
		if(is_negative_new_xvelocity) ball.transform.xvelocity = -ball.transform.xvelocity;
		ball.transform.yvelocity = new_speed * sin(reflection_angle_deg * M_PI / 180.0f);

		notify_collisionlisteners();
	}
}

void pong::check_score()
{
	if(ball.transform.x < 0.0f){
		score_right++;
		ball.transform.x = width / 2.0f;
		ball.transform.y = height / 2.0f;
		ball.transform.xvelocity = -settings.ball_start_speed;
		ball.transform.yvelocity = 0.0f;
		notify_scorechangelisteners();
	}
	else if(ball.transform.x > width){
		score_left++;
		ball.transform.x = width / 2.0f;
		ball.transform.y = height / 2.0f;
		ball.transform.xvelocity = settings.ball_start_speed;
		ball.transform.yvelocity = 0.0f;
		notify_scorechangelisteners();
	}
}

void pong::notify_scorechangelisteners()
{
	for(scorechangelistener *listener : score_change_listeners){
		listener->on_score_changed();
	}
}

void pong::notify_collisionlisteners()
{
	for(collisionlistener *listener : collision_listeners){
		listener->on_collision();
	}
}
