#pragma once

#include "Camera.hpp"
#include "WorldRenderer.hpp"

namespace mpp
{
	class Window;

	class World
	{
	public:
		World ( Window &, BlockTypeRegistry const &, BlockModel const & );

		void Update ();
		void Render ();

	private:

		Camera camera;
		WorldRenderer worldRenderer;
	};
}