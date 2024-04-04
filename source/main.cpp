#include <iostream>

#include <GLAD/glad.h>

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

#include "opengl/Shader.hpp"
#include "opengl/VertexArray.hpp"
#include "opengl/Buffer.hpp"

void GLAPIENTRY debugCallback ( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam ) 
{
	std::cout << "OpenGL Debug Message: " << message << std::endl;
}

int main ()
{
	auto glfwInitResult { glfwInit () };
	std::cout << "GLFW initialization " << ( glfwInitResult ? "successful" : "failed" ) << std::endl;

	glfwWindowHint ( GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE );
	GLFWwindow * window { glfwCreateWindow ( 1280, 720, "MinePP", nullptr, nullptr ) };
	glfwMakeContextCurrent ( window );
	
	auto gladInitResult { gladLoadGL () };
	std::cout << "GLAD initialization " << ( gladInitResult ? "successful" : "failed" ) << std::endl;

	glEnable ( GL_DEBUG_OUTPUT );
	glDebugMessageCallback ( debugCallback, nullptr );

	auto imguiContext { ImGui::CreateContext () };
	ImGui_ImplOpenGL3_Init ();
	ImGui_ImplGlfw_InitForOpenGL ( window, true );

	mpp::Shader shader { "shader/Shader.glsl" };
	
	mpp::Buffer vertexBuffer;
	vertexBuffer.SetData ( std::vector <float> { 0.0f, 0.5f, 0.0f,  0.5f, -0.5f, 0.0f,  -0.5f, -0.5f, 0.0f }, GL_STATIC_DRAW );

	mpp::VertexArray vertexArray { { { GL_FLOAT, 3 } } };

	while ( ! glfwWindowShouldClose ( window ) )
	{
		glfwPollEvents ();

		glClearColor ( 0.0f, 1.0f, 0.0f, 1.0f );
		glClear ( GL_COLOR_BUFFER_BIT );

		shader.Bind ();
		vertexArray.Bind ();
		vertexArray.BindVertexBuffer ( vertexBuffer );

		glDrawArrays ( GL_TRIANGLES, 0, 3 );

		ImGui_ImplGlfw_NewFrame ();
		ImGui_ImplOpenGL3_NewFrame ();
		
		ImGui::NewFrame ();
			ImGui::ShowDemoWindow ();
		ImGui::EndFrame ();
		
		ImGui::Render ();
		ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData () );
		
		glfwSwapBuffers ( window );
	}

	ImGui_ImplOpenGL3_Shutdown ();
	ImGui_ImplGlfw_Shutdown ();
	
	ImGui::DestroyContext ( imguiContext );

	glfwTerminate ();
}