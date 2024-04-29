#include "Chunk.hpp"

#include "WorldCache.hpp"
#include "Camera.hpp"
#include "BlockCache.hpp"
#include "World.hpp"
#include "../../core/Utility.hpp"

namespace mpp
{
	glm::vec3 const Chunk::size { 5.0f, 10.0f, 5.0f };

	Chunk::Chunk ( World & world, glm::vec3 const & position )
	: 
		world ( & world ),
		position ( position )
	{
		glm::vec3 chunkBegin { position - size * 0.5f };
		glm::vec3 chunkEnd { position + size * 0.5f };

		for ( float x { chunkBegin.x }; x < chunkEnd.x; ++x )
		{
			for ( float y { chunkBegin.y }; y < chunkEnd.y; ++y )
			{
				for ( float z { chunkBegin.z }; z < chunkEnd.z; ++z )
				{
					glm::vec3 position { x, y, z };
					blocks.emplace ( position, Block { *this, "Grass", position } );
				}
			}
		}

		UpdateBatches ();
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
		position = std::move ( r.position );
		batches = std::move ( r.batches );

		for ( auto & [ position, block ]: blocks )
			block.SetChunk ( *this );
		
		return *this;
	}

	Block * Chunk::GetBlock ( glm::vec3 const & position )
	{
		auto blockIt { blocks.find ( position ) };
		return blockIt == blocks.end () ? nullptr : & blockIt->second;
	}
	
	void Chunk::Update ()
	{
		UpdateBatches ();
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
		
		for ( auto & [type, batch] : batches )
			batch.Render ( worldCache.shader );

		glDisable ( GL_CULL_FACE );
	}

	bool Chunk::CheckRayIntersection ( Ray const & ray, Block const * & block, glm::vec3 & normal, float & distance )
	{
		auto rayEnd { ray.origin + ray.direction };
		
		if ( ! CheckPointInBox ( rayEnd, { position, size } ) )
			return false;

		struct BlockIntersection
		{
			Block const * block;
			glm::vec3 faceNormal;
			float distance;
		};

		std::vector <BlockIntersection> blockIntersections;

		for ( auto const & [ position, block ]: blocks )
		{
			BlockIntersection intersection { &block };
			auto intersects { block.CheckRayIntersection ( ray, intersection.faceNormal, intersection.distance ) };
			if ( intersects ) blockIntersections.push_back ( intersection );
		}

		block = nullptr; 
		normal = glm::zero <glm::vec3> (); 
		distance = std::numeric_limits <float>::infinity ();

		for ( auto const & blockIntersection : blockIntersections )
		{
			if ( blockIntersection.distance < distance )
			{
				block = blockIntersection.block;
				normal = blockIntersection.faceNormal;
				distance = blockIntersection.distance;
			}
		}

		return ! blockIntersections.empty ();
	}

	void Chunk::UpdateBatches ()
	{	
		std::unordered_map <std::string, std::vector <Block *> > typeBlocks;

		for ( auto & [position, block] : blocks )
		{
			if ( block.GetType () == "Air" )
				continue;

			typeBlocks [ block.GetType () ].push_back ( &block );
		}

		batches.clear ();
		
		for ( auto const & [type, blocks] : typeBlocks )
			batches.emplace ( type, Batch { world->GetCache ().blockCache->GetBlockTexture ( type ), blocks } );
	}
}