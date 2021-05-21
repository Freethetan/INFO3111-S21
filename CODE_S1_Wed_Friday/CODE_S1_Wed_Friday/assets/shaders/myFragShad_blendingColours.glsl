#version 420
// myFragShad.glsl

in vec3 colour;

out vec4 outputColour;

uniform vec4 wholeObjCol;
uniform bool bUseVertColour;

void main()
{
    //gl_FragColor = vec4(color, 1.0);
	
	if ( bUseVertColour )
	{
		// Use the vertex colour
		outputColour = vec4(colour, 1.0f);
	}
	else
	{
		// Use the "whole object colour"
		outputColour = wholeObjCol;
	}
};
