#pragma once

namespace mpp
{
	class Buffer;

	class VertexArray
	{
	public:
		struct AttributeDescription { GLenum type; int count; };
		
		VertexArray ();
		VertexArray ( std::vector <AttributeDescription> const & attributeDescriptions );
		~VertexArray ();
		
		void SetFormat ( std::vector <AttributeDescription> const & attributeDescriptions );

		void Bind ();
		void BindVertexBuffer ( Buffer const & vertexBuffer );

	private:
		GLuint vertexArray { 0 };
		unsigned int vertexSize { 0 };
	};
}