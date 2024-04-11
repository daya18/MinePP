#pragma once

#include <glm/glm.hpp>

namespace mpp
{
	namespace DirectionVectors
	{
		constexpr glm::vec3 up { 0.0f, 1.0f, 0.0f };
		constexpr glm::vec3 down { 0.0f, -1.0f, 0.0f };
		constexpr glm::vec3 left { -1.0f, 0.0f, 0.0f };
		constexpr glm::vec3 right { 1.0f, 0.0f, 0.0f };
		constexpr glm::vec3 forward { 0.0f, 0.0f, 1.0f };
		constexpr glm::vec3 back { 0.0f, 0.0f, -1.0f };
	}

	enum class Directions { up, down, left, right, forward, back };
}