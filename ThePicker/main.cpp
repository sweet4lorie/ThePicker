//
//  ThePicker
//  main.cpp
//
//  main file for ThePicker
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "Display.h"
#include "Sphere.h"
#include "Compound.h"
#include "Shader.h"
#include "dirent.h"

int window_height = 550;
int window_width = 650;
float const win_aspect = (float)window_width / (float)window_height;

// seteup Variables
static bool fixedDraw = false;
static bool boundDraw = false;

static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
Display display(window_width, window_height, "The Picker");

// Setup Objects
std::vector<Object> objList;
Object luff;
Object cube;

// Camera
Camera camera;
double * mouseXPress = new double;
double * mouseYPress = new double;
double * mouseXRelease = new double;
double * mouseYRelease = new double;
bool checkPress = false;
bool checkRelease = false;

int main(void)
{
    luff.setCompound("luff.obj");
    luff.scale(0.07);
    luff.translate(Vec3(-1.5, -0.6, -0.5));
    
    cube.setCompound("cube.obj");
    cube.translate(Vec3(0.6, -0.5, -0.5));
    cube.scale(0.5);
    
    objList.push_back(luff);
    objList.push_back(cube);

    Shader shader("objShader");
    Shader bbxShader("bbxShader");
    
    glfwSetKeyCallback(display.window, keyboardCallback);
    
	// Loop until the user closes the window
	while (!display.isClosed())
	{
        // Camera
        camera.setupCamera(win_aspect);
        
        // Mouse checks
        // only set if just released; order of checks matters
        if (GLFW_RELEASE == glfwGetMouseButton(display.window, GLFW_MOUSE_BUTTON_1) && checkPress)
        {
            glfwGetCursorPos(display.window, mouseXRelease, mouseYRelease);
            //std::cout<< "mouse released : " << *mouseXRelease << " " << *mouseYRelease << std::endl;
            checkRelease = true;
        }
        else
        {
            checkRelease = false;
        }
        if (GLFW_PRESS == glfwGetMouseButton(display.window, GLFW_MOUSE_BUTTON_1))
        {
            glfwGetCursorPos(display.window, mouseXPress, mouseYPress);
            checkPress = true;
        }
        else
        {
            checkPress = false;
        }
        
        // Background color
        display.clear(0.0f, 0.0f, 0.0f, 1.0f);

        // Render Objects
        for(int i = 0; i < objList.size(); i++)
        {
            // Shaders
            if (fixedDraw)
                shader.bindFixed();
            else
                shader.bind();
            
            
            // Object is hit
            glfwGetCursorPos(display.window, mouseXPress, mouseYPress);
            if (GLFW_PRESS == glfwGetMouseButton(display.window, GLFW_MOUSE_BUTTON_1) &&
				objList[i].hit(camera.getRay(window_width, window_height, float(*mouseXPress), float(*mouseYPress))))
            {
                shader.setColor(1.0, 1.0, 1.0, 1.0);
            }
            // cull object
            else if (!objList[i].inView(camera.myProjection, camera.myModelView))
                shader.setColor(1.0, 1.0, 1.0, 0.0);
            // Object is not hit
            else
                shader.setColor(1.0, 0.5, 0.0, 1.0);
            
            // Draw and Shade each object individually
            shader.update(camera, objList[i]);
            objList[i].draw();
            
            // == bounding boxes
            // Shaders
            if (boundDraw)
            {
                if (fixedDraw)
                    bbxShader.bindFixed();
                else
                    bbxShader.bind();
                bbxShader.setColor(1.0, 0.0, 0.0, 1.0);
                bbxShader.update(camera, objList[i]);
                objList[i].draw("bound");
            }
        }
        // Switch buffer and polling
		display.update();
	}
 
    display.destroy();
	return 0;
}


void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if( action == GLFW_PRESS || action == GLFW_REPEAT ){
        switch( key ){
          case GLFW_KEY_ESCAPE:
          case GLFW_KEY_Q:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
          case GLFW_KEY_H:
            printf("Help Message\n");
            // help message
            break;
          case GLFW_KEY_G:
            // fixed draw
            if (!fixedDraw)
                fixedDraw = true;
            else
                fixedDraw = false;
            break;
          case GLFW_KEY_B:
            // draw bounding
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

