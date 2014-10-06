//
//  ThePicker
//  Display.cpp
//
//  Helps handle display including keyboard
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "Display.h"
bool Display::boundDraw;

Display::Display(int width, int height, std::string title)
{
    boundDraw = false;
    const char * titleChar = title.c_str();
    
	// Initialize the library
	if (!glfwInit()){
        std::cerr << "GLFW failed to initiate" << std::endl;
    }

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(width, height, titleChar, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
        std::cerr << "Window failed" << std::endl;
	}
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, keyboardCallback);
    
	// Make the window's context current
	glfwMakeContextCurrent(window);
    
}


bool Display::isClosed()
{
    return glfwWindowShouldClose(window);
}


void Display::update()
{
    // Swap front and back buffers
    glfwSwapBuffers(window);
    
    // Poll for and process events
    glfwPollEvents();
}


void Display::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a); // makes background blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(0);
}

void Display::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if( action == GLFW_PRESS || action == GLFW_REPEAT ){
        switch( key ){
          case GLFW_KEY_ESCAPE:
          case GLFW_KEY_Q:
            glfwSetWindowShouldClose(window, GL_TRUE);;
            break;
          case GLFW_KEY_H:
            printf("Help Message\n");
            //printHelpMessage( );
            break;
          case GLFW_KEY_G:
            printf("Toggle between glsl and fixed pipeline\n");
            break;
          case GLFW_KEY_B:
            if (!boundDraw)
                boundDraw = true;
            else
                boundDraw = false;
            break;
          case GLFW_KEY_LEFT:
            printf("Camera Rotates Left\n");
            break;
          case GLFW_KEY_RIGHT:
            printf("Camera Rotates Right\n");
            break;
          case GLFW_KEY_UP:
            printf("Camera Rotates Up\n");
            break;
          case GLFW_KEY_DOWN:
            printf("Camera Rotates Down\n");
            break;
          default:
            fprintf( stderr, "You pushed '%c' (%d).\n", key, key );
            break;
        }
    }
}


Display::~Display()
{
    
}