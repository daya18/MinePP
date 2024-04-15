#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mpp
{
	class Transform
	{
	public:
		Transform ( glm::vec3 const & position = glm::zero <glm::vec3> () );

		void SetPosition ( glm::vec3 const & );
		void Move ( glm::vec3 const & );
		void SetScale ( glm::vec3 const & );
		void Scale ( glm::vec3 const & );
		glm::mat4 const & GetMatrix () const;
		glm::vec3 const & GetPosition () const;
		glm::vec3 const & GetScale () const;

	private:
		void UpdateMatrix ();

		glm::vec3 position { glm::zero <glm::vec3> () };
		glm::vec3 scale { glm::one <glm::vec3> () };

		glm::mat4 matrix { glm::identity <glm::mat4> () };
	};



	// Implementation
	inline glm::mat4 const & Transform::GetMatrix () const { return matrix; }
	inline glm::vec3 const & Transform::GetPosition () const { return position; }
	inline glm::vec3 const & Transform::GetScale () const { return scale; }
}