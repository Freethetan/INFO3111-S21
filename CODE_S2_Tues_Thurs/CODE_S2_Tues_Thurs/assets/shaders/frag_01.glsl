#version 420
// Pixel Fragment shader

in vec3 color;

out vec4 pixelOutputColour;

void main()
{
    //gl_FragColor = vec4(color, 1.0);
	
	pixelOutputColour = vec4(color, 1.0);
};