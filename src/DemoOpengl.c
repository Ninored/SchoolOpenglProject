#include "DemoOpengl.h"

#include "GameState.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "ShaderHandler.h"
#include "Matrix.h"

static SDL_Event event;
static SDL_GLContext openglContext;
static void S_DemoOpengl_Resized(void);

static Shader shaderPrincipal;
/* TEST */
static GLfloat vertex[9] = {
	-1.0f,-1.0f,0.0f,
	1.0f,-1.0f,0.0f,
	0.0f,1.0f,0.0f
};

static GLfloat color[9] = {
	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f
};

static GLuint vbo = 0;
static GLuint vao = 0;
static GLuint vco = 0;

static void MiniTest(void)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vco);
	glBindBuffer(GL_ARRAY_BUFFER, vco);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vco);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	SH_Load(&shaderPrincipal, "./Assets/Shader/Default.vs", "./Assets/Shader/Default.fs");



	Mat4f matriceA;
	Mat4f matriceB;
	Mat4f matriceC;

	matriceA[0][0] = 1;
	matriceA[0][1] = 2;
	matriceA[0][2] = 2;
	matriceA[0][3] = 0;

	matriceA[1][0] = 2;
	matriceA[1][1] = 1;
	matriceA[1][2] = 1;
	matriceA[1][3] = 0;

	matriceA[2][0] = 4;
	matriceA[2][1] = 6;
	matriceA[2][2] = 5;
	matriceA[2][3] = 0;

	matriceA[3][0] = 7;
	matriceA[3][1] = 9;
	matriceA[3][2] = 8;
	matriceA[3][3] = 0;
//
	matriceB[0][0] = 5;
	matriceB[0][1] = 6;
	matriceB[0][2] = 7;
	matriceB[0][3] = 0;

	matriceB[1][0] = 2;
	matriceB[1][1] = 5;
	matriceB[1][2] = 6;
	matriceB[1][3] = 0;

	matriceB[2][0] = 1;
	matriceB[2][1] = 9;
	matriceB[2][2] = 5;
	matriceB[2][3] = 0;

	matriceB[3][0] = 6;
	matriceB[3][1] = 4;
	matriceB[3][2] = 7;
	matriceB[3][3] = 0;
	MAT_Identity(matriceC);
	MAT_Mult(matriceC, matriceA, matriceB);
	MAT_Print(matriceC);

}



int S_DemoOpengl_Init(void)
{
	// paramettrage des variables pour opengl
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // utilisation du double buffering 
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);	// taille de tempon de profondeur : 24
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Version Majeur OPENGL 3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2); // Version Mineur OPENGL 2

	// creation du context OPENGL
	openglContext = SDL_GL_CreateContext(Window);


	// Rendu: 1=VSync 0=Direct
	SDL_GL_SetSwapInterval(0);
	printf("\n\n");
	printf("#################################################\n");
	printf("[INFO]\tOPENGL_Version: %s\n", glGetString(GL_VERSION));
	printf("[INFO]\tOPENGL_Renderer: %s\n", glGetString(GL_RENDERER));
	printf("#################################################\n");

	// initialisation de glew
	glewExperimental = GL_TRUE; // Drivers expérimental uniquement 
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		printf("[ERROR]\tError while loading GLEW: %s\n", glewGetErrorString(err));
		return -1;
	}

	glEnable(GL_DEPTH_TEST); // gestion de la profondeur ZBuffer

	MiniTest();

	return 0;
}

void S_DemoOpengl_Quit(void)
{
	SDL_GL_DeleteContext(openglContext);
}

void S_DemoOpengl_Resized(void)
{
	// TODO: refaire la matrice de perspective
	SDL_GetWindowSize(Window, &WINDOWS_W, &WINDOWS_H);
}

void S_DemoOpengl_Event(void)
{
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				_ExitGame();
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					_ExitGame();
					break;
				}
				break;
			case SDL_WINDOWEVENT:
				if(event.window.event == SDL_WINDOWEVENT_RESIZED)
					S_DemoOpengl_Resized();
				break;
		}		
	}
}

void S_DemoOpengl_Compute(void)
{

}

void S_DemoOpengl_Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glUseProgram(shaderPrincipal.shaderID);
	glBindVertexArray(vao);
	int size;  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawArrays(GL_TRIANGLES, 0, ((size) / sizeof(GL_FLOAT)));
	glBindVertexArray(0);


	glFlush();
	SDL_GL_SwapWindow(Window);
}
