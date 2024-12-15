#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "digitview.hpp"
#include "ballview.hpp"
#include "paddleview.hpp"
#include "shader/shader.hpp"

class pongview{

	private:
		const static int PX_PER_UNIT = 25;
		constexpr static float DIGIT_HEIGHT_FACTOR = 0.8f;
		constexpr static glm::vec3 CAMERA_POS = glm::vec3(0.0f, 0.0f, 5.0f);
		constexpr static glm::vec3 CAMERA_TARGET = glm::vec3(0.0f);
		constexpr static glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f,  0.0f);

	private:
		int px_width;
		int px_height;
		int px_score_height;
		float dx_left, dx_right, dy;
		shader *pong_shader;
		shader *single_texture_shader;
		digitview *dview;
		ballview *bview;
		paddleview *pview;
		GLFWwindow *window;
		glm::mat4 projection;
		glm::mat4 view;

	public:
		pongview(int width, int height, int score_height, float paddle_width_left, float paddle_height_left, float paddle_width_right, float paddle_height_right, float ball_size);
		~pongview();

	public:
		void render_pong(int score_left, int score_right, float bx, float by, float lx, float ly, float rx, float ry);
		GLFWwindow* get_window();

	private:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};