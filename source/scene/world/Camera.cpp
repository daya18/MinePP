#include "Camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "World.hpp"
#include "../../Window.hpp"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>

namespace mpp
{
	float const Camera::rotateSensitivity { 0.2f };
	float const Camera::moveSensitivity { 10.0f };

	Camera::Camera ( Window & window, World & world, glm::vec3 const & position )
	:
		window ( & window ),
		world ( & world ),
		position ( position ),
		lookDirection { 0.0f, 0.0f, -1.0f },
		aspect { window.GetAspectRatio () }
	{
		UpdateViewMatrix ();
		UpdateProjectionMatrix ();
		lastKnownMousePosition = window.GetMousePosition ();
	}

	Camera::~Camera ()
	{
	}
	
	void Camera::Update ( float delta )
	{
		glm::vec3 up { 0.0f, 1.0f, 0.0f };
		glm::vec3 moveRightDir { glm::cross ( lookDirection, up ) };
		glm::vec3 moveForwardDir { glm::cross ( moveRightDir, up ) };

		if ( window->GetkeyState ( GLFW_KEY_W ) )
			this->position -= moveForwardDir * moveSensitivity * delta;
		
		if ( window->GetkeyState ( GLFW_KEY_S ) )
			this->position += moveForwardDir * moveSensitivity * delta;

		if ( window->GetkeyState ( GLFW_KEY_D ) )
			this->position += moveRightDir * moveSensitivity * delta;

		if ( window->GetkeyState ( GLFW_KEY_A ) )
			this->position -= moveRightDir * moveSensitivity * delta;

		if ( window->GetkeyState ( GLFW_KEY_LEFT_SHIFT ) )
			this->position -= up * moveSensitivity * delta;

		if ( window->GetkeyState ( GLFW_KEY_SPACE ) )
			this->position += up * moveSensitivity * delta;

		auto currentMousePosition { window->GetMousePosition () };
		auto mouseDelta { currentMousePosition - lastKnownMousePosition };
		lastKnownMousePosition = currentMousePosition;

		Rotate ( glm::vec3 { mouseDelta.y, mouseDelta.x, 0.0f } * rotateSensitivity );

		UpdateViewMatrix ();
	}

	void Camera::SetPosition ( glm::vec3 const & position )
	{
		this->position = position;
		UpdateViewMatrix ();
	}
	
	void Camera::Rotate ( glm::vec3 delta )
	{
		glm::vec3 up { 0.0f, 1.0f, 0.0f };
		glm::vec3 localRight { glm::normalize ( glm::cross ( up, lookDirection ) ) };
		glm::vec3 localUp { glm::normalize ( glm::cross ( localRight, lookDirection ) ) };

		lookDirection = glm::rotate ( lookDirection, glm::radians ( delta.x ) , localRight );
		lookDirection = glm::rotate ( lookDirection, glm::radians ( delta.y ) , localUp );
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