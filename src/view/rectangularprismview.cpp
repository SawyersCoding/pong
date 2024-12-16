#include "rectangularprismview.hpp"

rectangularprismview::rectangularprismview(float x_size, float y_size, float z_size)
{
	float hx, hy, hz;
	hx = x_size / 2.0f;
	hy = y_size / 2.0f;
	hz = z_size / 2.0f;

	vertices = new float[vertices_size]{
		// positions	 // normals
		// bottom
		-hx, -hy, -hz,	 0.0f,  0.0f, -1.0f,
		 hx,  hy, -hz,	 0.0f,  0.0f, -1.0f,
		 hx, -hy, -hz,	 0.0f,  0.0f, -1.0f,
		-hx,  hy, -hz,	 0.0f,  0.0f, -1.0f,

		// top
		-hx, -hy,  hz,	 0.0f,  0.0f,  1.0f,
		 hx,  hy,  hz,	 0.0f,  0.0f,  1.0f,
		 hx, -hy,  hz,	 0.0f,  0.0f,  1.0f,
		-hx,  hy,  hz,	 0.0f,  0.0f,  1.0f,

		// left
		-hx, -hy, -hz,	-1.0f,  0.0f,  0.0f,
		-hx,  hy,  hz,	-1.0f,  0.0f,  0.0f,
		-hx, -hy,  hz,	-1.0f,  0.0f,  0.0f,
		-hx,  hy, -hz,	-1.0f,  0.0f,  0.0f,

		// right
		 hx, -hy, -hz,	 1.0f,  0.0f,  0.0f,
		 hx,  hy,  hz,	 1.0f,  0.0f,  0.0f,
		 hx, -hy,  hz,	 1.0f,  0.0f,  0.0f,
		 hx,  hy, -hz,	 1.0f,  0.0f,  0.0f,

		// front
		-hx, -hy, -hz,	 0.0f, -1.0f,  0.0f,
		 hx, -hy,  hz,	 0.0f, -1.0f,  0.0f,
		 hx, -hy, -hz,	 0.0f, -1.0f,  0.0f,
		-hx, -hy,  hz,	 0.0f, -1.0f,  0.0f,

		// back
		-hx,  hy, -hz,	 0.0f,  1.0f,  0.0f,
		 hx,  hy,  hz,	 0.0f,  1.0f,  0.0f,
		 hx,  hy, -hz,	 0.0f,  1.0f,  0.0f,
	};

	indeces = new unsigned int[indeces_size]{
		// bottom face
		0, 1, 2,
		0, 3, 1,
		// top face
		4, 5, 6,
		4, 7, 5,
		// left face
		8, 9, 10,
		8, 11, 9,
		// right face
		12, 13, 14,
		12, 15, 13,
		// front face
		16, 17, 18,
		16, 19, 17,
		// back face
		20, 21, 22,
		20, 23, 21
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(float), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeces_size * sizeof(unsigned int), indeces, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

rectangularprismview::~rectangularprismview()
{
	delete[] vertices;
	delete[] indeces;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);	
}

void rectangularprismview::render(shader *s, float x, float y, float z)
{
	s->use();
	s->set_vec3("objcolor", color);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, z));
	s->set_mat4("model", model);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indeces_size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
