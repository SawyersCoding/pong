#include "paddleview.hpp"

paddleview::paddleview(float paddle_width, float paddle_height)
{
	float half_width = paddle_width / 2.0f;
	float half_height = paddle_height / 2.0f;
	vertices = new float[18]{
		// lower right
		-half_width, -half_height, 0.0f,
		 half_width, half_height, 0.0f,
		 half_width, -half_height, 0.0f,
		// upper left
		-half_width, half_height, 0.0f,
		 half_width, half_height, 0.0f,
		-half_width, -half_height, 0.0f
	};

	// Sets up VAO.
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

paddleview::~paddleview()
{
	delete[] vertices;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void paddleview::render_paddle(shader *pong_shader, float px, float py)
{
	pong_shader->use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(px, py, 0.0f));
	pong_shader->set_mat4("model", model);
	pong_shader->set_vec3("color", color);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
