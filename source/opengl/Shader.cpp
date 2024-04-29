#include "Shader.hpp"

namespace mpp
{
	Shader::Shader ()
	{
		program = glCreateProgram ();
	}

	Shader::Shader ( std::string const & file )
		: Shader ()
	{
		LoadFromFile ( file );
	}

	Shader::~Shader ()
	{
	}

	void Shader::LoadFromFile ( std::string const & file )
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
			GLint length { static_cast < GLint > ( shaderInfo.source.size () ) };
			glShaderSource ( shaders.back (), 1, &source, &length );

			glCompileShader ( shaders.back () );

			GLint success;
			glGetShaderiv(shaders.back(), GL_COMPILE_STATUS, &success);

			if (!success) {
				GLint logLength;
				glGetShaderiv(shaders.back(), GL_INFO_LOG_LENGTH, &logLength);
				char* log = new char[logLength];
				glGetShaderInfoLog(shaders.back(), logLength, NULL, log);
				std::cerr << "Error: Shader compilation failed\n" << log << std::endl;
				delete[] log;
			}

			glAttachShader ( program, shaders.back () );
		}

		glLinkProgram ( program );

		GLint success;
		GLchar infoLog[512];
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			std::cerr << "Error: OpenGL program linking failed\n" << infoLog << std::endl;
		}

		for ( auto const & shader : shaders )
			glDeleteShader ( shader );
	}

	void Shader::SetUniform ( std::string const & name, glm::mat4 const & data )
	{
		glUniformMatrix4fv ( GetUniformLocation ( name ), 1, GL_FALSE, glm::value_ptr ( data ) );
	}
	
	void Shader::SetUniform ( std::string const & name, int data )
	{
		glUniform1i ( GetUniformLocation ( name ), data );
	}
	
	void Shader::SetUniform ( std::string const & name, std::vector <glm::mat4> const & data )
	{
		glUniformMatrix4fv ( GetUniformLocation ( name ), data.size (), GL_FALSE, glm::value_ptr ( data [0] ) );
	}

	void Shader::SetUniform ( std::string const & name, glm::vec4 const & data )
	{
		glUniform4f ( GetUniformLocation ( name ), data.x, data.y, data.z, data.w );
	}

	void Shader::Bind ()
	{
		glUseProgram ( program );
	}

	GLint Shader::GetUniformLocation ( std::string const & name )
	{
		auto locationIt { uniformLocations.find ( name ) };
		
		if ( locationIt == uniformLocations.end () )
			locationIt = uniformLocations.emplace ( name, glGetUniformLocation ( program, name.data () ) ).first;

		return locationIt->second;
	}

	GLuint Shader::GetUniformBlockIndex ( std::string const & name )
	{
		auto indexIt { uniformBlockIndices.find ( name ) };

		if ( indexIt == uniformBlockIndices.end () )
			indexIt = uniformBlockIndices.emplace ( name, glGetUniformBlockIndex ( program, name.data () ) ).first;

		return indexIt->second;
	}

	void Shader::SetUniformBlockBinding ( std::string const & name, GLuint binding )
	{
		glUniformBlockBinding ( program, GetUniformBlockIndex ( name ), binding );
	}
}
