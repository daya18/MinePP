#pragma once

#include "gui/Rectangle.hpp"

namespace mpp
{
	class RectangleRenderer;

	class HUD
	{
	public:
		HUD ( RectangleRenderer & );

		void Render ();
		void RenderGUI ();

	private:
		Rectangle background;
	};
}