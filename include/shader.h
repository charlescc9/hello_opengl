#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Print out OpenGL errors
GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

// Get file contents as string
std::string GetFileContents(const char* filename);

class Shader {
public:
    // Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertex_file, const char* fragment_file);

	// Activates the Shader Program
	void Activate();
	
    // Deletes the Shader Program
	void Delete();

private:
    // Reference ID of the Shader Program
	GLuint id_;
};
