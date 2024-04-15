#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../opengl/Shader.hpp"
#include "../opengl/VertexArray.hpp"
#include "../opengl/Buffer.hpp"
#include "../opengl/Texture.hpp"

namespace mpp
{
	class BlockThumbnailRenderer
	{
	public:
		BlockThumbnailRenderer ();

		void Render ();

	private:
		Camera const * camera { nullptr };

		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::Buffer indexBuffer;
		mpp::VertexArray vertexArray;
	};
}