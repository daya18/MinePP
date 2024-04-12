#include "World.hpp"

#include <iostream>

#include "Window.hpp"

namespace mpp
{
	World::World ( Window & window, BlockTypeRegistry const & blockRegistry, BlockModel const & blockModel )
	:
		camera ( window, { 0.0f, 0.0f, 5.0f } ),
		blockRenderer ( blockRegistry, blockModel )
	{
		blockRenderer.SetCamera ( camera );

		CreateBlock ( "Grass", { 0, 0, 0 } );
		CreateBlock ( "Grass", { 2, 0, 0 } );
	}
	
	void World::CreateBlock ( std::string const & type, glm::vec3 const & position )
	{
		blocks.push_back ( { type, position } );
		blockRenderer.AddBlock ( blocks.back () );
		blockRayCaster.AddBlock ( blocks.back () );

		std::cout << & blocks.back () << std::endl;
	}

	void World::Update ()
	{
		camera.Update ();

		auto intersection { blockRayCaster.CheckRayIntersection ( { camera.GetPosition (), glm::normalize ( camera.GetLookDirection () ) } ) };
	}

	void World::Render ()
	{
		blockRenderer.Render ();
	}
}