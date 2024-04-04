#include "VertexArray.hpp"

#include "Type.hpp"
#include "Buffer.hpp"

namespace mpp
{
	VertexArray::VertexArray ( std::vector <AttributeDescription> const & attributeDescriptions )
	{
		glGenVertexArrays ( 1, & vertexArray );

		int attributeIndex { 0 };
		int offset { 0 };
		vertexSize = 0;

		for ( auto const & attributeDescription : attributeDescriptions )
		{
			glBindVertexArray ( vertexArray );

			glEnableVertexAttribArray ( attributeIndex );
			glVertexAttribFormat ( attributeIndex, attributeDescription.count, attributeDescription.type, GL_FALSE, offset );
			glVertexAttribBinding ( attributeIndex, 0 );

			offset += GetSize ( attributeDescription.type ) * attributeDescription.count;
			++attributeIndex;
		}

		vertexSize = offset;
	}

	VertexArray::~VertexArray ()
	{
	}
	
	void VertexArray::Bind ()
	{
		glBindVertexArray ( vertexArray );
	}

	void VertexArray::BindVertexBuffer ( Buffer const & vertexBuffer )
	{
		glBindVertexBuffer ( 0, vertexBuffer.buffer, 0, vertexSize );
	}
}