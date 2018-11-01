#pragma once

#include <memory>
class GL_List
{
public:
	GL_List() : i(glGenLists(1)) {}
	GL_List(const GL_List&) = delete;
	~GL_List() { glDeleteLists(i, 1); }
	

	void New(GLenum mode = GL_COMPILE)
	{
		glNewList(i, mode);
	}
	void End(void)
	{
		glEndList();
	}
	void Call()
	{
		glCallList(i);
	}
private:
	GLuint i;
};