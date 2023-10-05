#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

class Shader
{
public:
    // Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate();
	
    // Deletes the Shader Program
	void Delete();

    // Get file contents as string
    std::string GetFileContents(const char* filename);

    // Reference ID of the Shader Program
	GLuint ID;
};

#endif
