#shader vertex

#version 440 core

layout ( location = 0 ) in vec3 i_position;

uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

void main ()
{
	gl_Position = u_projectionMatrix * u_viewMatrix * vec4 ( i_position, 1.0f );
}



#shader fragment

#version 440 core

layout ( location = 0 ) out vec4 o_color;

void main ()
{
	o_color = vec4 ( 1, 0, 0, 1 );
}