# pragma once

#include "shader/shader.hpp"

class paddle3dview{

	private:
		unsigned int VBO, VAO, EBO;
		unsigned int *indeces;
		float *vertices;
		constexpr static glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f); // white

	public:
		paddle3dview(float paddle_width, float paddle_height);
		~paddle3dview();

	public:
		void render_paddle(shader *pong_shader, float px, float py);

};