#shader vertex

#version 440 core

layout ( location = 0 ) in vec3 i_position;

uniform mat4 u_projectionMatrix;
uniform mat4 u_instanceTransformMatrices [1000];

void main ()
{
	mat4 modelMatrix = u_instanceTransformMatrices [gl_InstanceID];

	gl_Position = u_projectionMatrix * modelMatrix * vec4 ( i_position, 1.0f );
}



#shader fragment

#version 440 core

layout ( location = 0 ) out vec4 o_color;

void main ()
{
	o_color = vec4 ( 1, 1, 1, 1 );
}