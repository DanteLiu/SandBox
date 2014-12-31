// glewtest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#pragma comment(lib,"glew32.lib")

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>

#include "shader.h"

int main(int argc, CHAR* argv[])
{
	glutInitWindowSize(500,500);
	glutInitWindowPosition(140,140);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInit(&argc,argv);
	glutCreateWindow("Hello world");

	if(glewInit() == GLEW_OK)
		printf("glewInit OK!\n\n");

	printf("OpenGL version: %s\n",glGetString(GL_VERSION));
	printf("GLSL version: %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));


	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );


	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//GL_STATIC_DRAW: allocated buffer will not modify!

	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );

	// Use our shader
	glUseProgram(programID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);

	// Swap buffers
	glutSwapBuffers();
		

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	
	glutMainLoop();
	return 0;
}

