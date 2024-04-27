#pragma once

#include "../Transform.hpp"
#include "../../core/Ray.hpp"
#include "../../core/Constants.hpp"

namespace mpp
{
	class Chunk;

	class Block
	{
	public:
		Block ( Chunk &, std::string const & type, glm::vec3 const & position );

		Transform const & GetTransform () const;
		Transform & GetTransform ();
		std::string const & GetType () const;
		bool GetHighlighted () const;
		
		void SetType ( std::string const & );
		void SetHighlighted ( bool );
		bool CheckRayIntersection ( Ray const & ray, Directions & faceDirection, float & distance ) const;
		void Render () const;
		void SetChunk ( Chunk & );

	private:
		Chunk * chunk;
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
	inline void Block::SetChunk ( Chunk & chunk ) { this->chunk = &chunk; }
	inline void Block::SetType ( std::string const & type ) { this->type = type; }
}