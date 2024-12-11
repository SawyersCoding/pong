// More or less as seen in: https://learnopengl.com/Getting-started/Shaders

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class shader {

	private:
		unsigned int id;

	public:
		shader(std::string vertexPath, std::string fragmentPath);

	public:
		void use();
		unsigned int get_id();
		void set_bool(const std::string &name, bool value) const;
		void set_int(const std::string &name, int value) const;
		void set_float(const std::string &name, float value) const;
		void set_vec3(const std::string &name, const glm::vec3 value) const;
		void set_mat4(const std::string &name, const glm::mat4 value) const;

};

#endif // SHADER_H