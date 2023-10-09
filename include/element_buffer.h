#pragma once

#include <glad/glad.h>

class ElementBufferObject {
public:
    // Constructor that generates an Element Buffer Object and links it to vertices
	ElementBufferObject(GLuint* indices, GLsizeiptr size);

	// Binds the element buffer
    void Bind();
	
    // Unbinds the element buffer
	void Unbind();
	
    // Deletes the element buffer
	void Delete();

private:
    // Reference ID of the element buffer
	GLuint id_;
};
