#pragma once

#include <vector>
#include <glad/glad.h>

namespace mpp
{
	class Buffer
	{
	public:
		Buffer ();
		~Buffer ();

		void SetData ( void const * data, unsigned int size, GLenum usage );
		void Bind ( GLenum target );

		template < class ElementType >
		void SetData ( std::vector <ElementType> const & elements, GLenum usage );

	private:
		GLuint buffer;
		friend class VertexArray;
	};



	// Implementation
	template < class ElementType >
	void Buffer::SetData ( std::vector <ElementType> const & elements, GLenum usage )
	{
		SetData ( elements.data (), elements.size () * sizeof ( ElementType ), usage );
	}
}