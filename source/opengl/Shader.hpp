#pragma once

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

		GLuint GetUniformBlockIndex ( std::string const & name );
		void SetUniformBlockBinding ( std::string const & name, GLuint binding );

	private:
		GLint GetUniformLocation ( std::string const & );
		GLuint program;
		std::unordered_map < std::string, GLint > uniformLocations;
		std::unordered_map < std::string, GLuint > uniformBlockIndices;
	};
}