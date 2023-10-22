#include <vertex_array.h>

// Constructor that generates a Vertex Array Object ID
VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &id_);
}

// Links a vertex buffer to the vertex array using a certain layout
void VertexArrayObject::LinkVertextBuffer(VertexBufferObject& vertex_buffer, GLuint layout, 
										  GLuint num_componenets, GLenum type, GLsizeiptr stride, 
										  void* offset)
{
	vertex_buffer.Bind();
	glVertexAttribPointer(layout, num_componenets, type, GL_FALSE, stride, offset);
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
