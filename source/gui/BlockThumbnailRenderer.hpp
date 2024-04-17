#pragma once

#include "../opengl/Shader.hpp"
#include "../opengl/VertexArray.hpp"
#include "../opengl/Buffer.hpp"
#include "../opengl/Texture.hpp"
#include "../opengl/Framebuffer.hpp"

namespace mpp
{
	class BlockThumbnailRenderer
	{
	public:
		BlockThumbnailRenderer ();

		void Render ( Texture & in, Texture & out );

	private:
		Camera const * camera { nullptr };

		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::Buffer indexBuffer;
		mpp::VertexArray vertexArray;
		mpp::Framebuffer framebuffer;
	};
}