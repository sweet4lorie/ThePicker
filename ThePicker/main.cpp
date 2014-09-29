#include "Display.h"
#include "Sphere.h"
#include "Compound.h"
#include "Shader.h"
#include "dirent.h"

int window_height = 700;
int window_width = 700;

Display display(window_width, window_height, "The Picker");

int main(void)
{
    // Setup Objects
    Compound luff("luff.obj");
    //Compound cube("cube.obj");
    //Sphere sphere(0.5, 10, 10);
    
    luff.scale(.05);
    luff.translate(0, -0.7, -1);
    //cube.scale(.5);
    //cube.translate(-0.8, -0.5, -1);
    //sphere.translate(0.5, 0, -1);
    
    Shader shader("shader");
    Shader shader_red("shader");
    
	// Loop until the user closes the window
	while (!display.isClosed())
	{
        // Background color
        display.clear(0.0f, 0.0f, 1.0f, 1.0f);
        
		// Shaders
        shader.bind();
        shader.setColor(1.0, 0.5, 0.0, 1.0);
        
        // Render Objects
        //cube.setBuffer();
        //cube.draw();
        
        luff.draw();
        if (display.boundDraw)
        {
            shader_red.bind();
            shader_red.setColor(1.0, 0.0, 0.0, 1.0);
            luff.draw("bound");
        }
        
        //sphere.draw();
        
        // Switch buffer and polling
		display.update();
	}
 
    display.destroy();
	return 0;
}
