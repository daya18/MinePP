#include "BlockRayCaster.hpp"

#include "Block.hpp"

namespace mpp
{
	std::array <glm::vec3, 8> const BlockRayCaster::blockVertices
	{
		// Front plane ( Z+ )
		glm::vec3 { -1.0f, -1.0f, 1.0f }, // 0
		glm::vec3 { -1.0f,  1.0f, 1.0f }, // 1
		glm::vec3 {  1.0f,  1.0f, 1.0f }, // 2
		glm::vec3 {  1.0f, -1.0f, 1.0f }, // 3

		// Back plane ( Z- )
		glm::vec3 { -1.0f, -1.0f, -1.0f }, // 4
		glm::vec3 { -1.0f,  1.0f, -1.0f }, // 5
		glm::vec3 {  1.0f,  1.0f, -1.0f }, // 6
		glm::vec3 {  1.0f, -1.0f, -1.0f }, // 7
	};

	std::unordered_map <Directions, std::array < std::array <uint32_t, 3>, 2 > > BlockRayCaster::blockIndices
	{
		{ Directions::forward,	{ std::array <uint32_t, 3> { 0, 1, 2 }, std::array <uint32_t, 3> { 2, 3, 0 } } },
		{ Directions::back,		{ std::array <uint32_t, 3> { 4, 5, 6 }, std::array <uint32_t, 3> { 6, 7, 4 } } },
		{ Directions::left,		{ std::array <uint32_t, 3> { 0, 1, 5 }, std::array <uint32_t, 3> { 5, 4, 0 } } },
		{ Directions::right,	{ std::array <uint32_t, 3> { 6, 7, 3 }, std::array <uint32_t, 3> { 3, 2, 6 } } },
		{ Directions::up,		{ std::array <uint32_t, 3> { 1, 5, 6 }, std::array <uint32_t, 3> { 6, 2, 1 } } },
		{ Directions::down,		{ std::array <uint32_t, 3> { 4, 0, 3 }, std::array <uint32_t, 3> { 3, 7, 4 } } },
	};

	BlockRayCaster::BlockRayCaster ()
	{
	}

	void BlockRayCaster::AddBlock ( Block const & block )
	{
		BlockData data { blockVertices };
		

		// TO DO: Make this a method in a dedicated transform class

		for ( auto & blockVertex : data.vertices )
			blockVertex = block.GetTransform().GetMatrix () * glm::vec4 ( blockVertex, 1.0f );

		blockDatas.emplace ( &block, data );
	}

	void BlockRayCaster::DeleteBlock ( Block const & block )
	{
		blockDatas.erase ( &block );
	}

	RayIntersection BlockRayCaster::CheckRayIntersection ( Ray const & ray )
	{
		struct BlockIntersection
		{
			Block const * block;
			Directions faceDirection;
			float distance;
		};

		std::vector <BlockIntersection> blockIntersections;
		
		for ( auto const & [ block, blockData ] : blockDatas )
		{
			struct FaceIntersection
			{
				Directions direction;
				float distance;
			};

			std::vector <FaceIntersection> faceIntersections;

			for ( auto const & [ faceDirection, faceTriangleIndices ] : blockIndices )
			{
				bool intersects { false };
				float distance { 0.0f };

				for ( auto const & triangleIndices : faceTriangleIndices )
				{
					glm::vec2 baryPosition;

					 intersects = glm::intersectRayTriangle ( ray.origin, ray.direction,
						blockData.vertices [ triangleIndices [ 0 ] ],
						blockData.vertices [ triangleIndices [ 1 ] ],
						blockData.vertices [ triangleIndices [ 2 ] ],
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
				BlockIntersection blockIntersection { block, Directions::down, { std::numeric_limits <float>::infinity () } };

				for ( auto const & faceIntersection : faceIntersections )
				{
					if ( faceIntersection.distance < blockIntersection.distance )
					{
						blockIntersection.faceDirection = faceIntersection.direction;
						blockIntersection.distance = faceIntersection.distance;
					}
				}

				blockIntersections.push_back ( blockIntersection );
			}
		}

		RayIntersection intersection { ! blockIntersections.empty (), nullptr, Directions::down, std::numeric_limits <float>::infinity () };

		for ( auto const & blockIntersection : blockIntersections )
		{
			if ( blockIntersection.distance < intersection.distance )
			{
				intersection.block = blockIntersection.block;
				intersection.faceDirection = blockIntersection.faceDirection;
				intersection.distance = blockIntersection.distance;
			}
		}

		return intersection;
	}
}