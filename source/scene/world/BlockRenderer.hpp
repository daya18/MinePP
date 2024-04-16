#pragma once

#include <string>

#include <glm/glm.hpp>

#include "../../opengl/Shader.hpp"
#include "../../opengl/VertexArray.hpp"
#include "../../opengl/Buffer.hpp"
#include "../../opengl/Texture.hpp"

namespace mpp
{
	class BlockCache;
	class Block;

	class BlockRenderer
	{
	public:
		BlockRenderer ( BlockCache & );
		~BlockRenderer ();

		void SetCamera ( Camera const & );
		void AddBlock ( Block const & );
		void DeleteBlock ( Block const & );

		void Render ();

	private:
		BlockCache * blockCache;

		Camera const * camera { nullptr };

		mpp::Shader shader;
		mpp::Buffer vertexBuffer;
		mpp::Buffer indexBuffer;
		mpp::VertexArray vertexArray;
		mpp::Texture texture;
		mpp::Texture outlineMask;

		std::vector <Block const *> blocks;
	};
}