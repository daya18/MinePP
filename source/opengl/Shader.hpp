#pragma once

#include <unordered_map>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>

namespace mpp
{
	class Camera;

	class Shader
	{
	public:
		Shader ();
		Shader ( std::string const & file );
		~Shader ();
		
		void LoadFromFile ( std::string const & file );
		
		void Bind ();

		void SetUniform ( std::string const &, int );
		void SetUniform ( std::string const &, glm::mat4 const & );
		void SetUniform ( std::string const &, std::vector <glm::mat4> const & );
		void SetUniform ( std::string const &, glm::vec4 const & );

	private:
		GLint GetUniformLocation ( std::string const & );
		GLuint program;
		std::unordered_map < std::string, GLint > uniformLocations;
	};
}