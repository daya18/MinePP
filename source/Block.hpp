#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mpp
{
	class Block
	{
	public:
		Block ( std::string const & type, glm::vec3 const & position );

		glm::mat4 const & GetTransformMatrix () const;

	private:
		std::string type;
		glm::mat4 transform { glm::identity <glm::mat4> () };
	};



	// Implementation
	inline glm::mat4 const & Block::GetTransformMatrix () const { return transform; }
}