#pragma once

#include <glm/glm.hpp>

namespace mpp
{
	class Window;

	class Camera
	{
	public:
		Camera ( Window &, glm::vec3 const & position );
		~Camera ();

		void Update ();

		void SetPosition ( glm::vec3 const & position );
		void Rotate ( glm::vec3 );

		glm::mat4 const & GetViewMatrix () const;
		glm::mat4 const & GetProjectionMatrix () const;

	private:
		void OnMouseMove ( glm::vec2 const & delta );

		void UpdateViewMatrix ();
		void UpdateProjectionMatrix ();

		static float const rotateSensitivity;
		static float const moveSensitivity;

		Window * window;

		glm::vec3 position;
		glm::vec3 lookDirection;
		
		float aspect;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};



	// Implementation
	inline glm::mat4 const & Camera::GetViewMatrix () const { return viewMatrix; }
	inline glm::mat4 const & Camera::GetProjectionMatrix () const { return projectionMatrix; }

}