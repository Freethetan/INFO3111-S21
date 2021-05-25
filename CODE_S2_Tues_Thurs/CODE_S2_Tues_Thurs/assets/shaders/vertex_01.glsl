#version 420
// Vertex shader

//uniform mat4 MVP;
uniform mat4 mProjection;
uniform mat4 mView;
uniform mat4 mModel;

// Vertex layout
// Also used to be "attribute" is now "in"
in vec3 theVertexColour;			
in vec3 thePositionXYZ;	// added a z
in vec3 theNormal;

out vec3 colour;
out vec3 vNormal;		// "v" for "vertex"

void main()
{
	mat4 mMVP = mProjection * mView * mModel;
	
	// Note the 0.0 is gone (was the z coord)
    gl_Position = mMVP * vec4(thePositionXYZ, 1.0);
    colour = theVertexColour;
	
	vNormal = theNormal;
};



