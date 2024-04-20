#pragma once

#include "../scene/Transform.hpp"

namespace mpp
{
	struct Text
	{
		Transform transform;
		std::string text {};
		glm::vec4 color { 1.0f, 1.0f, 0.0f, 1.0f };
		glm::vec2 origin { 0.0f, 0.0f };
	};
}