#pragma once

struct pongsettings{

	private:
		constexpr static float PADDLE_WIDTH_LEFT_DEFAULT = 0.5f;
		constexpr static float PADDLE_HEIGHT_LEFT_DEFAULT = 3.0f;
		constexpr static float PADDLE_WIDTH_RIGHT_DEFAULT = 0.5f;
		constexpr static float PADDLE_HEIGHT_RIGHT_DEFAULT = 3.0f;
		constexpr static float PADDLE_MAX_REFLECTION_ANGLE_DEG_DEFAULT = 60.0f;
		constexpr static float PADDLE_SPEED_LEFT_DEFAULT = 5.0f;
		constexpr static float PADDLE_SPEED_RIGHT_DEFAULT = 5.0f;
		constexpr static float BALL_SIZE_DEFAULT = 0.25f;
		constexpr static float BALL_START_SPEED_DEFAULT = 5.0f;
		constexpr static float BALL_SPEED_INCREMENT_DEFAULT = 1.0f;
		const static int WINNING_SCORE_DEFAULT = 10;
	
	public:
		float paddle_width_left;
		float paddle_height_left;
		float paddle_width_right;
		float paddle_height_right;
		float paddle_max_reflection_angle_deg;
		float paddle_speed_left;
		float paddle_speed_right;
		float ball_size;
		float ball_start_speed;
		float ball_speed_increment;
		int winning_score;

	public:
		pongsettings(float paddle_width_left = PADDLE_WIDTH_LEFT_DEFAULT, float paddle_height_left = PADDLE_HEIGHT_LEFT_DEFAULT, float paddle_width_right = PADDLE_WIDTH_RIGHT_DEFAULT, float paddle_height_right = PADDLE_HEIGHT_RIGHT_DEFAULT, float paddle_speed_left = PADDLE_SPEED_LEFT_DEFAULT, float paddle_max_reflection_angle_deg = PADDLE_MAX_REFLECTION_ANGLE_DEG_DEFAULT, float paddle_speed_right = PADDLE_SPEED_RIGHT_DEFAULT, float ball_size = BALL_SIZE_DEFAULT, float ball_start_speed = BALL_START_SPEED_DEFAULT, float ball_speed_increment = BALL_SPEED_INCREMENT_DEFAULT, int winning_score = WINNING_SCORE_DEFAULT) : paddle_width_left(paddle_width_left), paddle_height_left(paddle_height_left), paddle_width_right(paddle_width_right), paddle_height_right(paddle_height_right), paddle_max_reflection_angle_deg(paddle_max_reflection_angle_deg), paddle_speed_left(paddle_speed_left), paddle_speed_right(paddle_speed_right), ball_size(ball_size), ball_start_speed(ball_start_speed), ball_speed_increment(ball_speed_increment), winning_score(winning_score) {}
};