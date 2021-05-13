#version 420
// Vertex shader

uniform mat4 MVP;

// Vertex layout
attribute vec3 theVertexColour;
attribute vec3 thePositionXYZ;	// added a z

out vec3 color;

void main()
{
	// Note the 0.0 is gone (was the z coord)
    gl_Position = MVP * vec4(thePositionXYZ, 1.0);
    color = theVertexColour;
};



