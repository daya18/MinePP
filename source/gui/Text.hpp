#pragma once

#include "../scene/Transform.hpp"

namespace mpp
{
	class Text
	{
	public:
		Transform const & GetTransform () const;
		Transform & GetTransform ();

		void SetText ( std::string const & );
		std::string const & GetText () const;

	private:
		Transform transform;
		std::string text;
	};
	


	// Implementation
	inline Transform const & Text::GetTransform () const { return transform; }
	inline Transform & Text::GetTransform () { return transform; }
	inline void Text::SetText ( std::string const & text ) { this->text = text; }
	inline std::string const & Text::GetText () const { return text; }
}