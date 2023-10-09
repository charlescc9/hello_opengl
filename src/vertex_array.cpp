#include <vertex_array.h>

// Constructor that generates a Vertex Array Object ID
VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &id_);
}

// Links a vertex buffer to the vertex array using a certain layout
void VertexArrayObject::LinkVertextBuffer(VertexBufferObject& vertex_buffer, GLuint layout)
{
	vertex_buffer.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	vertex_buffer.Unbind();
}

// Binds the vertex array
void VertexArrayObject::Bind()
{
	glBindVertexArray(id_);
}

// Unbinds the vertex array
void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the vertex array
void VertexArrayObject::Delete()
{
	glDeleteVertexArrays(1, &id_);
}