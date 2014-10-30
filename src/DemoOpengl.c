#include "DemoOpengl.h"

#include "GameState.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "ShaderHandler.h"
#include "Camera.h"
#include "Matrix.h"
#include "Model.h"

/* Variables d'evenement */
static SDL_Event event; // Gestionnaire d'evenement
static int Keys[256] = {0}; // 0 Key up | 1 Key Down
static int mouseX, mouseY;

static SDL_GLContext openglContext; // Context Opengl
static void S_DemoOpengl_Resized(void);	// Redimentionnement de la fenetre. A conserver


/* Model de la scene */
Model Model_Triangle;

static void MiniTest(void)
{
	MODEL_TEST_Triangle(&Model_Triangle);
// teste des matrice

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
	SDL_GL_SetSwapInterval(1);
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
	//glEnable(GL_CULL_FACE);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	CAM_Init();

	MiniTest();

	return 0;
}

void S_DemoOpengl_Quit(void)
{
	SDL_GL_DeleteContext(openglContext);
}

void S_DemoOpengl_Resized(void)
{
	SDL_GetWindowSize(Window, &WINDOWS_W, &WINDOWS_H);
	CAM_RebuildProjection();
}

void S_DemoOpengl_Event(void)
{
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_KEYDOWN)
			Keys[event.key.keysym.sym] = 1;
		if(event.type == SDL_KEYUP)
			Keys[event.key.keysym.sym] = 0;
		if(Keys[SDLK_ESCAPE])	// priorité a la sortie
			_ExitGame();
	}

	// Evenements
	if(Keys[SDLK_z] == 1)
		CAM_Forward(0.1f);

	if(Keys[SDLK_s] == 1)
		CAM_Forward(-0.1f);

	if(Keys[SDLK_d] == 1)
		CAM_Right(0.1f);

	if(Keys[SDLK_q] == 1)
		CAM_Right(-0.1f);
}

void S_DemoOpengl_Compute(void)
{
	SDL_GetRelativeMouseState(&mouseX, &mouseY);
	CAM_Yaw((float)mouseX);
	CAM_Pitch((float)mouseY);
}

void S_DemoOpengl_Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	MODEL_Display(&Model_Triangle);


	glFlush();
	SDL_GL_SwapWindow(Window);
}
