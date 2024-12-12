#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ballview.hpp"
#include "paddleview.hpp"
#include "shader/shader.hpp"

class pongview{

	private:
		const static int px_per_unit = 25;
		constexpr static float pitch = 0.0f;
		constexpr static float yaw = -90.0f;
		constexpr static glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 5.0f);
		constexpr static glm::vec3 camera_target = glm::vec3(0.0f);
		constexpr static glm::vec3 camera_up = glm::vec3(0.0f, 1.0f,  0.0f);

	private:
		int px_width;
		int px_height;
		int px_score_height;
		shader *pong_shader;
		// camera *cam;
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