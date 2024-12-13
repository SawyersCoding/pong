#include "digitview.hpp"

digitview::digitview(float scale) : scale(scale)
{
	glGenTextures(1, &digit_texture);
	glBindTexture(GL_TEXTURE_2D, digit_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char *img = stbi_load("resources/pong_digits.png", &img_width, &img_height, &img_nchannels, STBI_rgb_alpha);

	if(img){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	}
	else{
		std::cerr << "Failed to load digit texture" << std::endl;
		exit(EXIT_FAILURE);
	}
	stbi_image_free(img);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 30 * sizeof(float), nullptr, GL_DYNAMIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

digitview::~digitview()
{
	delete[] vertices;
	glDeleteTextures(1, &digit_texture);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void digitview::render_digit(shader *digit_shader, int digit, float x, float y)
{
	// Do not render if digit is negative
	if(digit < 0) return;

	float umin, vmin, umax, vmax;
	get_texture_coords(digit, umin, vmin, umax, vmax);

	vertices = new float[30]{
		// positions		// texture coords
		// lower right
		-0.5f, -0.5f, 0.0f,	umin, vmax,
		 0.5f, -0.5f, 0.0f,	umax, vmax,
		 0.5f,  0.5f, 0.0f,	umax, vmin,
		 // upper left
		 0.5f,  0.5f, 0.0f,	umax, vmin,
		-0.5f,  0.5f, 0.0f,	umin, vmin,
		-0.5f, -0.5f, 0.0f,	umin, vmax
	};

	digit_shader->use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, 0.0f));
	model = glm::scale(model, glm::vec3(scale));

	digit_shader->set_mat4("model", model);
	digit_shader->set_int("digit_texture", 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 30 * sizeof(float), vertices);

	glBindTexture(GL_TEXTURE_2D, digit_texture);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void digitview::get_texture_coords(int digit, float &umin, float &vmin, float &umax, float &vmax)
{
	float ustep = 1.0f / NDIGITS;
	umin = digit * ustep;
	umax = (digit + 1) * ustep;
	vmin = 0.0f;
	vmax = 1.0f;
}
