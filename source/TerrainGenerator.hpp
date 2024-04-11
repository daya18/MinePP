#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace mpp
{
	class TerrainGenerator
	{
	public:
		std::vector <glm::vec3> Generate ();
	};
}