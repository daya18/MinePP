#pragma once 

#include "Window.hpp"
#include "scene/Scene.hpp"

namespace mpp
{
	class Application
	{
	public:
		Application ();
		~Application ();

		void Run ();
		
		Window & GetWindow ();

		void Quit ();
		void SetScene ( std::unique_ptr <Scene> );

	private:
		std::chrono::steady_clock::duration fixedUpdateInterval { std::chrono::milliseconds ( 16 ) };

		static void GLAPIENTRY debugCallback (
			GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar * message,
			const void * userParam
		);

		Window window;
		ImGuiContext * imguiContext;
		std::unique_ptr <Scene> scene;
		bool quit { false };
	};



	// Implementation
	inline Window & Application::GetWindow () { return window; }
	inline void Application::Quit () { quit = true; }
}
