#pragma once

#include <glad/glad.h>

namespace mpp
{
	class Texture;

	class Framebuffer
	{
	public:
		Framebuffer ();
		~Framebuffer ();

		void BindTexture ( Texture & );

		void Bind ();
		void Unbind ();

	private:
		GLuint framebuffer;
		GLuint depthBuffer;

	};
}