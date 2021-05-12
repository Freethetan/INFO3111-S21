#version 420
// myVertShad.glsl

uniform mat4 MVP;

attribute vec3 vCol;
attribute vec2 vPos;

out vec3 colour;

void main()
{
	float scale = 4.0f;
	float xOffset = 0.0f;
	float yOffset = -0.3f;	
	float roation = 13.0f;
	
	vec2 thisVertex = vPos;

	thisVertex.x *= scale;
	thisVertex.y *= scale;

	thisVertex.x += xOffset;
	thisVertex.y += yOffset;		


    //gl_Position = MVP * vec4(vPos, 0.0, 1.0);
	gl_Position = MVP * vec4(thisVertex, 0.0f, 1.0f);
	
	// Now pick a colour
	vec3 theColour = vCol;
	theColour.r = 0.0f;
	theColour.g = 0.0f;
	theColour.b = 0.0f;
	
	// sqrt(X ^ 2 + y ^ 2)
	float distance = sqrt( (thisVertex.x * thisVertex.x) + 
						   (thisVertex.y * thisVertex.y) );
	
	if ( distance > 0.15f )
	{
		theColour.g = 1.0f;
	}
	else
	{
		theColour.r = 1.0f;
	}
	
    colour = theColour;	// vCol;
};
