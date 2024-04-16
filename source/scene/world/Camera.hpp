#pragma once

#include <glm/glm.hpp>

namespace mpp
{
	class Window;
	class World;

	class Camera
	{
	public:
		Camera ( Window &, World &, glm::vec3 const & position );
		~Camera ();

		void Update ( float delta );

		void SetPosition ( glm::vec3 const & position );
		void Rotate ( glm::vec3 );

		glm::mat4 const & GetViewMatrix () const;
		glm::mat4 const & GetProjectionMatrix () const;

		glm::vec3 const & GetPosition () const;
		glm::vec3 const & GetLookDirection () const;

	private:
		void OnMouseMove ( glm::vec2 const & delta );

		void UpdateViewMatrix ();
		void UpdateProjectionMatrix ();

		static float const rotateSensitivity;
		static float const moveSensitivity;

		Window * window;
		World * world;

		glm::vec3 position;
		glm::vec3 lookDirection;
		
		float aspect;

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		
		glm::vec2 lastKnownMousePosition { 0.0f, 0.0f };
	};



	// Implementation
	inline glm::mat4 const & Camera::GetViewMatrix () const { return viewMatrix; }
	inline glm::mat4 const & Camera::GetProjectionMatrix () const { return projectionMatrix; }
	inline glm::vec3 const & Camera::GetPosition () const { return position; }
	inline glm::vec3 const & Camera::GetLookDirection () const { return lookDirection; }

}