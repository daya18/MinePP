#include <iostream>

#include <GLAD/glad.h>

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

int main ()
{
	auto glfwInitResult { glfwInit () };
	std::cout << "GLFW initialization " << ( glfwInitResult ? "successful" : "failed" ) << std::endl;

	GLFWwindow * window { glfwCreateWindow ( 1280, 720, "MinePP", nullptr, nullptr ) };
	glfwMakeContextCurrent ( window );

	auto gladInitResult { gladLoadGL () };
	std::cout << "GLAD initialization " << ( gladInitResult ? "successful" : "failure" ) << std::endl;

	auto imguiContext { ImGui::CreateContext () };
	ImGui_ImplOpenGL3_Init ();
	ImGui_ImplGlfw_InitForOpenGL ( window, true );

	while ( ! glfwWindowShouldClose ( window ) )
	{
		glfwPollEvents ();

		glClearColor ( 0.0f, 1.0f, 0.0f, 1.0f );
		glClear ( GL_COLOR_BUFFER_BIT );

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