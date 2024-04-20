#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace mpp
{
	Texture::Texture ()
	{
		glGenTextures ( 1, &texture );
		
		Bind ();
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		Unbind ();
	}

	Texture::Texture ( glm::vec2 const & size )
		: Texture ()
	{
		Bind ();
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );
		this->size = size;
		Unbind ();
	}

	Texture::Texture ( std::string const & path )
		: Texture ()
	{
		assert ( std::filesystem::exists ( path ) );

		int width { 0 }, height { 0 };
		stbi_set_flip_vertically_on_load ( 1 );
		auto data { stbi_load ( path.data (), &width, &height, nullptr, 4 ) };

		Bind ();
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
		size = { width, height };
		Unbind ();
	}
	
	void Texture::SetData ( unsigned char const * data, glm::vec2 const & size, GLenum format )
	{
		Bind ();
		glTexImage2D ( GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data );
		Unbind ();
	}

	void Texture::Bind ( GLuint unit ) const
	{
		glActiveTexture ( GL_TEXTURE0 + unit );
		glBindTexture ( GL_TEXTURE_2D, texture );
	}
	
	void Texture::Unbind ( GLuint unit ) const
	{
		glActiveTexture ( GL_TEXTURE0 + unit );
		glBindTexture ( GL_TEXTURE_2D, 0 );
	}
}