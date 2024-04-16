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
		window = glfwCreateWindow ( size.x, size.y, title.data (), nullptr, nullptr);

		glfwSetWindowUserPointer ( window, this );

		glfwSetKeyCallback ( window, GLFWKeyCallback );
		glfwSetMouseButtonCallback ( window, GLFWButtonCallback );
		glfwSetScrollCallback ( window, GLFWScrollCallback );
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
	
	void Window::SetRawInput ( bool enabled )
	{
		if ( ! glfwRawMouseMotionSupported () )
			return;
		
		glfwSetInputMode ( window, GLFW_CURSOR, enabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL );
		glfwSetInputMode ( window, GLFW_RAW_MOUSE_MOTION, enabled ? GLFW_TRUE : GLFW_FALSE );
	}

	float Window::GetAspectRatio () const
	{
		int width, height;
		glfwGetFramebufferSize ( window, &width, &height );
		return static_cast < float > ( width ) / static_cast < float > ( height );
	}
	
	glm::vec2 Window::GetSize () const
	{
		glm::ivec2 size;
		glfwGetFramebufferSize ( window, &size.x, &size.y );
		return size;
	}
	
	glm::vec2 Window::GetMousePosition () const 
	{
		glm::dvec2 position;
		glfwGetCursorPos ( window, &position.x, &position.y );
		return position; 
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

	void Window::GLFWButtonCallback ( GLFWwindow * glfwWindow, int button, int action, int mods )
	{
		auto & window { *GetWindow ( glfwWindow ) };

		for ( auto const & buttonCallback : window.buttonCallbacks )
			buttonCallback ( button, action );
	}
	
	void Window::GLFWScrollCallback ( GLFWwindow * glfwWindow, double xoffset, double yoffset )
	{
		for ( auto const & scrollCallback : GetWindow ( glfwWindow )->scrollCallbacks )
		{
			scrollCallback ( { xoffset, yoffset } );
		}
	}

	Window * Window::GetWindow ( GLFWwindow * window )
	{
		return reinterpret_cast < Window * > ( glfwGetWindowUserPointer ( window ) );
	}

}