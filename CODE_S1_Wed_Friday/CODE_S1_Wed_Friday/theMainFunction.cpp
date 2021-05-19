#include "globalStuff.h"
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
// 
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
#include <string>
#include <iostream>
#include <vector>

#include "cShaderManager.h"

#include "cVAOManager.h"    // Manages meshes, etc.

#include "cMeshObject.h"

//struct sVertex
//{
//    float x, y, z;
//    float r, g, b;
//};
//
//const unsigned int NUM_VERTICES = 48903;
//
//sVertex vertices[NUM_VERTICES] =
////{
////    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
////    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
////    {   0.f,  0.6f, 0.f, 0.f, 1.f }
////};



bool g_IsWireframe = false;

glm::vec3 g_cameraEye = glm::vec3(0.0, 0.0, -4.0f);
glm::vec3 g_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);


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

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == '1')
	{
		std::cout << "Switching to wireframe" << std::endl;
		::g_IsWireframe = true;
	}
	if (key == '2')
	{
		std::cout << "Switching to solid fill" << std::endl;
		::g_IsWireframe = false;
	}

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void doKeyboardMouseStuffAsync(GLFWwindow* window)
{
    float cameraSpeed = 0.1f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        ::g_cameraEye.x -= cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        ::g_cameraEye.z += cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        ::g_cameraEye.z -= cameraSpeed;
    }
    return;
}

bool generateQnDHeaderFileFromPLY(std::string plyFileName,
                                  std::string headerFileName,
                                  unsigned int& numVertices);

int main(void)
{
    //unsigned int numVertices = 0;
    //if (generateQnDHeaderFileFromPLY("assets/models/bun_zipper_res2.ply",
    //                                 "theBunny.h", numVertices))
    //{
    //    std::cout << "Duun!" << std::endl;
    //}
    //else
    //{
    //    std::cout << "oh no..." << std::endl;
    //}
    //return 0;



    GLFWwindow* window = NULL;	// or 0 or nullptr

    GLuint vertex_buffer = 0;
	//GLuint vertex_shader = 0;
	//GLunit fragment_shader = 0;
	GLuint program = 0;

    //GLint mvp_location = 0;
	GLint vpos_location = 0;
	GLint vcol_location = 0;

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

//	// Change the bunny model (in RAM) before it's copied up
//	for (unsigned int index = 0; index != NUM_VERTICES; index++)
//	{
//		//struct sVertex {
//		//	float x, y;
//		//	float r, g, b;
//		//};
//		float scale = 4.0f;
//		float xOffset = 0.0f;
//		float yOffset = -0.3f;		// Centre is -0.11, so a little more and it takes into account scaling
//		float roation = 13.0f;
//		
		//vertices[index].x *= scale;
		//vertices[index].y *= scale;
//
		//vertices[index].x += xOffset;
		//vertices[index].y += yOffset;		
//
		//vertices[index].r = 0.0f;
		//vertices[index].g = 0.0f;
		//vertices[index].b = 0.0f;
//
		//// Assume a point at the origin
		//// See if the vertex is within a certain distance from that.
//
		//// sqrt(X ^ 2 + y ^ 2)
		//float distance = sqrt( (vertices[index].x * vertices[index].x) + 
		//					   (vertices[index].y * vertices[index].y) );
//
//		if (distance > 0.1f)
//		{
//			// Outside the circle
//			vertices[index].g = 1.0f;
//		}
//		else
//		{
//			// Inside the circle
//			vertices[index].b = 1.0f;
//		}
//
//
////		if (vertices[index].x > 0.0f)
////		{
////			vertices[index].r = 1.0f;
////		}
////		else
////		{
////			vertices[index].b = 1.0f;
////		}
//
////		vertices[index].x += sin(13.0f);
////		vertices[index].y += cos(13.0f);	  Euler	
//
//	}

	// OpenGL is ready to go...

	cShaderManager* pShaderManager = new cShaderManager();

	cShaderManager::cShader myVertexShader;
	cShaderManager::cShader myFragmentShader;

	pShaderManager->setBasePath("assets/shaders/");

	myVertexShader.fileName = "myVertShad.glsl";
	myFragmentShader.fileName = "myFragShad.glsl";

	if (pShaderManager->createProgramFromFile("SimpleShader",
											  myVertexShader,
											  myFragmentShader))
	{
		std::cout << "Compiled the shader program OK" << std::endl;
	}
	else
	{
		std::cout << "Oh NO!: Here's why: " << pShaderManager->getLastError() << std::endl;
	}


	// What's the name of our shader
	program = pShaderManager->getIDFromFriendlyName("SimpleShader");

    
    cVAOManager* pVAOMan = new cVAOManager();

    sModelDrawInfo mdoBunny;
    if (pVAOMan->LoadModelIntoVAO("assets/models/bun_zipper_res2_xyz_rgba.ply",
                                  mdoBunny, program))
    {
        std::cout << "Bunny loaded OK" << std::endl;
        std::cout << "Has: " << mdoBunny.numberOfVertices << " vertices" << std::endl;
    }

    sModelDrawInfo mdoFish;
    pVAOMan->LoadModelIntoVAO("assets/models/PacificCod0_xyz_rgba.ply",mdoFish, program);


    sModelDrawInfo mdoEagleShaceShip;
    pVAOMan->LoadModelIntoVAO("assets/models/Eagle_xyz_rgba.ply", mdoEagleShaceShip, program);


    // NOTE: OpenGL error checks have been omitted for brevity
//    glGenBuffers(1, &vertex_buffer);
 //   glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
 //   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //glCompileShader(vertex_shader);
//
    //fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //glCompileShader(fragment_shader);
//
    //program = glCreateProgram();
//
    //glAttachShader(program, vertex_shader);
    //glAttachShader(program, fragment_shader);
    //glLinkProgram(program);




//	vpos_location = glGetAttribLocation(program, "vPos");
//    glEnableVertexAttribArray(vpos_location);
//    glVertexAttribPointer(vpos_location, 
//						  3, 
//						  GL_FLOAT, 
//						  GL_FALSE,
//                          sizeof(sVertex),					// sizeof(vertices[0]),
//						  (void*)offsetof(sVertex, x) );	//  (void*)0);
//
//
//	vcol_location = glGetAttribLocation(program, "vCol");
//	glEnableVertexAttribArray(vcol_location);
//    glVertexAttribPointer(vcol_location, 
//						  3, 
//						  GL_FLOAT, 
//						  GL_FALSE,
//						  sizeof(sVertex),					// sizeof(vertices[0]), 
//						  (void*)offsetof(sVertex, r));	//  (void*)(sizeof(float) * 2));


    std::vector<cMeshObject> vecObjectsToDraw;

    cMeshObject bunny;
    bunny.meshName = "assets/models/bun_zipper_res2_xyz_rgba.ply";
    bunny.scale = 6.43f;        // makes it fit into a 1x1x1 box
    bunny.position.x = 1.0f;
    bunny.orientation.y = 0.5f;
    bunny.orientation.z = 0.1f;

    bunny.wholeObjectColour = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);
    bunny.bUseWholeObjectColour = true;

    vecObjectsToDraw.push_back(bunny);




    cMeshObject spaceShip;
    spaceShip.meshName = "assets/models/Eagle_xyz_rgba.ply";
    spaceShip.scale = 0.03994727f;      // Fits into a 1x1x1 box
    spaceShip.position.y = -0.5f;

    spaceShip.wholeObjectColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    spaceShip.bUseWholeObjectColour = true;

    vecObjectsToDraw.push_back(spaceShip);

    cMeshObject spaceShip2;
    spaceShip2.meshName = "assets/models/Eagle_xyz_rgba.ply";
    spaceShip2.scale = 0.03994727f * 2.0f;      // Fits into a 1x1x1 box
    spaceShip2.position.y = 0.75f;

    spaceShip2.wholeObjectColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    spaceShip2.bUseWholeObjectColour = true;

    vecObjectsToDraw.push_back(spaceShip2);

    //cMeshObject fish;
    //fish.meshName = "assets/models/PacificCod0_xyz_rgba.ply";
    //fish.scale = 3.0f;
    //fish.orientation.x = glm::radians(90.0f);       // PI div 2
    //vecObjectsToDraw.push_back(fish);



    // This loop draws "the scene" over and over again

    while ( ! glfwWindowShouldClose(window) )
    {
        float ratio;
        int width, height;
        //       mat4x4 m, p, mvp;
        
        glm::mat4 matModel;
        glm::mat4 matProjection;        // p
        glm::mat4 matView;              // v
//        glm::mat4 matMVP;


        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);

//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

         
        // Draw all the things
        for (unsigned int index = 0; index != vecObjectsToDraw.size(); index++)
        {
            // Get the current mesh to draw from the vector
            cMeshObject curMesh = vecObjectsToDraw[index];

//            // Get the drawing information of this model right away
//            sModelDrawInfo mdoMesh;
//            if (!pVAOMan->FindDrawInfoByModelName(curMesh.meshName,
//                                                  mdoMesh))
 //           {
 //               // We're outta here
 //               continue;
//            }

            //         mat4x4_identity(m);
            matModel = glm::mat4(1.0f);     // Make an identity matrix

            glm::mat4 matRotateZ;
            glm::mat4 matRotateY;
            glm::mat4 matRotateX;
            glm::mat4 matScale;
            glm::mat4 matTranslate;         // Move

            matRotateZ = glm::rotate(glm::mat4(1.0f),
                                     curMesh.orientation.z,    // (float)glfwGetTime(),
                                     glm::vec3(0.0f, 0.0f, 1.0f));

            matRotateY = glm::rotate(glm::mat4(1.0f),
                                     curMesh.orientation.y,    // (float)glfwGetTime(),
                                     glm::vec3(0.0f, 1.0, 0.0f));

            matRotateX = glm::rotate(glm::mat4(1.0f),
                                     curMesh.orientation.x,    // (float)glfwGetTime(),
                                     glm::vec3(1.0f, 0.0, 0.0f));

            float uniformScale = curMesh.scale;
//           float uniformScale = curMesh.scale * mdoMesh.scaleFor1x1x1BB;

            matScale = glm::scale(glm::mat4(1.0f), glm::vec3(uniformScale, uniformScale, uniformScale));
        
            matTranslate = glm::translate(glm::mat4(1.0f), 
                                          glm::vec3(curMesh.position.x, 
                                                    curMesh.position.y, 
                                                    curMesh.position.z));

            // Combine all the matrices to one final matrix that does ALL the transformations
            matModel = matModel * matTranslate;
            matModel = matModel * matRotateX;
            matModel = matModel * matRotateY;
            matModel = matModel * matRotateZ;
            matModel = matModel * matScale;
 
            //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            matProjection = glm::perspective(0.6f,
                                             ratio,
                                             0.1f,
                                             1000.0f);

            matView = glm::mat4(1.0f);

            glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

            matView = glm::lookAt(::g_cameraEye,
                                  ::g_cameraTarget,
                                  upVector);

            //mat4x4_mul(mvp, p, m);
//            matMVP = matProjection * matView * matModel;

            // 0 and whatever (-1 means "didn't find it")
//            GLint mvp_location = glGetUniformLocation(program, "MVP");
//            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(matMVP));

            GLint mView_UniLocID = glGetUniformLocation(program, "mView");
            glUniformMatrix4fv(mView_UniLocID, 1, GL_FALSE, glm::value_ptr(matView));

            GLint mModel_UniLocID = glGetUniformLocation(program, "mModel");
            glUniformMatrix4fv(mModel_UniLocID, 1, GL_FALSE, glm::value_ptr(matModel));

            GLint mProj_UniLocID = glGetUniformLocation(program, "mProj");
            glUniformMatrix4fv(mProj_UniLocID, 1, GL_FALSE, glm::value_ptr(matProjection));


//            uniform vec4 wholeObjCol;
//            uniform bool bUseVertColour;

            GLint wholeObjCol_UniLocID = glGetUniformLocation(program, "wholeObjCol");
            glUniform4f(wholeObjCol_UniLocID, 
                        curMesh.wholeObjectColour.r, 
                        curMesh.wholeObjectColour.g,
                        curMesh.wholeObjectColour.b,
                        curMesh.wholeObjectColour.a);


            GLint bUseVertColour_UniLocID = glGetUniformLocation(program, "bUseVertColour");

            if (curMesh.bUseWholeObjectColour)
            {
                glUniform1i(bUseVertColour_UniLocID, GL_FALSE);
            }
            else
            {
                glUniform1i(bUseVertColour_UniLocID, GL_TRUE);
            }




            glUseProgram(program);


		    if ( ::g_IsWireframe )
		    {
			    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		    }
		    else
		    {
			    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		    }

		    // Enable depth checking when drawing
		    glEnable(GL_DEPTH_TEST);
		    // Don't draw "back facing" triangles
		    glCullFace(GL_BACK);



     //       glDrawArrays(GL_TRIANGLES, 0, 3);
     //       glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);

            sModelDrawInfo mdoMesh;
            if (pVAOMan->FindDrawInfoByModelName(curMesh.meshName,
                                                 mdoMesh) )
            {
                glBindVertexArray(mdoMesh.VAO_ID);

                glDrawElements(GL_TRIANGLES, mdoMesh.numberOfIndices, GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);
            }

        }//for (unsigned int index

        // Presents whatever we've drawn to the screen
        // ALl done drawing
        glfwSwapBuffers(window);

        // Do all the mouse, keyboard, whatever updates
        glfwPollEvents();

        doKeyboardMouseStuffAsync(window);

    }

	// Clean up what we made...
	delete pShaderManager;
    delete pVAOMan;

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
