#version 420
// myVertShad.glsl

uniform mat4 MVP;

//struct sVertex
//{
 //   float x, y, z
//    float r, g, b;
//};

attribute vec3 vertexColour;
attribute vec3 vertexPosition;

out vec3 colour;

void main()
{
//	float scale = 4.0f;
//	float xOffset = 0.0f;
//	float yOffset = -0.3f;	
//	float roation = 13.0f;
	
	vec3 thisVertex = vertexPosition;

//	thisVertex.x *= scale;
//	thisVertex.y *= scale;
//	thisVertex.z *= scale;

//	thisVertex.y += yOffset;		


    //gl_Position = MVP * vec4(vPos, 0.0, 1.0);
	gl_Position = MVP * vec4(thisVertex, 1.0f);
	
	// Now pick a colour
	vec3 theColour = vertexColour;
	theColour.r = 0.0f;
	theColour.g = 0.0f;
	theColour.b = 0.0f;
	
	// sqrt(X ^ 2 + y ^ 2)
	float distance = sqrt( (thisVertex.x * thisVertex.x) + 
						   (thisVertex.y * thisVertex.y) );
	
	if ( distance > 0.03f )
	{
		theColour.g = 1.0f;
	}
	else
	{
		theColour.r = 1.0f;
	}
	
    colour = theColour;	// vCol;
};
