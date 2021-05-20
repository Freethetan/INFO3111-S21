#include "globalStuff.h"
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

//#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <vector>

#include "cShaderManager.h"

#include "cVAOManager.h"

#include "cMeshObject.h"





//static const struct
//{
//    float x, y;
//    float r, g, b;
//} vertices[3] =
//{
//    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
//    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
//    {   0.f,  0.6f, 0.f, 0.f, 1.f }
//};

struct sVertex
{
    float x, y, z;
    float r, g, b;
};


//sVertex vertices[3] =
//{
//    { -0.6f, -0.4f, 1.0f, 0.0f, 0.0f },    // v 0
//    {  0.6f, -0.4f, 0.0f, 1.0f, 0.0f },    // v 1
//    {  0.0f,  0.6f, 0.0f, 0.0f, 1.0f }     // v 3
//};


// bye bye evil hard coded model


// This will change the polygon mode at the render
bool g_DrawWireframe = false;

//static const char* vertex_shader_text =
//"#version 110\n"
//"uniform mat4 MVP;\n"
//"attribute vec3 vCol;\n"
//"attribute vec2 vPos;\n"
//"varying vec3 color;\n"
//"void main()\n"
//"{\n"
//"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
//"    color = vCol;\n"
//"}\n";
//
//static const char* fragment_shader_text =
//"#version 110\n"
//"varying vec3 color;\n"
//"void main()\n"
//"{\n"
//"    gl_FragColor = vec4(color, 1.0);\n"
//"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



// This is the TEMPORARY 'make the ply file a header' "quick and dirty" code
bool generateQnDHeaderFileFromPLY(std::string plyFileName, std::string headerFileName, unsigned int& numVertices);

int main(void)
{
    //// Convert the ply file to a header
    //unsigned int numVertices = 0;
    //if ( generateQnDHeaderFileFromPLY("assets/models/bun_zipper_res2.ply", "bunny.h", numVertices))
    //{
    //    std::cout << "OK!" << std::endl;
    //}
    //return 0;

    GLFWwindow* window = NULL;

    GLuint vertex_buffer = 0;

// These have been replaced by the shader manager class
//	GLuint vertex_shader = 0;
//	GLuint fragment_shader = 0;
//	GLuint program = 0;

//    GLint mvp_location = -1;		// Usually GLint -1 is "bad value"

	GLint vpos_location = -1;		// GLuint 0 is "bad value"
	GLint vcol_location = -1;



    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(1080, 640, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);


	// Make a shader manager
	cShaderManager* pShaderManager = new cShaderManager();

	cShaderManager::cShader vertShader;
	cShaderManager::cShader fragShader;

	vertShader.fileName = "assets/shaders/vertex_01.glsl";
	fragShader.fileName = "assets/shaders/frag_01.glsl";

	// Here we've called our shader program 'Basic'
	if (pShaderManager->createProgramFromFile("Basic", vertShader, fragShader))
	{
		std::cout << "Shaders are loaded and compiled" << std::endl;
	}
	else
	{
		std::cout << "Something went wrong: " << std::endl;
		std::cout << pShaderManager->getLastError() << std::endl;
	}

	GLuint program = 0;
	program = pShaderManager->getIDFromFriendlyName("Basic");


	cVAOManager* pVAOManager = new cVAOManager();


	// Load the models we want to (or might want to) eventually draw...
	// (i.e. load them into the GPU)

	sModelDrawInfo mdoBunny;
	if (pVAOManager->LoadModelIntoVAO("assets/models/bun_zipper_res2_xyz_rgba.ply",
									  mdoBunny, program))
	{
		std::cout << "Bunny model loaded OK" << std::endl;
	}

	
	sModelDrawInfo mdoCow;
	if (pVAOManager->LoadModelIntoVAO("assets/models/cow_xyz_rgba.ply",
									  mdoCow, program))
	{
		std::cout << "Cow model loaded OK" << std::endl;
	}

	sModelDrawInfo mdoTree;
	if (pVAOManager->LoadModelIntoVAO("assets/models/SM_Env_Mangrove_Tree_02_xyz_rgba.ply",
									  mdoTree, program))
	{
		std::cout << "Tree model loaded OK" << std::endl;
	}
	// Change the vertex array (locally)
//	struct sVertex
//	{
//		float x, y;
//		float r, g, b;
//	};
	// For each vertex
//	for (unsigned int index = 0; index != NUM_VERTICES_BUNNY; index++)
//	{
//		// WE ARE ONLY CHANGING ***ONE*** VERTEX AT A TIME
//		// This is literally what each vertex shader does.
//		vertices[index].y -= 0.11f;		// Got this number from MeshLap (centre location is 0.11 in the y)
//
//
//		vertices[index].x *= 6.0f;
//		vertices[index].y *= 6.0f;
//		vertices[index].z *= 6.0f;
//
//		// See if this is within a certain radius of the centre.
//		// This is using Pythagorean theorem, yo
//		float distance = sqrt( (vertices[index].x * vertices[index].x) + 
//			                   (vertices[index].y * vertices[index].y));
//
//		vertices[index].r = 0.0f;
//		vertices[index].g = 0.0f;
//		vertices[index].b = 1.0f;
//
//		if (distance < 0.1f)
//		{
//			vertices[index].r = 0.0f;
//			vertices[index].g = 1.0f;
//			vertices[index].b = 0.0f;
//		}
//
//
////		vertices[index].r = ((float)(rand() % 255))/255.0f;
////		vertices[index].g = ((float)(rand() % 255)) / 255.0f;
////		vertices[index].b = ((float)(rand() % 255)) / 255.0f;
//	}

//    // NOTE: OpenGL error checks have been omitted for brevity
// 	 The VAO Manager replaces this...
//   glGenBuffers(1, &vertex_buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
//    glCompileShader(vertex_shader);
//
//    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
//    glCompileShader(fragment_shader);
//
//    program = glCreateProgram();
//
//    glAttachShader(program, vertex_shader);
//    glAttachShader(program, fragment_shader);
//    glLinkProgram(program);


    vpos_location = glGetAttribLocation(program, "thePositionXYZ");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 
						  3, 
						  GL_FLOAT, 
						  GL_FALSE,
                          sizeof(sVertex),				//sizeof(vertices[0]), 
						  (void*)offsetof(sVertex, x));	// (void*)0);


	vcol_location = glGetAttribLocation(program, "theVertexColour");
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 
						  3, 
						  GL_FLOAT, 
						  GL_FALSE,	
						  sizeof(sVertex),					//sizeof(vertices[0]), 
						  (void*)offsetof(sVertex, r));		// (void*)(sizeof(float) * 2));


	// **********************************************************
	// All the objects to draw are here:
	std::vector<cMeshObject> vecMyModels;

	cMeshObject bunny;
	bunny.meshName = "assets/models/bun_zipper_res2_xyz_rgba.ply";
	bunny.scale = 6.430868167f;
	bunny.position.x = -1.0f;
	bunny.isWireframe = true;
	bunny.bUseVertexColours = false;
	bunny.wholeObjectColour = glm::vec4(1.0f, 0.0f, 0.5f, 1.0f);	// Bright hot pink
	vecMyModels.push_back(bunny);

	cMeshObject bunny2;
	bunny2.meshName = "assets/models/bun_zipper_res2_xyz_rgba.ply";
	bunny2.position.x = 1.0f;
	bunny2.scale = 6.430868167f;
	vecMyModels.push_back(bunny2);

	cMeshObject bunny3;
	bunny3.meshName = "assets/models/cow_xyz_rgba.ply";
	bunny3.position.y = -1.0f;
// This value would be taked from the sModelDrawInfo for *this* mesh.
// This would be calculated on the load
	float tempScaleOfOneForCowMesh = 0.096153846f;
	bunny3.scale = 1.0f * tempScaleOfOneForCowMesh;	// 		0.75f;
	bunny3.orientation.y = glm::radians(180.0f);		// Same as glm::pi  2PI radians = 360
	vecMyModels.push_back(bunny3);

	cMeshObject aTree;
	aTree.meshName = "assets/models/SM_Env_Mangrove_Tree_02_xyz_rgba.ply";
	aTree.position.y = -0.5f;
	aTree.position.x = -0.5f;

	aTree.bUseVertexColours = false;
	aTree.wholeObjectColour.r = 0.0f;
	aTree.wholeObjectColour.g = 1.0f;
	aTree.wholeObjectColour.b = 0.0f;

	float tempScaleOfOneForTreeMesh = 23.25581395f;
	aTree.scale = 2.0f * tempScaleOfOneForTreeMesh;		// 295.0f;
	vecMyModels.push_back(aTree);


	// **********************************************************


    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        //       mat4x4 m, p, mvp;
        glm::mat4 matModel;			// m;
		glm::mat4 matProjection;	// p;
		glm::mat4 matView;			// v;
		glm::mat4 mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width - 30, height - 30);

		// Clear the depth (or z) buffer, too
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		// Start the draw all the model loop
		for (unsigned int index = 0; index != vecMyModels.size(); index++)
		{
			// You could look up the mesh (model) right away...
			// 1) if the mesh isn't loaded, there's no point continuing 
			// 2) You might want some of the information (like the "scaleToOne" value)
			//
//			sModelDrawInfo mdoMeshToDraw;
//			if (pVAOManager->FindDrawInfoByModelName(vecMyModels[index].meshName,
//													 mdoMeshToDraw))


			//         mat4x4_identity(m);
			matModel = glm::mat4(1.0f);

			////mat4x4_rotate_Z(m, m, (float) glfwGetTime());
		
			int x = 1;
			int y = 123; 
			int z = 1;
			int total = x * y * z;

			glm::mat4 rotateX = glm::mat4(1.0f);	// Short for 'identity' matrix
			glm::mat4 rotateY = glm::mat4(1.0f);
			glm::mat4 rotateZ = glm::mat4(1.0f);
			glm::mat4 matScale = glm::mat4(1.0f);
			glm::mat4 matTranslate = glm::mat4(1.0f);	// Move

			// Make a copy of the current model (to make the later code simpler)
			cMeshObject currentObject = vecMyModels[index];


			// You could apply the mdoMeshToDraw.scaleOfOne here...
			float theScale = currentObject.scale;
			matScale = glm::scale(glm::mat4(1.0f), 
								  glm::vec3(theScale, theScale, theScale));

//			matTranslate = glm::translate(glm::mat4(1.0f), 
//										  glm::vec3(0.5f, 0.0f, 0.0f));
			matTranslate = glm::translate(glm::mat4(1.0f), 
										  glm::vec3(currentObject.position.x,
													currentObject.position.y,
													currentObject.position.z));
			

			rotateZ = glm::rotate(glm::mat4(1.0f),
								  currentObject.orientation.z,		// 11.7f, // (float)glfwGetTime(),
								  glm::vec3(0.0f, 0.0, 1.0f));


			rotateY = glm::rotate(glm::mat4(1.0f),
								  currentObject.orientation.y,		// (float)glfwGetTime(),
								  glm::vec3(0.0f, 1.0, 0.0f));


			rotateX = glm::rotate(glm::mat4(1.0f),
								  currentObject.orientation.x,		// -(float)glfwGetTime()/3.14f,
								  glm::vec3(1.0f, 0.0, 0.0f));


			// We can combine these to make "one matrix to rule them all"
			// i.e. 1 single matrix that does ALL of these transformation
			matModel = matModel * matTranslate;
			matModel = matModel * rotateZ;
			matModel = matModel * rotateY;
			matModel = matModel * rotateX;
			matModel = matModel * matScale;


			//		m = m * matTranslate * rotateZ * rotateY * rotateX * matScale;
			   
		
			//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
			matProjection = glm::perspective(0.6f,
											 ratio,
											 0.1f,
											 1000.0f);


			matView = glm::mat4(1.0f);

			//glm::vec3 g_CameraEye = glm::vec3(0.0, 0.0, -4.0f);
			//glm::vec3 g_CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

			glm::vec3 cameraEye = ::g_CameraEye;
			glm::vec3 cameraTarget = ::g_CameraTarget;
			glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

			matView = glm::lookAt(cameraEye,
								  cameraTarget,
								  upVector);


			glUseProgram(program);


			//mat4x4_mul(mvp, p, m);
			//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
			//GLint mvp_location = glGetUniformLocation(program, "MVP");
			//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
			
//			mvp = matProjection * matView * matModel;
//
//			uniform mat4 mProjection;
//			uniform mat4 mView;
//			uniform mat4 mModel;
			GLint mProjection_locID = glGetUniformLocation(program, "mProjection");
			glUniformMatrix4fv(mProjection_locID, 1, GL_FALSE, glm::value_ptr(matProjection));

			GLint mView_locID = glGetUniformLocation(program, "mView");
			glUniformMatrix4fv(mView_locID, 1, GL_FALSE, glm::value_ptr(matView));

			GLint mModel_locID = glGetUniformLocation(program, "mModel");
			glUniformMatrix4fv(mModel_locID, 1, GL_FALSE, glm::value_ptr(matModel));


			// Set the object colour 
			// uniform vec4 wholeObjCol;
			// uniform bool bVertCol;

			GLint bVertCol_locID = glGetUniformLocation(program, "bVertCol");
			if (currentObject.bUseVertexColours)
			{
				glUniform1i(bVertCol_locID, GL_TRUE);		
			}
			else
			{
				glUniform1i(bVertCol_locID, GL_FALSE);		
			}
			

			GLint wholeObjCol_locID = glGetUniformLocation(program, "wholeObjCol");
			glUniform4f(wholeObjCol_locID, 
						currentObject.wholeObjectColour.r,
						currentObject.wholeObjectColour.g,
						currentObject.wholeObjectColour.b,
						currentObject.wholeObjectColour.a );



			// This will set the rendering to Point, Line, or Fill 
			// (Fill is the default)
			if ( currentObject.isWireframe )
			{
				// Doesn't fill in the centres of the triangles
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

				glDisable(GL_DEPTH_TEST);
				// Turn OFF the face culling
				glDisable(GL_CULL_FACE);
			}
			else
			{
				// Normal rendering

				// Default "filled in" mode (fills in the triangles)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				// Turns on the depth test 
				glEnable(GL_DEPTH_TEST);
				// Don't bother drawing "back facing" triangles
				glCullFace(GL_BACK);		
				// Turn on the face culling
				glEnable(GL_CULL_FACE);
			}




	//        glDrawArrays(GL_TRIANGLES, 0, 3);
	//        glDrawArrays(GL_TRIANGLES, 28002, 48903);
			sModelDrawInfo mdoBunny;
//			if (pVAOManager->FindDrawInfoByModelName("assets/models/bun_zipper_res2_xyz_rgba.ply", 
//													 mdoBunny))

			if (pVAOManager->FindDrawInfoByModelName(vecMyModels[index].meshName,
													 mdoBunny))
			{
				// Set up the buffers, vertex layout, etc. for this model
				glBindVertexArray(mdoBunny.VAO_ID);

				glDrawElements(GL_TRIANGLES, mdoBunny.numberOfIndices, GL_UNSIGNED_INT, 0 );

				glBindVertexArray(0);
			}

		}//for (unsigned int index



        glfwSwapBuffers(window);

		// Grab the keyboard and mouse events
        glfwPollEvents();

		asyncKeyboardMouse(window);

    }

	// Clean up
	delete pShaderManager;

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
