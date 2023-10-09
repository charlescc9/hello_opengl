#pragma once

#include <glad/glad.h>
#include <vertex_buffer.h>

class VertexArrayObject
{
public:
	// Constructor that generates a Vertex Array Object ID
	VertexArrayObject();

	// Links a vertex buffer to the vertex array using a certain layout
	void LinkVertextBuffer(VertexBufferObject& vertex_buffer, GLuint layout);
	
    // Binds the vertex array
	void Bind();
	
    // Unbinds the vertex array
	void Unbind();
	
    // Deletes the vertex array
	void Delete();

private:
    // Reference ID of the vertex array
	GLuint id_;
};
