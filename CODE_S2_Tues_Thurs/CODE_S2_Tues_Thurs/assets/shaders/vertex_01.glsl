#version 420
// Vertex shader

//uniform mat4 MVP;
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

// Vertex layout
attribute vec3 theVertexColour;
attribute vec3 thePositionXYZ;	// added a z

out vec3 colour;

void main()
{
	mat4 mMVP = mProjection * mView * mModel;
	
	// Note the 0.0 is gone (was the z coord)
    gl_Position = mMVP * vec4(thePositionXYZ, 1.0);
    colour = theVertexColour;
};



