# pragma once

#include "shader/shader.hpp"

class rectangularprismview{

	private:
		static const int vertices_size = 144;
		static const int indeces_size = 36;
		unsigned int VBO, VAO, EBO;
		unsigned int *indeces;
		float *vertices;
		constexpr static glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f); // white

	public:
		rectangularprismview(float x_size, float y_size, float z_size = 1.0f);
		~rectangularprismview();

	public:
		void render(shader *s, float x = 0.0f, float y= 0.0f, float z = 0.0f);

};