#pragma once

#include "Block.hpp"
#include "../../core/Ray.hpp"
#include "../../core/Constants.hpp"
#include "../../opengl/Buffer.hpp"
#include "Batch.hpp"

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
		
		void Update ();
		void Render ( Camera const & );
		bool CheckRayIntersection ( Ray const & ray, Block const * & block, glm::vec3 & normal, float & distance );
		
		Block * GetBlock ( glm::vec3 const & position );
		World & GetWorld ();
		inline static glm::vec3 const & GetSize ();

	private:
		static glm::vec3 const size;

		void UpdateBatches ();

		World * world;
		glm::vec3 position;
		std::unordered_map <glm::vec3, Block> blocks;
		std::unordered_map <std::string, Batch> batches;
	};

	inline World & Chunk::GetWorld () { return *world; }
	inline glm::vec3 const & Chunk::GetSize () { return size; }
}