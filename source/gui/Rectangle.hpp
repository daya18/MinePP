#pragma once

#include "../Transform.hpp"

namespace mpp
{
	class Rectangle
	{
	public:
		Transform const & GetTransform () const;
		Transform & GetTransform ();

	private:
		Transform transform;
	};



	// Implementation
	inline Transform const & Rectangle::GetTransform () const { return transform; }
	inline Transform & Rectangle::GetTransform () { return transform; }

}