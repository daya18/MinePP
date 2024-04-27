#include "Block.hpp"

#include "../../opengl/Shader.hpp"
#include "../../opengl/Texture.hpp"

#include "../world/Chunk.hpp"
#include "../world/World.hpp"
#include "../world/WorldCache.hpp"
#include "../world/BlockCache.hpp"

namespace mpp
{
	Block::Block ( Chunk & chunk, std::string const & type, glm::vec3 const & position )
		: chunk ( & chunk ), type (type), transform (position)
	{
	}
	
	void Block::Render () const
	{
		if ( type == "Air" )
			return;

		auto & worldCache { chunk->GetWorld ().GetCache () };

		worldCache.shader.SetUniform ( "u_modelMatrix", transform.GetMatrix () );

		worldCache.blockCache->GetBlockTexture ( type ).Bind ( 0 );

		worldCache.shader.SetUniform ( "u_useMask", highlighted );

		if ( highlighted )
		{
			worldCache.shader.SetUniform ( "u_maskSampler", 1 );
			worldCache.outlineMask.Bind ( 1 );
		}

		glDrawElements ( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
	}

	bool Block::CheckRayIntersection ( Ray const & ray, Directions & faceDirection, float & distance ) const
	{
		if ( type == "Air" )
			return false;
		
		auto & worldCache { chunk->GetWorld ().GetCache () };

		struct FaceIntersection
		{
			Directions direction;
			float distance;
		};

		std::vector <FaceIntersection> faceIntersections;

		for ( auto const & [faceDirection, faceTriangleIndices] : worldCache.blockIndices )
		{
			bool intersects { false };
			float distance { 0.0f };

			for ( auto const & triangleIndices : faceTriangleIndices )
			{
				glm::vec2 baryPosition;

				intersects = glm::intersectRayTriangle ( ray.origin, ray.direction,
					glm::vec3 { transform.GetMatrix () * glm::vec4 { worldCache.blockVertices [ triangleIndices [ 0 ] ], 1.0f } },
					glm::vec3 { transform.GetMatrix () * glm::vec4 { worldCache.blockVertices [ triangleIndices [ 1 ] ], 1.0f } },
					glm::vec3 { transform.GetMatrix () * glm::vec4 { worldCache.blockVertices [ triangleIndices [ 2 ] ], 1.0f } },
					baryPosition,
					distance
				);

				if ( intersects )
					break;
			}

			if ( intersects )
				faceIntersections.push_back ( { faceDirection, distance } );
		}

		if ( ! faceIntersections.empty () )
		{
			faceDirection = Directions::down;
			distance = std::numeric_limits <float>::infinity ();

			for ( auto const & faceIntersection : faceIntersections )
			{
				if ( faceIntersection.distance < distance )
				{
					faceDirection = faceIntersection.direction;
					distance = faceIntersection.distance;
				}
			}
		}

		return ! faceIntersections.empty ();
	}
}