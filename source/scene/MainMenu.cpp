#include "MainMenu.hpp"

#include <memory>

#include "../Application.hpp"
#include "imgui.h"

#include "../Window.hpp"
#include "world/World.hpp"

namespace mpp
{
	MainMenu::MainMenu ( Application & application )
		: application ( &application )
	{
		application.GetWindow().SetRawInput (false);
	}

	void MainMenu::Render ()
	{
	}

	void MainMenu::RenderGUI ()
	{
		ImGui::ShowDemoWindow ();

		auto displaySize { ImGui::GetIO ().DisplaySize };
		ImVec2 size { displaySize.x * 0.5f, displaySize.y * 0.5f };

		ImGui::SetNextWindowSize ( size );
		ImGui::SetNextWindowPos ( { ( displaySize.x - size.x ) * 0.5f, ( displaySize.y - size.y ) * 0.5f } );
		
		ImGui::Begin ( "Main Menu", nullptr, ImGuiWindowFlags_NoDecoration );

		ImGui::Text ( "Welcome to Mine++" );
		
		ImGui::NewLine ();
		
		ImGui::Button ( "Create New World" );

		ImGui::SameLine ();

		if ( ImGui::Button ( "Enter Test World" ) )
			application->SetScene ( std::make_unique <World> ( *application ) );
		
		ImGui::SameLine ();
		
		if ( ImGui::Button ( "Quit" ) )
			application->Quit ();

		ImGui::End ();
	}

	void MainMenu::Update ( float delta )
	{

	}
}