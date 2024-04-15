#include "Framebuffer.hpp"

#include "Texture.hpp"
#include <iostream>

namespace mpp
{
	Framebuffer::Framebuffer ()
	{
		glGenFramebuffers ( 1, &framebuffer );
		Bind ();
		glGenRenderbuffers ( 1, &depthBuffer );
		glBindRenderbuffer ( GL_RENDERBUFFER, depthBuffer );
		glRenderbufferStorage ( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 3000, 3000 );
		glFramebufferRenderbuffer ( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer );
		Unbind ();
	}

	Framebuffer::~Framebuffer ()
	{
	}
	void Framebuffer::BindTexture ( Texture & texture )
	{
		Bind ();
		glFramebufferTexture ( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture.texture, 0 );

		GLenum drawBuffers [ 1 ] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers ( 1, drawBuffers );
		Unbind ();
	}

	void Framebuffer::Bind ()
	{
		glBindFramebuffer ( GL_FRAMEBUFFER, framebuffer );
	}

	void Framebuffer::Unbind ()
	{
		glBindFramebuffer ( GL_FRAMEBUFFER, 0 );
	}
}