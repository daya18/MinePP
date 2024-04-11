#pragma once

#include <glad/glad.h>

#include <string>

namespace mpp
{
	class Texture
	{
	public:
		Texture ();
		Texture ( std::string const & );

		void Bind ( GLuint unit );

	private:
		GLuint texture;
	};
}