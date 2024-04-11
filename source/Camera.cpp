#include "Camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "Window.hpp"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>

namespace mpp
{
	float const Camera::rotateSensitivity { 0.2f };
	float const Camera::moveSensitivity { 0.02f };

	Camera::Camera ( Window & window, glm::vec3 const & position )
	:
		window ( & window ),
		position ( position ),
		lookDirection { 0.0f, 0.0f, -1.0f },
		aspect { window.GetAspectRatio () }
	{
		UpdateViewMatrix ();
		UpdateProjectionMatrix ();

		// Bind window event handlers
		window.AddMouseMotionCallback ( [this] ( glm::vec2 const & delta ) { OnMouseMove ( delta ); } );
	}

	Camera::~Camera ()
	{
	}
	
	void Camera::Update ()
	{
		glm::vec3 up { 0.0f, 1.0f, 0.0f };
		glm::vec3 moveRightDir { glm::cross ( lookDirection, up ) };
		glm::vec3 moveForwardDir { glm::cross ( moveRightDir, up ) };

		if ( window->GetkeyState ( GLFW_KEY_W ) )
			this->position -= moveForwardDir * moveSensitivity;
		
		if ( window->GetkeyState ( GLFW_KEY_S ) )
			this->position += moveForwardDir * moveSensitivity;

		if ( window->GetkeyState ( GLFW_KEY_D ) )
			this->position += moveRightDir * moveSensitivity;

		if ( window->GetkeyState ( GLFW_KEY_A ) )
			this->position -= moveRightDir * moveSensitivity;

		if ( window->GetkeyState ( GLFW_KEY_LEFT_SHIFT ) )
			this->position -= up * moveSensitivity;

		if ( window->GetkeyState ( GLFW_KEY_SPACE ) )
			this->position += up * moveSensitivity;

		UpdateViewMatrix ();
	}

	void Camera::OnMouseMove ( glm::vec2 const & delta )
	{
		Rotate ( { delta.y, delta.x, 0.0f } );
	}

	void Camera::SetPosition ( glm::vec3 const & position )
	{
		this->position = position;
		UpdateViewMatrix ();
	}
	
	void Camera::Rotate ( glm::vec3 delta )
	{
		glm::vec3 up { 0.0f, 1.0f, 0.0f };
		glm::vec3 localRight { glm::cross ( up, lookDirection ) };
		glm::vec3 localUp { glm::cross ( localRight, lookDirection ) };

		lookDirection = glm::rotate ( lookDirection, glm::radians ( delta.x * rotateSensitivity ) , localRight );
		lookDirection = glm::rotate ( lookDirection, glm::radians ( delta.y * rotateSensitivity ) , localUp );
	}

	void Camera::UpdateViewMatrix ()
	{
		viewMatrix = glm::lookAt ( position, position + lookDirection, glm::vec3 { 0.0f, 1.0f, 0.0f } );
	}

	void Camera::UpdateProjectionMatrix ()
	{
		projectionMatrix = glm::perspective ( glm::radians ( 45.0f ), aspect, 0.1f, 1000.0f );
	}
}