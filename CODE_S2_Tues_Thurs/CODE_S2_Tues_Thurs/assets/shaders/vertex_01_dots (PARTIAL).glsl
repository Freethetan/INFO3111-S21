#version 420

// Will place a dot on the bunny

uniform mat4 MVP;

attribute vec3 vCol;
attribute vec2 vPos;

varying vec3 color;

void main()
{
	vec2 newPos = vPos;
	newPos.y -= 0.11;
	
	newPos.x *= 6.0;
	newPos.y *= 6.0;
	
//	float distance = sqrt( (newPos.x * newPos.x) + (newPos.y * newPos.y) );
	
	vec2 myPoints[5] =  { { 0.0f, 0.0f },
	                      { 1.0f, 1.0f },... and so on
	
	newColour.r = 0.0;
	newColour.g = 0.0;	
	newColour.b = 1.0;
	
	for ( int index = 0; index < 5; index++ )
	{
		float dist = distance(newPos, myPoints[index]);
	
		vec3 newColour = vCol;

		if (dist < 0.1)
		{
			newColour.r = 0.0;
			newColour.g = 1.0;
			newColour.b = 0.0;
		}
	}


    gl_Position = MVP * vec4(newPos, 0.0, 1.0);
	
    color = newColour;	//vCol;
};

