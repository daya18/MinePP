#include "Block.hpp"

namespace mpp
{
	Block::Block ( std::string const & type, glm::vec3 const & position )
		: position ( position ), transform ( glm::translate ( glm::identity <glm::mat4> (), position ) )
	{
	}
}