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

		std::string const & GetType () const;
		bool GetHighlighted () const;
		
		void SetType ( std::string const & );
		void SetHighlighted ( bool );
		bool CheckRayIntersection ( Ray const & ray, glm::vec3 & normal, float & distance ) const;
		void Render () const;
		void SetChunk ( Chunk & );
		Chunk & GetChunk ();
		glm::vec3 const & GetPosition () const;
		glm::mat4 const & GetTransform () const;

	private:
		Chunk * chunk;
		std::string type;
		glm::vec3 position;
		glm::mat4 transform;
		bool highlighted { false };
	};



	// Implementation
	inline glm::mat4 const & Block::GetTransform () const { return transform; }
	inline std::string const & Block::GetType () const { return type; }
	inline bool Block::GetHighlighted () const { return highlighted; }
	inline void Block::SetHighlighted ( bool highlighted ) { this->highlighted = highlighted; }
	inline void Block::SetChunk ( Chunk & chunk ) { this->chunk = &chunk; }
	inline void Block::SetType ( std::string const & type ) { this->type = type; }
	inline glm::vec3 const & Block::GetPosition () const { return position; }
	inline Chunk & Block::GetChunk () { return *chunk; }
}