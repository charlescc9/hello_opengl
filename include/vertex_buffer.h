#pragma once

#include <glad/glad.h>

class VertexBufferObject {
public:
    // Constructor that generates a Vertex Buffer Object and links it to vertices
	VertexBufferObject(GLfloat* vertices, GLsizeiptr size);

	// Binds the vertex buffer
    void Bind();
	
    // Unbinds the vertex buffer
	void Unbind();
	
    // Deletes the vertex buffer
	void Delete();

private:
    // Reference ID of the vertex buffer
	GLuint id_;
};
