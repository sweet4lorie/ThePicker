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

Display::Display(int width, int height, std::string title)
{
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

Display::~Display()
{
    
}