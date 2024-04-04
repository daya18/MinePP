#include "Type.hpp"

#include <stdexcept>

namespace mpp
{
	GLuint GetSize ( GLenum type )
	{
		switch ( type )
		{
		case GL_UNSIGNED_INT:	return sizeof ( GLuint );
		case GL_FLOAT:			return sizeof ( GLfloat );
		case GL_INT:			return sizeof ( GLint );

		default: throw std::runtime_error { "Invalid type" };
		}
	}
}