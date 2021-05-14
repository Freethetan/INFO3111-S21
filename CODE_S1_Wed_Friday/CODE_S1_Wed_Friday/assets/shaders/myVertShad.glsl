#version 420
// myVertShad.glsl

uniform mat4 MVP;

attribute vec3 vertexColour;
attribute vec3 vertexPosition;

out vec3 colour;

void main()
{
	vec3 thisVertex = vertexPosition;

    //gl_Position = MVP * vec4(vPos, 0.0, 1.0);
	gl_Position = MVP * vec4(thisVertex, 1.0f);
	
	// Now pick a colour
	vec3 theColour = vertexColour;

    colour = theColour;	// vCol;
};
