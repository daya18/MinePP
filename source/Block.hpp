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
		glm::vec3 const & GetPosition () const;
		std::string const & GetType () const;
		bool GetHighlighted () const;
		void SetHighlighted ( bool );

	private:
		std::string type;
		glm::vec3 position;
		glm::mat4 transform { glm::identity <glm::mat4> () };
		bool highlighted { false };
	};



	// Implementation
	inline glm::mat4 const & Block::GetTransformMatrix () const { return transform; }
	inline glm::vec3 const & Block::GetPosition () const { return position; }
	inline std::string const & Block::GetType () const { return type; }
	inline bool Block::GetHighlighted () const { return highlighted; }
	inline void Block::SetHighlighted ( bool highlighted ) { this->highlighted = highlighted; }
}