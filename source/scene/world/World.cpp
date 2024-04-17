#include "World.hpp"

#include "../../Application.hpp"
#include "../../Window.hpp"

namespace mpp
{
	World::World ( Application & application )
	:
		application ( &application ),
		window ( & application.GetWindow () ),
		camera ( *window, *this, { 0.0f, 0.0f, 5.0f } ),
		blockRenderer ( blockCache ),
		blockCache ( blockThumbnailRenderer ),
		rectangleRenderer ( *window ),
		playerInventory ( 20 ),
		inventoryHud ( blockCache, rectangleRenderer, *window, playerInventory )
	{
		blockRenderer.SetCamera ( camera );

		CreateBlock ( "Grass", { 0, 0, 0 } );
		CreateBlock ( "Grass", { 2, 0, 0 } );

		window->AddButtonCallback ( [this] ( int button, int action ) { OnButtonAction ( button, action ); } );
		window->AddKeyCallback ( [ this ] ( int key, int action ) { OnKeyAction ( key, action ); } );

		playerInventory.GetSlot ( 0 ).SetStack ( { "Grass", 1 } );
		playerInventory.GetSlot ( 1 ).SetStack ( { "Stone", 1 } );
		playerInventory.GetSlot ( 2 ).SetStack ( { "Log", 1 } );

		inventoryHud.Update ();

		SetPaused ( false );
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

	void World::Update ( float delta )
	{
		if ( paused )
			return;

		camera.Update ( delta );

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
		RenderCrosshair ();

		if ( ImGui::Begin ( "Statistics" ) )
		{
			ImGui::Text ( "FPS: %f", ImGui::GetIO ().Framerate );
			ImGui::Text ( "Frame Time: %f", ImGui::GetIO ().DeltaTime * 1000.0f );
			ImGui::End ();
		}

		if ( paused )
		{
			auto displaySize { ImGui::GetIO ().DisplaySize };
			ImVec2 size { displaySize.x * 0.2f, displaySize.y * 0.5f };

			ImGui::SetNextWindowSize ( size );
			ImGui::SetNextWindowPos ( { ( displaySize.x - size.x ) * 0.5f, ( displaySize.y - size.y ) * 0.5f } );

			ImGui::Begin ( "Pause Menu" );
			
			if ( ImGui::Button ( "Quit" ) )
				application->Quit ();
			
			ImGui::End ();
		}

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

	void World::SetPaused ( bool paused )
	{
		this->paused = paused;
		window->SetRawInput ( ! paused );
	}

	void World::OnKeyAction ( int key, int action )
	{
		if ( action == GLFW_PRESS )
		{
			if ( key == GLFW_KEY_ESCAPE )
			{
				SetPaused ( ! paused );
			}
		}
	}

	void World::OnButtonAction ( int button, int action )
	{
		if ( action == GLFW_PRESS )
		{
			if ( ! paused )
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

						int selectedSlotIndex { inventoryHud.GetSelectedItemSlot () };
						auto const & selectedSlot { playerInventory.GetSlot ( selectedSlotIndex ) };

						if ( selectedSlot.HasStack () )
							CreateBlock ( selectedSlot.GetStack ().GetItemType (), position );
					}
				}
			}
		}
	}

	void World::RenderCrosshair ()
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

}