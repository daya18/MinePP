#shader vertex

#version 440 core

layout ( location = 0 ) in vec3 i_position;
layout ( location = 1 ) in vec2 i_textureCoordinates;
layout ( location = 2 ) in vec2 i_maskTextureCoordinates;

layout ( location = 0 ) out vec2 o_textureCoordinates;
//layout ( location = 1 ) out vec2 o_maskTextureCoordinates;

uniform u_modelMatrices
{
	mat4 modelMatrices [10000];
}
modelMatrices;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main ()
{
	mat4 modelMatrix = modelMatrices.modelMatrices [gl_InstanceID];
	gl_Position = u_projectionMatrix * u_viewMatrix * modelMatrix * vec4 ( i_position, 1.0f );
	o_textureCoordinates = i_textureCoordinates;
	//o_maskTextureCoordinates = i_maskTextureCoordinates;
}



#shader fragment

#version 440 core

layout ( location = 0 ) in vec2 i_textureCoordinates;
//layout ( location = 1 ) in vec2 i_maskTextureCoordinates;

layout ( location = 0 ) out vec4 o_color;

uniform sampler2D u_sampler;

//uniform sampler2D u_maskSampler;
//uniform int u_useMask;

void main ()
{
	o_color = texture ( u_sampler, i_textureCoordinates );
	//o_color = vec4 ( 1, 1, 1, 1 );
//	if ( u_useMask == 1 )
//	{
//		float maskSample = texture ( u_maskSampler, i_maskTextureCoordinates ).a;
//		
//		if ( maskSample != 0.0f )
//			o_color = vec4 ( 0, 0, 0, maskSample );
//	}
}
