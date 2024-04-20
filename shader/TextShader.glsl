#shader vertex

#version 440 core

layout ( location = 0 ) in vec3 i_position;
layout ( location = 1 ) in vec2 i_textureCoordinates;

layout ( location = 0 ) out vec2 o_textureCoordinates;

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelMatrix;

void main ()
{
	gl_Position = u_projectionMatrix * u_modelMatrix * vec4 ( i_position, 1.0f );
	o_textureCoordinates = i_textureCoordinates;
}



#shader fragment

#version 440 core

layout ( location = 0 ) in vec2 i_textureCoordinates;

layout ( location = 0 ) out vec4 o_color;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main ()
{
	o_color = vec4 ( texture ( u_texture, i_textureCoordinates ).r, 0.0f, 0.0f, 1.0f );
}