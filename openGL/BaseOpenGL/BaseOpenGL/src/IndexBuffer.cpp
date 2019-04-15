#include "IndexBuffer.h"
#include "Render.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	GLCall(glGenBuffers(1, &m_RenderID));	//made a buffer
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));	//assigned/bound buffer
	//for triangle
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));	//fill buffer with data, or NULL instead of GL_ARRAY_BUFFER
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RenderID));
}
void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));	//assigned/bound buffer
}

void IndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));	//assigned/bound buffer
}

