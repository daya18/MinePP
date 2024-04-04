#include "Buffer.hpp"

namespace mpp
{
	Buffer::Buffer ()
	{
		glCreateBuffers ( 1, &buffer );
	}

	Buffer::~Buffer ()
	{
	}

	void Buffer::SetData ( void const * data, unsigned int size, GLenum usage )
	{
		glNamedBufferData ( buffer, size, data, usage );
	}

	void Buffer::Bind ( GLenum target )
	{
		glBindBuffer ( target, buffer );
	}
}