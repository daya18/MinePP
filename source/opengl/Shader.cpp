#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cassert>

namespace mpp
{
	Shader::Shader ( std::string const & file )
		: program ( glCreateProgram () )
	{
		struct ShaderInfo
		{
			GLenum type;
			std::string source;
		};

		std::vector <ShaderInfo> shaderInfos;

		assert ( std::filesystem::exists ( file ) );

		std::ifstream fileStream { file };

		std::string line;
		while ( fileStream.good () )
		{
			std::getline ( fileStream, line );
		
			if ( line.find ( "#shader" ) != line.npos )
			{
				GLenum shaderType =
					  line == "#shader vertex" ? GL_VERTEX_SHADER
					: line == "#shader fragment" ? GL_FRAGMENT_SHADER
					: throw std::runtime_error { "Invalid shader type" };

				shaderInfos.push_back ( { shaderType } );
				continue;
			}

			if ( ! shaderInfos.empty () )
			{
				auto shaderSourceLine { line + "\n" };
				shaderInfos.back ().source.insert ( shaderInfos.back ().source.size (), shaderSourceLine );
			}
		}

		std::vector <GLuint> shaders;
		for ( auto const & shaderInfo : shaderInfos )
		{
			shaders.push_back ( glCreateShader ( shaderInfo.type ) );

			char const * source { shaderInfo.source.data () };
			GLint length { static_cast <GLint> ( shaderInfo.source.size () ) };
			glShaderSource ( shaders.back (), 1, &source, &length );

			glCompileShader ( shaders.back () );

			glAttachShader ( program, shaders.back () );
		}

		glLinkProgram ( program );

		for ( auto const & shader : shaders )
			glDeleteShader ( shader );
	}

	Shader::~Shader ()
	{

	}

	void Shader::Bind ()
	{
		glUseProgram ( program );
	}

}