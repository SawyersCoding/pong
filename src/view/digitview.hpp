#pragma once

#include "shader/shader.hpp"
#include "stb_image/stb_image.hpp"

class digitview{

	private:
		const static int NDIGITS = 12;

	private:
		int img_width;
		int img_height;
		int img_nchannels;
		unsigned int VBO, VAO;
		unsigned int digit_texture;
		float scale;
		float *vertices;
		

	public:
		digitview(float scale);
		~digitview();

	public:
		void render_digit(shader *digit_shader, int digit, float x, float y);

	private:
		void get_texture_coords(int digit, float &umin, float &vmin, float &umax, float &vmax);
};