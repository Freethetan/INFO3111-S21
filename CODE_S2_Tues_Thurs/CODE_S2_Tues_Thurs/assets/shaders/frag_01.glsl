#version 420
// Pixel Fragment shader

in vec3 colour;

out vec4 pixelOutputColour;

uniform vec4 wholeObjCol;
uniform bool bVertCol;

void main()
{
    //gl_FragColor = vec4(color, 1.0);
	
	if ( bVertCol )
	{
		// Use the vertex colours from the file
		pixelOutputColour = vec4(colour, 1.0);
	}
	else
	{
		// Use the whole object colour
		pixelOutputColour = wholeObjCol;
	}
};