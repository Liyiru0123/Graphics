/* 
   basic_deprecated.cpp
   Basic GLFW3 Example 
   This is a full OpenGL compatability (using deprecated features) and GLFW example
   without shaders using fixed-pipeline.
   It should not be used for AC41001/AC51008 development but is instead used to show and discuss
   the deprected features (which we won't be using!).
   
   To build this source file in Visual Studio
	- Create lib and include directories
	- Copy the GLFW and GLLoad libs into the lib directory
	- Copy the GLLoad and GLFW headers into the include directory
	- Add the lib path to the VC++ lib directory (right click on project, then properties)
	- Add the include path to the VC++ include directory (right click on project, then properties)
	- Note that you may have to rebuild the libs from source if they don't work on
	  your system
   */

/* Link to static libraries, you could define these as linker inputs in the project settings instead
if you prefer */
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

/* Include standard libraries and the GLFW3 header*/
#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

/* Define a GLFW error callback to output errors to stderr 
   (standard error stream) */
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

/* Define a GLFW keyboard callback to process keyboard events */
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

/* Standard main function
   Initialise GLFW, create a window, register callbacks and run the event loop */
int main(void)
{
    GLFWwindow* window;

	/* Register an error callback */
    glfwSetErrorCallback(error_callback);

	/* Initialise GLFW */
    if (!glfwInit())
        exit(EXIT_FAILURE);

	/* Create a GLFW window 
	  http://www.glfw.org/docs/latest/group__window.html#ga5c336fddf2cbb5b92f65f10fb6043344 */
    window = glfwCreateWindow(640, 480, "Hello Graphics World (deprecated)", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

	/* Get an OpenGL context */
    glfwMakeContextCurrent(window);

	/* Register an error callback */
    glfwSetKeyCallback(window, key_callback);

	/* This is the event loop, loop forever until  */
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

		/* This section is deprecated OpenGL code */
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

		/* Defines a triangle using deprecated immediate mode */
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();

		/* Draw the scene by swapping the frame buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	/* Out of the event loop now so destroy the window to clean up */
    glfwDestroyWindow(window);
	/* Terminate GLFW */
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

