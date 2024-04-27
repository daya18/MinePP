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
	set_source_files_properties ( external/glad/src/glad.c PROPERTIES LANGUAGE CXX )
	
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

	# Add freetype
	add_subdirectory ( external/freetype-2.10.0 )
	target_link_libraries ( MinePP PRIVATE freetype )

# Set sources
target_sources ( MinePP PRIVATE 
	source/Application.cpp 
	source/opengl/Shader.cpp 
	"source/scene/world/World.cpp"
	source/opengl/VertexArray.cpp 
	source/opengl/Type.cpp
	source/opengl/Buffer.cpp 
	"source/scene/world/Camera.cpp" 
	source/main.cpp
	source/Window.cpp
	"source/scene/world/WorldCache.cpp" 
	"source/opengl/Texture.cpp" 
	"source/scene/world/Block.cpp" 
	
	"source/scene/Transform.cpp" 
	 
	"source/scene/world/InventoryHUD.cpp" 
	"source/gui/Rectangle.cpp" 
	"source/gui/RectangleRenderer.cpp" 
	"source/gui/BlockThumbnailRenderer.cpp" 
	"source/scene/world/BlockCache.cpp"
	"source/opengl/Framebuffer.cpp"  
	"source/scene/MainMenu.cpp"
	"source/gui/Text.cpp"
 "source/gui/TextRenderer.cpp"   "source/scene/world/Chunk.cpp")

# Set precompiled header
target_precompile_headers ( MinePP PRIVATE source/PrecompiledHeader.hpp )