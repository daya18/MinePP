#pragma once

namespace mpp
{
	class Texture
	{
	public:
		Texture ();
		Texture ( glm::vec2 const & size );
		Texture ( std::string const & );
		
		void SetData ( unsigned char const * data, glm::vec2 const & size, GLenum format );
		void Bind ( GLuint unit = 0 ) const;
		void Unbind ( GLuint unit = 0 ) const;

		glm::vec2 const & GetSize () const;

	private:
		glm::vec2 size { 0.0f, 0.0f };
		GLuint texture;

		friend class Framebuffer;
	};



	// Implementation
	inline glm::vec2 const & Texture::GetSize () const { return size; }
}