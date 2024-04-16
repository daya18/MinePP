#pragma once

#include "../../Constants.hpp"

#include <glm/glm.hpp>

namespace mpp
{
	class Block;
	class BlockModel;

	struct Ray
	{
		glm::vec3 origin { 0.0f, 0.0f, 0.0f };
		glm::vec3 direction { 0.0f, 0.0f, 0.0f };
	};

	struct RayIntersection
	{
		bool intersects				{ false };
		Block const * block			{ nullptr };
		Directions faceDirection	{ Directions::down };
		float distance				{ 0.0f };
	};

	class BlockRayCaster
	{
	public:
		BlockRayCaster ();

		void AddBlock ( Block const & );
		void DeleteBlock ( Block const & );

		RayIntersection CheckRayIntersection ( Ray const & ray );

	private:
		struct BlockData
		{
			std::array <glm::vec3, 8> vertices;
		};

		static std::array <glm::vec3, 8> const blockVertices;
		static std::unordered_map <Directions, std::array < std::array <uint32_t, 3>, 2 > > blockIndices;

		std::unordered_map <Block const *, BlockData> blockDatas;
	};
}