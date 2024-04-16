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
		using ButtonCallback = std::function < void ( int, int ) >;
		using ScrollCallback = std::function < void ( glm::vec2 ) >;

		Window ( std::string const & title, glm::vec2 const & size );
		
		void MakeContextCurrent ();
		bool ShouldClose ();
		void InitImGuiForOpenGL ();
		void SwapBuffers ();
		bool GetkeyState ( int key );
		void SetRawInput ( bool );

		float GetAspectRatio () const;

		void AddMouseMotionCallback ( MouseMotionCallback );
		void AddKeyCallback ( KeyCallback );
		void AddButtonCallback ( ButtonCallback );
		void AddScrollCallback ( ScrollCallback );

		glm::vec2 GetSize () const;

	private:
		static void GLFWKeyCallback ( GLFWwindow * window, int key, int scancode, int action, int mods );
		static void GLFWButtonCallback ( GLFWwindow * window, int button, int action, int mods );
		static void GLFWCursorPositionCallback ( GLFWwindow * window, double xpos, double ypos );
		static void GLFWCursorEnterCallback ( GLFWwindow *, int entered );
		static void GLFWScrollCallback ( GLFWwindow * window, double xoffset, double yoffset );

		static Window * GetWindow ( GLFWwindow * );

		GLFWwindow * window;
		
		std::vector <MouseMotionCallback> mouseMotionCallbacks;
		std::vector <KeyCallback> keyCallbacks;
		std::vector <ButtonCallback> buttonCallbacks;
		std::vector <ScrollCallback> scrollCallbacks;

		glm::vec2 lastMousePosition { 0.0f, 0.0f };
		bool ignoreNextMouseMotion { false };
	};



	// Implementation
	inline void Window::AddMouseMotionCallback ( MouseMotionCallback callback )
	{ mouseMotionCallbacks.push_back ( callback ); }
	
	inline void Window::AddKeyCallback ( KeyCallback callback )
	{ keyCallbacks.push_back ( callback ); }

	inline void Window::AddButtonCallback ( ButtonCallback callback )
	{ buttonCallbacks.push_back ( callback ); }

	inline void Window::AddScrollCallback ( ScrollCallback callback )
	{ scrollCallbacks.push_back ( callback ); }

}