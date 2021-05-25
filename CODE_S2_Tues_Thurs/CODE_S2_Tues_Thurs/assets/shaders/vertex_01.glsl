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
out vec4 vVertexWorld;	// vertex position in world coordinates

void main()
{
	mat4 mMVP = mProjection * mView * mModel;
	
	// Note the 0.0 is gone (was the z coord)
    gl_Position = mMVP * vec4(thePositionXYZ, 1.0);
    colour = theVertexColour;
	
	// This is the location of the vertex in the world 
	// (i.e. not based on the view or projection)
	vVertexWorld = mModel * vec4(thePositionXYZ, 1.0);	
	
	vNormal = theNormal;
};



