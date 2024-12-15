#include "paddle3dview.hpp"

paddle3dview::paddle3dview(float paddle_width, float paddle_height)
{
	float half_width = paddle_width / 2.0f;
	float half_height = paddle_height / 2.0f;

	vertices = new float[24]{
		-half_width, -half_height, -half_width, // 0
		 half_width,  half_height, -half_width, // 1
		 half_width, -half_height, -half_width, // 2
		-half_width,  half_height, -half_width, // 3
		-half_width, -half_height,  half_width, // 4
		 half_width,  half_height,  half_width, // 5
		 half_width, -half_height,  half_width, // 6
		-half_width,  half_height,  half_width  // 7
	};

	indeces = new unsigned int[36]{
		// bottom face
		0, 1, 2,
		0, 3, 1,
		// top face
		4, 5, 6,
		4, 7, 5,
		// left face
		0, 4, 7,
		0, 3, 7,
		// right face
		1, 5, 6,
		1, 2, 6,
		// front face
		0, 2, 6,
		0, 4, 6,
		// back face
		3, 1, 5,
		3, 7, 5
	};
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indeces, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

paddle3dview::~paddle3dview()
{
	delete[] vertices;
	delete[] indeces;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
}

void paddle3dview::render_paddle(shader *pong_shader, float px, float py)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(px, py, 0.0f));
	pong_shader->use();
	pong_shader->set_mat4("model", model);
	pong_shader->set_vec3("color", color);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
