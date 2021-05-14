#version 420
// myFragShad.glsl

in vec3 colour;

out vec4 outputColour;

void main()
{
    //gl_FragColor = vec4(color, 1.0);
	
	
	outputColour = vec4(colour, 1.0f);
};
