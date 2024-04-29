#include "Block.hpp"

#include "../../opengl/Shader.hpp"
#include "../../opengl/Texture.hpp"

#include "../world/Chunk.hpp"
#include "../world/World.hpp"
#include "../world/WorldCache.hpp"
#include "../world/BlockCache.hpp"
#include "../../core/Utility.hpp"

namespace mpp
{
	Block::Block ( Chunk & chunk, std::string const & type, glm::vec3 const & position )
		: chunk ( & chunk ), type (type), position (position)
	{
		transform = CombineTransforms ( position, { 1.0f, 1.0f, 1.0f } );
	}
	
	void Block::Render () const
	{
		if ( type == "Air" )
			return;

		auto & worldCache { chunk->GetWorld ().GetCache () };

		worldCache.shader.SetUniform ( "u_sampler", 0 );
		worldCache.blockCache->GetBlockTexture ( type ).Bind ( 0 );
		
		worldCache.shader.SetUniform ( "u_modelMatrix", transform );

		worldCache.shader.SetUniform ( "u_useMask", highlighted );

		if ( highlighted )
		{
			worldCache.shader.SetUniform ( "u_maskSampler", 1 );
			worldCache.outlineMask.Bind ( 1 );
		}

		glDrawElements ( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0 );
	}

	bool Block::CheckRayIntersection ( Ray const & ray, glm::vec3 & faceNormal, float & distance ) const
	{
		if ( type == "Air" )
			return false;
		
		float sphereRadius { glm::length ( glm::vec3 { 1.0f, 1.0f, 1.0f } ) };
		float sphereIntersectDistance;
		if ( ! glm::intersectRaySphere ( ray.origin, ray.direction, position, sphereRadius * sphereRadius, sphereIntersectDistance ) )
			return false;

		if ( glm::distance ( ray.origin, position ) > glm::length ( ray.direction ) )
			return false;

		return CheckRayIntersectBox ( ray, { position, { 1.0f, 1.0f, 1.0f } }, faceNormal, distance );
	}
}