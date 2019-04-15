#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Render.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
//#include "Texture.h"

//********************************************************************//
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 768, "Making this shit happen", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); //uses monitor refresh rate to smooth transitions between calls

	//make glewinit AFTER glfwMakecontextCurrent
	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;

	//prints what version of OpenGL and video card driver/manufacturer
	std::cout << glGetString(GL_VERSION) << std::endl;


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	//create a scope for the while loop
	//{
		//positions array of float
		//3 vertex positions
		float positions[] = {
			/*-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
*/
		   - 0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indicies[] = {
			0, 1, 2,
			2, 3, 0
		};

		//create VAO


		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 *sizeof(float));
		//VertexBuffer vb(positions, 4 *  * sizeof(float));  //updated to 4 * FOUR to account for texture positons

		VertexBufferLayout layout;
		layout.Push<float>(2);
		//layout.Push<float>(2);	//did after adding texture positions to positions[]
		va.AddBuffer(vb, layout);


		IndexBuffer ib(indicies, 6);


		//bound shader
		Shader shader("res/shaders/Shader.shader");
		shader.Bind();

		//uniforms
		shader.SetUniform4f("u_Color", 0.0f, 0.8f, 0.8f, 1.0f);

		//Texture texture("res/textures/syl.png");
		//texture.Bind();
		//shader.SetUniform1i("u_Texture", 0);

		

		//clear all bindings
		va.UnBind();
		vb.UnBind();
		ib.UnBind();
		shader.UnBind();

		Render render;


		float r = 0.0f;
		float increment = 0.05f;

		//********************************************************************//
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			render.Clear();

			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.8f, 0.8f, 1.0f);

			render.Draw(va, ib, shader);
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			//glDrawElements(GL_TRIANGLES, 3, )	//index buffers


			//alternating the color

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;


			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();

		//}
		//// Check if the ESC key was pressed or the window was closed
		//while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		//	glfwWindowShouldClose(window) == 0);

	}

	glfwTerminate();
	return 0;
}