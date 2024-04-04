#pragma once

#include <vector>

#include <glad/glad.h>

namespace mpp
{
	class Buffer;

	class VertexArray
	{
	public:
		struct AttributeDescription { GLenum type; int count; };
		
		VertexArray ( std::vector <AttributeDescription> const & attributeDescriptions );
		~VertexArray ();
		
		void Bind ();
		void BindVertexBuffer ( Buffer const & vertexBuffer );

	private:
		GLuint vertexArray;
		unsigned int vertexSize;
	};
}