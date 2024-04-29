#include "Batch.hpp"

#include "../../opengl/Shader.hpp"
#include "../../opengl/Texture.hpp"
#include "Block.hpp"

namespace mpp
{
	Batch::Batch ( Texture const & texture, std::vector <Block *> const & blocks )
	: 
		texture ( &texture ),
		uniformBuffer ( std::vector { glm::identity <glm::mat4> () }, GL_STATIC_DRAW )
	{
		std::vector <glm::mat4> transforms;
		transforms.reserve ( blocks.size () );

		for ( auto block : blocks )
			transforms.push_back ( block->GetTransform () );

		uniformBuffer.SetData ( transforms, GL_STATIC_DRAW );
		instanceCount = transforms.size ();
	}

	void Batch::Render ( Shader & shader )
	{
		shader.SetUniform ( "u_sampler", 0 );
		texture->Bind ( 0 );

		shader.SetUniformBlockBinding ( "u_modelMatrices", 0 );
		uniformBuffer.BindBase ( GL_UNIFORM_BUFFER, 0 );
		
		glDrawElementsInstanced ( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, instanceCount );
	}
}