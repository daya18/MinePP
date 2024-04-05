#include "Window.hpp"

#include <imgui_impl_glfw.h>

#include <iostream>

namespace mpp
{
	Window::Window ( std::string const & title, glm::vec2 const & size )
	{
		auto glfwInitResult { glfwInit () };
		std::cout << "GLFW initialization " << ( glfwInitResult ? "successful" : "failed" ) << std::endl;

		glfwWindowHint ( GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE );
		window = glfwCreateWindow ( 1280, 720, "MinePP", nullptr, nullptr );

		glfwSetWindowUserPointer ( window, this );

		glfwSetKeyCallback ( window, GLFWKeyCallback );
		glfwSetCursorPosCallback ( window, GLFWCursorPositionCallback );
		glfwSetCursorEnterCallback ( window, GLFWCursorEnterCallback );

		if ( glfwRawMouseMotionSupported () )
		{
			glfwSetInputMode ( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
			glfwSetInputMode ( window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE );
		}
	}
	
	void Window::MakeContextCurrent ()
	{
		glfwMakeContextCurrent ( window );
	}
	
	bool Window::ShouldClose ()
	{
		return glfwWindowShouldClose ( window );
	}
	
	void Window::SwapBuffers ()
	{
		glfwSwapBuffers ( window );
	}
	
	bool Window::GetkeyState ( int key )
	{
		return glfwGetKey ( window, key );
	}

	void Window::InitImGuiForOpenGL ()
	{
		ImGui_ImplGlfw_InitForOpenGL ( window, true );
	}

	void Window::GLFWKeyCallback ( GLFWwindow * glfwWindow, int key, int scancode, int action, int mods )
	{
		auto & window { *GetWindow ( glfwWindow ) };
		
		for ( auto const & keyCallback : window.keyCallbacks )
			keyCallback ( key, action );
	}

	void Window::GLFWCursorPositionCallback ( GLFWwindow * glfwWindow, double xpos, double ypos )
	{
		auto & window { *GetWindow ( glfwWindow ) };
		
		glm::vec2 currentMousePosition { static_cast < float > ( xpos ), static_cast < float > ( ypos ) };
		
		if ( ! window.ignoreNextMouseMotion )
		{
			for ( auto const & mouseMotionCallback : window.mouseMotionCallbacks )
				mouseMotionCallback ( currentMousePosition - window.lastMousePosition );
			
		}
		else
			window.ignoreNextMouseMotion = false;

		window.lastMousePosition = currentMousePosition;
	}

	void Window::GLFWCursorEnterCallback ( GLFWwindow * window, int entered )
	{
		if ( entered )
			GetWindow ( window )->ignoreNextMouseMotion = true;
	}

	Window * Window::GetWindow ( GLFWwindow * window )
	{
		return reinterpret_cast < Window * > ( glfwGetWindowUserPointer ( window ) );
	}

}