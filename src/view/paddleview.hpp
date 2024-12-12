#pragma once
#include "shader/shader.hpp"

class paddleview{

	private:
		unsigned int VBO, VAO;
		float *vertices;
		constexpr static glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f); // white

	public:
		paddleview(float paddle_width, float paddle_height);
		~paddleview();

	public:
		void render_paddle(shader *pong_shader, float px, float py);

};