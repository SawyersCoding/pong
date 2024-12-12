#pragma once
#include "shader/shader.hpp"

class ballview{

	private:
		unsigned int VBO, VAO;
		float *vertices;
		constexpr static glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f); // white

	public:
		ballview(float ball_size);
		~ballview();

	public:
		void render_ball(shader *pong_shader, float bx, float by);

};