#pragma once

#include <glad/glad.h>

#include <string>

#include <glm/glm.hpp>

namespace mpp
{
	class Texture
	{
	public:
		Texture ();
		Texture ( glm::vec2 const & size );
		Texture ( std::string const & );
		
		void Bind ( GLuint unit = 0 ) const;
		void Unbind ( GLuint unit = 0 ) const;

		glm::vec2 const & GetSize () const;

	private:
		void SetDefaultParameters ();

		glm::vec2 size { 0.0f, 0.0f };
		GLuint texture;

		friend class Framebuffer;
	};



	// Implementation
	inline glm::vec2 const & Texture::GetSize () const { return size; }
}