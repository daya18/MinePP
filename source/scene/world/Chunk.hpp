#pragma once

#include "Block.hpp"
#include "../../core/Ray.hpp"
#include "../../core/Constants.hpp"

namespace mpp
{
	class World;
	class Camera;

	class Chunk
	{
	public:
		Chunk ( World & world, glm::vec3 const & position );
		~Chunk ();
		
		Chunk ( Chunk const & ) = delete;
		Chunk ( Chunk && );

		Chunk & operator = ( Chunk const & ) = delete;
		Chunk & operator = ( Chunk && );

		Block * GetBlock ( glm::vec3 const & position );
		void Render ( Camera const & );
		bool CheckRayIntersection ( Ray const & ray, Block const * & block, Directions & faceDirection, float & distance );
		World & GetWorld ();
		inline static glm::vec3 const & GetSize ();

	private:
		static glm::vec3 const size;

		World * world;
		std::unordered_map <glm::vec3, Block> blocks;
	};

	inline World & Chunk::GetWorld () { return *world; }
	inline glm::vec3 const & Chunk::GetSize () { return size; }
}