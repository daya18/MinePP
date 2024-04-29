#pragma once

namespace mpp
{
	struct Ray
	{
		glm::vec3 origin { 0.0f, 0.0f, 0.0f };
		glm::vec3 direction { 0.0f, 0.0f, 0.0f };
	};

	struct Box
	{
		glm::vec3 center;
		glm::vec3 size;
	};

	bool CheckRayIntersectBox ( Ray const & ray, Box const & box, glm::vec3 & normal, float & distance );
	bool CheckPointInBox ( glm::vec3 const & point, Box const & box );
}