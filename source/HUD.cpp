#include "HUD.hpp"

#include "gui/RectangleRenderer.hpp"

namespace mpp
{
	HUD::HUD ( RectangleRenderer & rectangleRenderer )
	{
		background.GetTransform ().SetScale ( { 100.0f, 100.0f, 1.0f } );
		rectangleRenderer.AddRectangle ( background );
	}

	void HUD::Render ()
	{
	}

	void HUD::RenderGUI ()
	{
	}
}