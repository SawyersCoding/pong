// More or less as seen in: https://learnopengl.com/Getting-started/Shaders

#include "shader.hpp"
#include <filesystem>

shader::shader(std::string vertexPath, std::string fragmentPath) {

    int success;
    unsigned int vertex_shader, fragment_shader;
    char infoLog[512];
    const char* v_shader_code, * f_shader_code;
    std::string vertex_code, fragment_code;
    std::ifstream v_shader_file, f_shader_file;

    // Step 1: Get the vertex and fragment shader code.
    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // Open the code files
        v_shader_file.open(vertexPath);
        f_shader_file.open(fragmentPath);
		
        std::stringstream v_shader_stream, f_shader_stream;

        // Read the entire code files
        v_shader_stream << v_shader_file.rdbuf();
        f_shader_stream << f_shader_file.rdbuf();

        // Close the code files
        v_shader_file.close();
        f_shader_file.close();

        // Convert the code files to strings
        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
    }
    catch (std::ifstream::failure &e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		std::cout << e.what() << std::endl;
	}

    v_shader_code = vertex_code.c_str();
    f_shader_code = fragment_code.c_str();

    // Step 2: Compile the shaders
    // vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &v_shader_code, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
    // fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &f_shader_code, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // shader program
    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

    // Delete the shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

}

void shader::use() {
    glUseProgram(id);
}

unsigned int shader::get_id() {
    return id;
}

void shader::set_bool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void shader::set_int(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void shader::set_float(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void shader::set_vec3(const std::string &name, const glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void shader::set_mat4(const std::string &name, const glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
