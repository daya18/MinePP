#include "World.hpp"

#include <iostream>

#include "imgui.h"

#include "Window.hpp"

namespace mpp
{
	World::World ( Window & window )
		:
		camera ( window, { 0.0f, 0.0f, 5.0f } ),
		blockRenderer ( ),
		rectangleRenderer ( window ),
		inventoryHud ( rectangleRenderer )
	{
		blockRenderer.SetCamera ( camera );

		CreateBlock ( "Grass", { 0, 0, 0 } );
		CreateBlock ( "Grass", { 2, 0, 0 } );

		window.AddButtonCallback ( [ this ] ( int button, int action ) 
		{ 
			if ( action == GLFW_PRESS )
			{
				if ( button == GLFW_MOUSE_BUTTON_LEFT )
				{
					DestroyBlock ( selectedBlock );
					selectedBlock = nullptr;
				}

				if ( button == GLFW_MOUSE_BUTTON_RIGHT )
				{
					if ( selectedBlock )
					{
						auto position { selectedBlock->GetTransform ().GetPosition () };
						position += directionVectors.at ( selectedBlockFaceDirection ) * 2.0f;
						CreateBlock ( "Grass", position );
					}
				}
			}
		} );
	}
	
	void World::CreateBlock ( std::string const & type, glm::vec3 const & position )
	{
		blocks.push_back ( { type, position } );
		blockRenderer.AddBlock ( blocks.back () );
		blockRayCaster.AddBlock ( blocks.back () );
	}

	void World::DestroyBlock ( Block * block )
	{
		blockRenderer.DeleteBlock ( *block );
		blockRayCaster.DeleteBlock ( *block );
		
		for ( auto it { blocks.begin () }; it != blocks.end (); ++it )
		{
			if ( &*it == block )
			{
				blocks.erase ( it );
				break;
			}
		}
	}

	void World::Update ()
	{
		camera.Update ();

		auto intersection { blockRayCaster.CheckRayIntersection ( 
			{ camera.GetPosition (), glm::normalize ( camera.GetLookDirection () ) } ) };
		
		if ( intersection.intersects )
		{
			SelectBlock ( const_cast < Block * > ( intersection.block ) );
			selectedBlockFaceDirection = intersection.faceDirection;
		}
		else
			SelectBlock ( nullptr );
	}

	void World::Render ()
	{
		blockRenderer.Render ();
		rectangleRenderer.Render ();
	}

	void World::RenderGUI ()
	{
		float aspectRatio { ImGui::GetIO ().DisplaySize.x / ImGui::GetIO ().DisplaySize.y };
		ImVec2 center { ImGui::GetIO ().DisplaySize.x * 0.5f, ImGui::GetIO ().DisplaySize.y * 0.5f };
		
		ImVec2 crosshairSize { 30.0f, 30.0f };

		ImGui::PushStyleVar ( ImGuiStyleVar_WindowPadding, { 0, 0 } );
		ImGui::SetNextWindowSize ( { crosshairSize.x, crosshairSize.y } );
		ImGui::SetNextWindowPos ( { center.x - crosshairSize.x * 0.5f, center.y - crosshairSize.y * 0.5f } );
		ImGui::Begin ( "Crosshair", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground );
		auto drawList { ImGui::GetWindowDrawList () };
		drawList->AddLine ( { center.x - crosshairSize.x * 0.5f, center.y }, { center.x + crosshairSize.x * 0.5f, center.y }, IM_COL32_WHITE, 3.0f );
		drawList->AddLine ( { center.x, center.y - crosshairSize.y * 0.5f }, { center.x, center.y + crosshairSize.y * 0.5f }, IM_COL32_WHITE, 3.0f );
		ImGui::End ();
		ImGui::PopStyleVar ();
	}

	void World::SelectBlock ( Block * block )
	{
		if ( selectedBlock == block )
			return;

		if ( selectedBlock != nullptr )
		{
			selectedBlock->SetHighlighted ( false );
			selectedBlock = nullptr;
		}

		selectedBlock = block;

		if ( selectedBlock != nullptr )
			selectedBlock->SetHighlighted ( true );
	}

}