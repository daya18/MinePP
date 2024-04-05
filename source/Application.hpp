#pragma once 

#include <memory>

#include <GLAD/glad.h>
#include <imgui.h>

#include "Window.hpp"
#include "World.hpp"

namespace mpp
{
	class Application
	{
	public:
		Application ();
		~Application ();

		void Run ();

	private:
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

		std::unique_ptr <World> world;
	};
}