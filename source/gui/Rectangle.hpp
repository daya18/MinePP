#pragma once

#include <string>
#include <glm/glm.hpp>

#include "../Transform.hpp"

namespace mpp
{
	class Texture;

	class Rectangle
	{
	public:
		Transform const & GetTransform () const;
		Transform & GetTransform ();

		void SetColor ( glm::vec4 const & );
		void SetTexture ( Texture const * );

		glm::vec4 const & GetColor () const;
		Texture const * GetTexture () const;

	private:
		glm::vec4 color { glm::one <glm::vec4> () };
		Texture const * texture { nullptr };
		Transform transform;
	};



	// Implementation
	inline Transform const & Rectangle::GetTransform () const { return transform; }
	inline Transform & Rectangle::GetTransform () { return transform; }
	inline void Rectangle::SetColor ( glm::vec4 const & color ) { this->color = color; }
	inline void Rectangle::SetTexture ( Texture const * texture ) { this->texture = texture; }
	inline glm::vec4 const & Rectangle::GetColor () const { return color; }
	inline Texture const * Rectangle::GetTexture () const { return texture; }
}