#version 420
// Vertex shader

uniform mat4 MVP;

// Vertex layout
attribute vec3 vCol;
attribute vec3 vPos;	// added a z

out vec3 color;

void main()
{
	// Note the 0.0 is gone (was the z coord)
    gl_Position = MVP * vec4(vPos, 1.0);
    color = vCol;
};



