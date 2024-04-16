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
	float const Camera::rotateSensitivity { 36.0f };
	float const Camera::moveSensitivity { 6.0f };

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

		auto rotationDelta { glm::vec3 { window->GetCursorDelta ().y, window->GetCursorDelta ().x, 0.0f } };
		Rotate ( rotationDelta * rotateSensitivity * delta );

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
		glm::vec3 localRight { glm::cross ( up, lookDirection ) };
		glm::vec3 localUp { glm::cross ( localRight, lookDirection ) };

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