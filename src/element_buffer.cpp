#include <element_buffer.h>

// Constructor that generates a Element Buffer Object and links it to vertices
ElementBufferObject::ElementBufferObject(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &id_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Binds the element buffer
void ElementBufferObject::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

// Unbinds the element buffer
void ElementBufferObject::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the element buffer
void ElementBufferObject::Delete()
{
	glDeleteBuffers(1, &id_);
}