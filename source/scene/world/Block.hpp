#pragma once

#include "../Transform.hpp"

namespace mpp
{
	class Block
	{
	public:
		Block ( std::string const & type, glm::vec3 const & position );

		Transform const & GetTransform () const;
		Transform & GetTransform ();
		std::string const & GetType () const;
		bool GetHighlighted () const;
		void SetHighlighted ( bool );

	private:
		std::string type;
		Transform transform;
		bool highlighted { false };
	};



	// Implementation
	inline Transform const & Block::GetTransform () const { return transform; }
	inline Transform & Block::GetTransform () { return transform; }
	inline std::string const & Block::GetType () const { return type; }
	inline bool Block::GetHighlighted () const { return highlighted; }
	inline void Block::SetHighlighted ( bool highlighted ) { this->highlighted = highlighted; }
}