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

		void SetUniform ( std::string const &, glm::mat4 const & );
		GLint GetUniformLocation ( std::string const & );

	private:
		GLuint program;
		std::unordered_map < std::string, GLint > uniformLocations;
	};
}