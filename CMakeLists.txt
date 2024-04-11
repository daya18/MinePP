cmake_minimum_required ( VERSION 3.20 )

project ( MinePP )

set ( CMAKE_CXX_STANDARD 20 )

add_executable ( MinePP )

# Add external dependencies
	# Add GLFW
	add_subdirectory ( external/glfw-3.4 )
	target_link_libraries ( MinePP PRIVATE glfw )

	# Add GLAD
	target_include_directories ( MinePP PRIVATE external/glad/include )
	target_sources ( MinePP PRIVATE external/glad/src/glad.c  )
	
	# Add GLM
	add_subdirectory ( external/glm )
	target_link_libraries ( MinePP PRIVATE glm )

	# Add IMGUI
	target_sources ( MinePP PRIVATE 
		external/imgui/imgui.cpp
		external/imgui/imgui_demo.cpp
		external/imgui/imgui_draw.cpp
		external/imgui/imgui_widgets.cpp
		external/imgui/imgui_tables.cpp
		external/imgui/backends/imgui_impl_opengl3.cpp
		external/imgui/backends/imgui_impl_glfw.cpp
	)
	target_include_directories ( MinePP PRIVATE 
		external/imgui 
		external/imgui/backends 
	)

	# Add OBJLoader
	target_include_directories ( MinePP PRIVATE external/OBJ-Loader/Source )

	# Add stb image
	target_include_directories ( MinePP PRIVATE external )

# Set sources
target_sources ( MinePP PRIVATE 
	source/Application.cpp 
	source/opengl/Shader.cpp 
	source/World.cpp
	source/opengl/VertexArray.cpp 
	source/opengl/Type.cpp
	source/opengl/Buffer.cpp 
	source/Camera.cpp 
	source/main.cpp
	source/Window.cpp
	source/WorldRenderer.cpp 
	source/BlockModel.cpp
 "source/opengl/Texture.cpp")
