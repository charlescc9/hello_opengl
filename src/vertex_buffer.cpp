#include <vertex_buffer.h>

// Constructor that generates a Vertex Buffer Object and links it to vertices
VertexBufferObject::VertexBufferObject(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ARRAY_BUFFER, id_);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds the vertex buffer
void VertexBufferObject::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id_);
}

// Unbinds the vertex buffer
void VertexBufferObject::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the vertex buffer
void VertexBufferObject::Delete()
{
	glDeleteBuffers(1, &id_);
}