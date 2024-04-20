#include "Transform.hpp"

namespace mpp
{
	Transform::Transform ( glm::vec3 const & position, glm::vec3 const & scale )
		: position ( position ), scale ( scale )
	{
		UpdateMatrix ();
	}

	void Transform::SetPosition ( glm::vec3 const & position ) 
	{ 
		this->position = position; 
		UpdateMatrix ();
	}

	void Transform::Move ( glm::vec3 const & delta ) 
	{ 
		this->position += delta; 
		UpdateMatrix ();
	}
	
	void Transform::SetScale ( glm::vec3 const & scale ) 
	{ 
		this->scale = scale; 
		UpdateMatrix ();
	}

	void Transform::Scale ( glm::vec3 const & delta ) 
	{ 
		this->scale += delta; 
		UpdateMatrix ();
	}

	void Transform::UpdateMatrix ()
	{
		static constexpr glm::mat4 identityMatrix { glm::identity <glm::mat4> () };

		glm::mat4 translationMatrix { glm::translate ( identityMatrix, position ) };
		glm::mat4 scaleMatrix		{ glm::scale ( identityMatrix, scale ) };

		matrix = translationMatrix * scaleMatrix;
	}
}