#include "Application.hpp"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace mpp
{
	Application::Application ()
		: window ( "MinePP", { 1280, 720 } )
	{	
		window.MakeContextCurrent ();

		auto gladInitResult { gladLoadGL () };
		std::cout << "GLAD initialization " << ( gladInitResult ? "successful" : "failed" ) << std::endl;

		glEnable ( GL_DEBUG_OUTPUT );
		glDebugMessageCallback ( debugCallback, nullptr );
		
		glEnable ( GL_DEPTH_TEST );

		imguiContext = ImGui::CreateContext ();
		ImGui_ImplOpenGL3_Init ();
		window.InitImGuiForOpenGL ();

		world = std::make_unique <World> ( window );
	}
	
	Application::~Application ()
	{
	}

	void GLAPIENTRY Application::debugCallback ( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam )
	{
		std::cout << "OpenGL Debug Message: " << message << std::endl;
	}

	void Application::Run ()
	{
		while ( ! window.ShouldClose () )
		{
			glfwPollEvents ();

			world->Update ();

			glClearColor ( 0.529f, 0.808f, 0.922f, 1.0f );
			glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			world->Render ();

			ImGui_ImplGlfw_NewFrame ();
			ImGui_ImplOpenGL3_NewFrame ();

			ImGui::NewFrame ();
			ImGui::ShowMetricsWindow ();
			world->RenderGUI ();
			ImGui::EndFrame ();

			ImGui::Render ();
			ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData () );

			window.SwapBuffers ();
		}

		ImGui_ImplOpenGL3_Shutdown ();
		ImGui_ImplGlfw_Shutdown ();

		ImGui::DestroyContext ( imguiContext );

		glfwTerminate ();
	}
}