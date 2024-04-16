#include "Application.hpp"

#include <iostream>
#include <map>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "scene/world/World.hpp"
#include "scene/MainMenu.hpp"

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

		scene = std::make_unique <World> ( *this );
	}
	
	Application::~Application ()
	{
	}

	void GLAPIENTRY Application::debugCallback ( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam )
	{
		if ( severity == GL_DEBUG_SEVERITY_NOTIFICATION )
			return;

		std::map<GLenum, std::string> sourceMap = {
				{GL_DEBUG_SOURCE_API, "API"},
				{GL_DEBUG_SOURCE_WINDOW_SYSTEM, "Window System"},
				{GL_DEBUG_SOURCE_SHADER_COMPILER, "Shader Compiler"},
				{GL_DEBUG_SOURCE_THIRD_PARTY, "Third Party"},
				{GL_DEBUG_SOURCE_APPLICATION, "Application"},
				{GL_DEBUG_SOURCE_OTHER, "Other"}
			};

			std::map<GLenum, std::string> typeMap = {
				{GL_DEBUG_TYPE_ERROR, "Error"},
				{GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "Deprecated Behavior"},
				{GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "Undefined Behavior"},
				{GL_DEBUG_TYPE_PORTABILITY, "Portability"},
				{GL_DEBUG_TYPE_PERFORMANCE, "Performance"},
				{GL_DEBUG_TYPE_MARKER, "Marker"},
				{GL_DEBUG_TYPE_PUSH_GROUP, "Push Group"},
				{GL_DEBUG_TYPE_POP_GROUP, "Pop Group"},
				{GL_DEBUG_TYPE_OTHER, "Other"}
			};

			std::map<GLenum, std::string> severityMap = {
				{GL_DEBUG_SEVERITY_HIGH, "High"},
				{GL_DEBUG_SEVERITY_MEDIUM, "Medium"},
				{GL_DEBUG_SEVERITY_LOW, "Low"},
				{GL_DEBUG_SEVERITY_NOTIFICATION, "Notification"}
			};

			std::cerr << "OpenGL debug message:"
					<< "\n    Source: " << sourceMap[source]
					<< "\n    Type: " << typeMap[type]
					<< "\n    Severity: " << severityMap[severity]
					<< "\n    ID: " << id
					<< "\n    Message: " << message << std::endl;
	}

	void Application::Run ()
	{
		lastFixedUpdateTime = std::chrono::steady_clock::now ();

		while ( ! window.ShouldClose () && ! quit )
		{
			auto now { std::chrono::steady_clock::now () };
			
			glfwPollEvents ();

			scene->Update ( ImGui::GetIO().DeltaTime );

			auto windowSize { window.GetSize () };
			glViewport ( 0, 0, windowSize.x, windowSize.y );

			//glClearColor ( 0.529f, 0.808f, 0.922f, 1.0f );
			glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
			glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			
			scene->Render ();

			ImGui_ImplGlfw_NewFrame ();
			ImGui_ImplOpenGL3_NewFrame ();

			ImGui::NewFrame ();
			scene->RenderGUI ();
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

	void Application::SetScene ( std::unique_ptr <Scene> scene )
	{
		this->scene = std::move ( scene );
	}
}
