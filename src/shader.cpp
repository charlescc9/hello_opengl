#include <shader.h>

GLenum glCheckError_(const char *file, int line) {
	GLenum error_code;
	while ((error_code = glGetError()) != GL_NO_ERROR) {
		std::string error;
		switch (error_code) {
			case GL_INVALID_ENUM:
				error = "INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				error = "INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				error = "INVALID_OPERATION";
				break;
			case GL_STACK_OVERFLOW:
				error = "STACK_OVERFLOW";
				break;
			case GL_STACK_UNDERFLOW:
				error = "STACK_UNDERFLOW";
				break;
			case GL_OUT_OF_MEMORY:
				error = "OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error = "INVALID_FRAMEBUFFER_OPERATION";
				break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return error_code;
}

std::string GetFileContents(const char *filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	} else {
		std::cout << "Invalid filename" << std::endl;
	}
	throw(errno);
}

Shader::Shader(const char *vertex_file, const char *fragment_file) {
	// Read vertex and fragment shaders from file and store the strings
	std::string vertex_code = GetFileContents(vertex_file);
	std::string fragment_code = GetFileContents(fragment_file);

	// Convert the shader source strings into character arrays
	const char *vertex_source = vertex_code.c_str();
	const char *fragment_source = fragment_code.c_str();

	// Create vertext shader and get its reference
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glCheckError();

	// Attach vertex shader source to the vertex shader object
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCheckError();

	// Compile the vertex shader into machine code
	glCompileShader(vertex_shader);
	glCheckError();

	// Create fragment shader and get its reference
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	// Attach fragment shader source to the fragment shader object
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCheckError();

	// Compile the fragment shader into machine code
	glCompileShader(fragment_shader);
	glCheckError();

	// Create shader program and get its reference
	id = glCreateProgram();

	// Attach the vertex and fragment shaders to the shader program
	glAttachShader(id, vertex_shader);
	glAttachShader(id, fragment_shader);
	glCheckError();

	// Link all the shaders together into the shader program
	glLinkProgram(id);
	glCheckError();

	// Delete the now useless vertex and fragment shader objects
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glCheckError();
}

void Shader::Activate() {
	glUseProgram(id);
}

void Shader::Delete() {
	glDeleteProgram(id);
}
