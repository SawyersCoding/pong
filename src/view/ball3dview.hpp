# pragma once

#include "shader/shader.hpp"

class ball3dview{

	private:
		unsigned int VBO, VAO, EBO;
		unsigned int *indeces;
		float *vertices;
		constexpr static glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f); // white

	public:
		ball3dview(float ball_size);
		~ball3dview();

	public:
		void render_ball(shader *pong_shader, float bx, float by);

};