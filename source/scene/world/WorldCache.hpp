#pragma once

#include <string>

#include "../../opengl/Shader.hpp"
#include "../../opengl/VertexArray.hpp"
#include "../../opengl/Buffer.hpp"
#include "../../opengl/Texture.hpp"
#include "../../core/Constants.hpp"

namespace mpp
{
	class BlockCache;

	class WorldCache
	{
	public:
		WorldCache ( BlockCache & );
		~WorldCache ();

	private:
		BlockCache * blockCache;
		
		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::Buffer indexBuffer;
		mpp::VertexArray vertexArray;
		mpp::Texture texture;
		mpp::Texture outlineMask;

		friend class Chunk;
		friend class Block;
	};
}