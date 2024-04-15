#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "opengl/Texture.hpp"

namespace mpp
{
	class BlockThumbnailRenderer;

	class BlockCache
	{
	public:
		BlockCache ( BlockThumbnailRenderer & );

		void InvalidateBlockThumbnails ();
		Texture const & GetBlockTexture ( std::string const & name );
		Texture const & GetBlockThumbnailTexture ( std::string const & name );

	private:
		BlockThumbnailRenderer * blockThumbnailRenderer;
		std::unordered_map <std::string, Texture> blockTextures;
		std::unordered_map <std::string, Texture> blockThumbnails;
	};
}