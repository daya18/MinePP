#shader vertex

#version 440 core

layout ( location = 0 ) in vec3 i_position;
layout ( location = 1 ) in vec2 i_textureCoordinates;

layout ( location = 0 ) out vec2 o_textureCoordinates;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main ()
{
	gl_Position = u_projectionMatrix * u_viewMatrix * vec4 ( i_position, 1.0f );
	o_textureCoordinates = i_textureCoordinates;
}



#shader fragment

#version 440 core

layout ( location = 0 ) in vec2 i_textureCoordinates;

layout ( location = 0 ) out vec4 o_color;

uniform sampler2D u_sampler;

void main ()
{
	o_color = texture ( u_sampler, i_textureCoordinates );
}