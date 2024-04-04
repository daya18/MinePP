#shader vertex

#version 440 core

layout ( location = 0 ) in vec3 position;

void main ()
{
	gl_Position = vec4 ( position, 1.0f );
}



#shader fragment

#version 440 core

layout ( location = 0 ) out vec4 color;

void main ()
{
color = vec4 ( 1, 0, 0, 1 );
}