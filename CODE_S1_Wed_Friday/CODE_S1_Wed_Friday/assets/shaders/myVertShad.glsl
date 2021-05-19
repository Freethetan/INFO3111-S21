#version 420
// myVertShad.glsl

//uniform mat4 MVP;
uniform mat4 mView;		// View
uniform mat4 mModel;	// Model or World
uniform mat4 mProj;		// Projection

attribute vec3 vertexColour;
attribute vec3 vertexPosition;

out vec3 colour;

void main()
{
	vec3 thisVertex = vertexPosition;

    mat4 matMVP;
	// matMVP = matProjection * matView * matModel;
	matMVP = mProj * mView * mModel;
	
	gl_Position = matMVP * vec4(thisVertex, 1.0f);
	
	// Now pick a colour
	vec3 theColour = vertexColour;

    colour = theColour;	// vCol;
};
