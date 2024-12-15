#pragma once

#include "shader/shader.hpp"
#include "stb_image/stb_image.hpp"


class staticquadtextureview{

	private:
		unsigned int VBO, VAO, EBO;
		unsigned int texture;
		unsigned int *indeces;
		float *vertices;

	public:
		staticquadtextureview(const char *texture_path);
		~staticquadtextureview();

	public:
		void render_quad(shader *shader);

};