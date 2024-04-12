#pragma once

#include <unordered_map>
#include <string>
#include <array>

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

	constexpr std::array <Directions, 6> directions 
	{ Directions::up, Directions::down, Directions::left, Directions::right, Directions::forward, Directions::back };

	inline const std::unordered_map <Directions, std::string> directionStrings
	{
		{ Directions::up, "Up" },
		{ Directions::down, "Down" },
		{ Directions::left, "Left" },
		{ Directions::right, "Right" },
		{ Directions::forward, "Forward" },
		{ Directions::back, "Back" },
	};
}