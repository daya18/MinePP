#include "World.hpp"

#include "Window.hpp"

namespace mpp
{
	World::World ( Window & window, BlockTypeRegistry const & blockRegistry, BlockModel const & blockModel )
	:
		camera ( window, { 0.0f, 0.0f, 5.0f } ),
		worldRenderer ( blockRegistry, blockModel )
	{
		worldRenderer.SetCamera ( camera );
	}

	void World::Update ()
	{
		camera.Update ();
	}

	void World::Render ()
	{
		worldRenderer.Render ();
	}
}