
#include "ShaderStuff.hpp"

static void error_callback(int error, const char* description){ fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	glfwSetWindowShouldClose(window, GL_TRUE);

}

int main(void){

	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
	glfwTerminate();
	exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);

	// Create the shaders
	init();

	while(!glfwWindowShouldClose(window)){

		glClear( GL_COLOR_BUFFER_BIT );     // fills the window with the background color
		//glDrawArrays( GL_POINTS, 0, nvertices );    // draw a point at each vertex location
		//glDrawArrays( GL_LINES, 0, nvertices );    // draw a line between each vertex pair
		//glDrawArrays( GL_LINE_LOOP, 0, nvertices );    // draw a line between each successive vertex
		//glDrawArrays( GL_TRIANGLES, 0, nvertices );    // draw a triangle for each vertex triple
		glDrawArrays( GL_TRIANGLE_FAN, 0, nvertices );    // draw a triangle between the first vertex and each successive vertex pair
		glFlush();	

		{ // Handle events
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	} // end game loop

	// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

} // end main


