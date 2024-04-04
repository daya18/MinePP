#pragma once

#include <string>

#include <glad/glad.h>

namespace mpp
{
	class Shader
	{
	public:
		Shader ( std::string const & file );
		~Shader ();
		
		void Bind ();

	private:
		GLuint program;
	};
}