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
#include "Texture.h"
//#include "dirent.h"

int window_height = 550;
int window_width = 650;
float const win_aspect = (float)window_width / (float)window_height;

// seteup Variables
static bool fixedDraw = false;
static bool boundDraw = false;
static bool cameraReset = false;
bool hit = true;

Display display(window_width, window_height, "The Picker");
static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void helpMessage();

// Setup Objects
std::vector<Object> objList;
Object luff;
Object cube;
Object tiger;

// Camera
Vec3 eyePosition = {0.0, 0.0, 2.0};
Vec3 upVector = {0.0, 1.0, 0.0};
Camera camera (eyePosition, upVector);
double * mouseXStart = new double;
double * mouseYStart = new double;
double * mouseXEnd = new double;
double * mouseYEnd = new double;
double * mouseX = new double;
double * mouseY = new double;
bool checkPress = false;
bool checkRelease = false;

int main(void)
{
    tiger.setCompound("Tiger.obj");
    tiger.scale(0.00035);
    tiger.translate(Vec3(-0.6, -0.3, -0.5));
    
    luff.setCompound("luff.obj");
    luff.scale(0.07);
    luff.translate(Vec3(0.2, -0.6, -0.5));
    
    cube.setCompound("cube.obj");
    cube.translate(Vec3(0.7, -0.5, -0.5));
    cube.scale(0.5);
    
    objList.push_back(tiger);
    objList.push_back(luff);
    objList.push_back(cube);

    Shader shader("textShader");
    Shader obj("objShader");
    Shader bbxShader("bbxShader");
    Texture texture("granite_128.png");
    Vec4 color;
    
    glfwSetKeyCallback(display.window, keyboardCallback);
    
	// Loop until the user closes the window
	while (!display.isClosed())
	{
        // Camera
        camera.setupCamera(win_aspect);
        if (cameraReset == true)
        {
            camera.reset(eyePosition, upVector);
            cameraReset = false;
        }
        
        // Mouse checks
        if (GLFW_PRESS == glfwGetMouseButton(display.window, GLFW_MOUSE_BUTTON_1) and GLFW_PRESS == glfwGetKey(display.window, GLFW_KEY_LEFT_SHIFT))
        {
            if (mouseYStart)
            {
                glfwGetCursorPos(display.window, mouseXEnd, mouseYEnd);
                camera.rotate(*mouseXStart, *mouseYStart, *mouseXEnd, *mouseYEnd, window_height);
            }
            else
            {
                glfwGetCursorPos(display.window, mouseXEnd, mouseYEnd);
            }
        }
        
        // Background color
        display.clear(0.0f, 0.0f, 0.0f, 1.0f);

        // Render Objects
        for(int i = 0; i < objList.size(); i++)
        {
            // Object is hit
            glfwGetCursorPos(display.window, mouseX, mouseY);
            if (GLFW_PRESS == glfwGetMouseButton(display.window, GLFW_MOUSE_BUTTON_1) &&
                GLFW_PRESS != glfwGetKey(display.window, GLFW_KEY_LEFT_SHIFT) &&
				objList[i].hit(camera.getRay(window_width, window_height, float(*mouseX), float(*mouseY))))
            {
                color = Vec4(1.0, 1.0, 1.0, 1.0);
                hit = true;
            }
            // cull object
            else if (!objList[i].inView(camera.myProjection, camera.myModelView))
                color = Vec4(0.0, 0.0, 0.0, 0.0); // black
            // Object is not hit
            else
            {
                color = Vec4(1.0, 0.5, 0.0, 1.0);
                hit = false;
            }
            
            // Shaders
            if (fixedDraw)
            {
                texture.bind();
                obj.bindFixed();
            }
            else
            {
                if(i == 1)
                {
                    texture.bind();
                    shader.bind();
                    shader.setColor(color._x, color._y, color._z, color._w);
                    shader.update(camera, objList[i]);
                }
                else
                {
                    obj.bind();
                    obj.setColor(color._x, color._y, color._z, color._w);
                    obj.update(camera, objList[i]);
                }
            }

            // Draw and Shade each object individually
            objList[i].draw();

            // == bounding boxes
            // Shaders
            if (boundDraw || hit == true)
            {
                if (fixedDraw)
                {
                    bbxShader.bindFixed();
                }
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

void helpMessage()
{
    printf("Help:\n\t click + shift: rotate camera (error: rotates one direction) \
                    \t r: reset camera orientation to default state \
                    \t b: toggle rendering the bounding volumes \
                    \t g: toggle between my GLSL program and teh fixed function pipeline (error: not working) \
                    \t h: print help message \
                    \t q: quit \
                    \t esc: escape\n");
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
            helpMessage();
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
          case GLFW_KEY_R:
                cameraReset = true;
                std::cout << "reset";
            break;
          default:
            fprintf( stderr, "You pushed '%c' (%d).\n", key, key );
            break;
        }
    }
}

