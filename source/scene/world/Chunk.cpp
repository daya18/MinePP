#include "Chunk.hpp"

#include "WorldCache.hpp"
#include "Camera.hpp"
#include "BlockCache.hpp"
#include "World.hpp"

namespace mpp
{
	glm::vec3 const Chunk::size { 5.0f, 10.0f, 5.0f };

	Chunk::Chunk ( World & world, glm::vec3 const & position )
	: 
		world ( & world )
	{
		//blocks.emplace ( position, Block { *this, "Grass", position } );

		glm::vec3 chunkBegin { position - size * 0.5f };
		glm::vec3 chunkEnd { position + size * 0.5f };

		for ( float x { chunkBegin.x }; x < chunkEnd.x; ++x )
		{
			for ( float y { chunkBegin.y }; y < chunkEnd.y; ++y )
			{
				for ( float z { chunkBegin.z }; z < chunkEnd.z; ++z )
				{
					glm::vec3 position { x, y, z };
					position *= 2.0f;
					blocks.emplace ( position, Block { *this, "Grass", position } );
				}
			}
		}
	}
	
	Chunk::~Chunk ()
	{
	}
	
	Chunk::Chunk ( Chunk && r )
	{
		*this = std::move ( r );
	}

	Chunk & Chunk::operator = ( Chunk && r )
	{
		world = r.world;
		blocks = std::move ( r.blocks );

		for ( auto & [ position, block ]: blocks )
			block.SetChunk ( *this );
		
		return *this;
	}

	Block * Chunk::GetBlock ( glm::vec3 const & position )
	{
		auto blockIt { blocks.find ( position ) };
		return blockIt == blocks.end () ? nullptr : & blockIt->second;
	}
	
	void Chunk::Render ( Camera const & camera )
	{
		auto & worldCache { world->GetCache () };
		
		glEnable ( GL_CULL_FACE );

		worldCache.shader.Bind ();

		worldCache.vertexArray.Bind ();
		worldCache.indexBuffer.Bind ( GL_ELEMENT_ARRAY_BUFFER );

		worldCache.shader.SetUniform ( "u_viewMatrix", camera.GetViewMatrix () );
		worldCache.shader.SetUniform ( "u_projectionMatrix", camera.GetProjectionMatrix () );

		worldCache.shader.SetUniform ( "u_sampler", 0 );

		for ( auto const & [ position, block ]: blocks )
			block.Render ();

		glDisable ( GL_CULL_FACE );
	}

	bool Chunk::CheckRayIntersection ( Ray const & ray, Block const * & block, Directions & faceDirection, float & distance )
	{
		struct BlockIntersection
		{
			Block const * block;
			Directions faceDirection;
			float distance;
		};

		std::vector <BlockIntersection> blockIntersections;

		for ( auto const & [ position, block ]: blocks )
		{
			Directions faceDirection; float distance;
			auto intersects { block.CheckRayIntersection ( ray, faceDirection, distance ) };
			
			if ( intersects )
				blockIntersections.push_back ( { &block, faceDirection, distance } );
		}

		block = nullptr; 
		faceDirection = Directions::down; 
		distance = std::numeric_limits <float>::infinity ();

		for ( auto const & blockIntersection : blockIntersections )
		{
			if ( blockIntersection.distance < distance )
			{
				block = blockIntersection.block;
				faceDirection = blockIntersection.faceDirection;
				distance = blockIntersection.distance;
			}
		}

		return ! blockIntersections.empty ();
	}
}