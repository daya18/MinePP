#include "Utility.hpp"

namespace mpp
{
	glm::mat4 CombineTransforms ( glm::vec3 const & translation, glm::vec3 const & scale )
	{
		static constexpr glm::mat4 identityMatrix { glm::identity <glm::mat4> () };

		glm::mat4 translationMatrix { glm::translate ( identityMatrix, translation ) };
		glm::mat4 scaleMatrix { glm::scale ( identityMatrix, scale ) };

		return translationMatrix * scaleMatrix;
	}
}