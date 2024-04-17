#include "BlockCache.hpp"

#include "../../gui/BlockThumbnailRenderer.hpp"

namespace mpp
{
	BlockCache::BlockCache ( BlockThumbnailRenderer & blockThumbnailRenderer )
		: blockThumbnailRenderer ( &blockThumbnailRenderer )
	{
	}
	
	Texture const & BlockCache::GetBlockTexture ( std::string const & name )
	{
		auto blockTextureIt { blockTextures.find ( name ) };

		if ( blockTextureIt == blockTextures.end () )
		{
			auto path { std::string { "image/block/" } + name + ".png" };
			blockTextureIt = blockTextures.emplace ( name, Texture { path } ).first;
		}

		return blockTextureIt->second;
	}

	Texture const & BlockCache::GetBlockThumbnailTexture ( std::string const & name )
	{
		auto blockThumbnailIt { blockThumbnails.find ( name ) };

		if ( blockThumbnailIt == blockThumbnails.end () )
		{
			auto blockTexture { GetBlockTexture ( name ) };
			blockThumbnailIt = blockThumbnails.emplace ( name, Texture { glm::vec2 { 100, 100 } } ).first;
			blockThumbnailRenderer->Render ( blockTexture, blockThumbnailIt->second );

			// TO DO: File backed caching
		}

		return blockThumbnailIt->second;
	}

	void InvalidateBlockThumbnails ()
	{

	}
}