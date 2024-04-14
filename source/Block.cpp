#include "Block.hpp"

namespace mpp
{
	Block::Block ( std::string const & type, glm::vec3 const & position )
		: transform ( position )
	{
	}
}