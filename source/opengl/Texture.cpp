#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cassert>
#include <filesystem>
#include <iostream>

namespace mpp
{
	Texture::Texture ()
	{
		glGenTextures ( 1, &texture );
	}

	Texture::Texture ( std::string const & path )
		: Texture ()
	{
		assert ( std::filesystem::exists ( path ) );

		int width { 0 }, height { 0 };
		stbi_set_flip_vertically_on_load ( 1 );
		auto data { stbi_load ( path.data (), &width, &height, nullptr, 4 ) };

		glBindTexture ( GL_TEXTURE_2D, texture );
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
		
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	}

	void Texture::Bind ( GLuint unit )
	{
		glActiveTexture ( GL_TEXTURE0 + unit );
		glBindTexture ( GL_TEXTURE_2D, texture );
	}
}