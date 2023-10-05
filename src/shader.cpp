#include "shader.h"

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

Shader::Shader(const char* vertex_file, const char* fragment_file)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertex_code = GetFileContents(vertex_file);
	std::string fragment_code = GetFileContents(fragment_file);

	// Convert the shader source strings into character arrays
	const char* vertex_source = vertex_code.c_str();
	const char* fragment_source = fragment_code.c_str();

	// Create Vertex Shader Object and get its reference
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glCheckError();

    // Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCheckError();

    // Compile the Vertex Shader into machine code
	glCompileShader(vertex_shader);
    glCheckError();

	// Create Fragment Shader Object and get its reference
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	
    // Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCheckError();

    // Compile the Vertex Shader into machine code
	glCompileShader(fragment_shader);
    glCheckError();

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	std::cout << ID << std::endl;

    // Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);
	glCheckError();

    // Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
    glCheckError();

	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
    glCheckError();
}

void Shader::Activate()
{
	glUseProgram(ID);
    glCheckError();
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

std::string Shader::GetFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	} else {
        std::cout << "Invalid filename" << std::endl;
    }
	throw(errno);
}
