#pragma once

#include <string>

#include <glm/glm.hpp>

#include <GLFW/glfw3.h>

namespace mpp
{
	class Window
	{
	public:
		using MouseMotionCallback = std::function < void ( glm::vec2 const & ) >;
		using KeyCallback = std::function < void ( int, int ) >;

		Window ( std::string const & title, glm::vec2 const & size );
		
		void MakeContextCurrent ();
		bool ShouldClose ();
		void InitImGuiForOpenGL ();
		void SwapBuffers ();
		bool GetkeyState ( int key );

		float GetAspectRatio () const;

		void AddMouseMotionCallback ( MouseMotionCallback );
		void AddKeyCallback ( KeyCallback );

	private:
		static void GLFWKeyCallback ( GLFWwindow * window, int key, int scancode, int action, int mods );
		static void GLFWCursorPositionCallback ( GLFWwindow * window, double xpos, double ypos );
		static void GLFWCursorEnterCallback ( GLFWwindow *, int entered );
		static Window * GetWindow ( GLFWwindow * );

		GLFWwindow * window;
		std::vector <MouseMotionCallback> mouseMotionCallbacks;
		std::vector <KeyCallback> keyCallbacks;
		glm::vec2 lastMousePosition { 0.0f, 0.0f };
		bool ignoreNextMouseMotion { false };
	};



	// Implementation
	inline void Window::AddMouseMotionCallback ( MouseMotionCallback callback )
	{ mouseMotionCallbacks.push_back ( callback ); }
	
	inline void Window::AddKeyCallback ( KeyCallback callback )
	{ keyCallbacks.push_back ( callback ); }
}