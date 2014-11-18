#include "DemoOpengl.h"

#include "GameState.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "ShaderHandler.h"
#include "Camera.h"
#include "Matrix.h"
#include "Model.h"
#include "Light.h"

/* Variables d'evenement */
static SDL_Event event; // Gestionnaire d'evenement
static int Keys[512] = {0}; // 0 Key up | 1 Key Down
static int mouseX, mouseY;

static SDL_GLContext openglContext; // Context Opengl

/* Model de la scene */
Light Light_Test;
Model Model_Torus;
Model Model_Ground;

int S_DemoOpengl_Init(void)
{
	// paramettrage des variables pour opengl
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // utilisation du double buffering 
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);	// taille de tempon de profondeur : 24
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Version Majeur OPENGL 3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2); // Version Mineur OPENGL 2
 	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// creation du context OPENGL
	openglContext = SDL_GL_CreateContext(Window);

	// Rendu: 1=VSync 0=Direct
	SDL_GL_SetSwapInterval(1);

	printf("\n\n");
	printf("#################################################\n");
	printf("[INFO]\tOPENGL_Version: \t%s\n", glGetString(GL_VERSION));
	printf("[INFO]\tOPENGL_Renderer: \t%s\n", glGetString(GL_RENDERER));
	printf("#################################################\n");

	// initialisation de glew
	glewExperimental = GL_TRUE; // Drivers expérimental uniquement 
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		printf("[ERROR]\tError while loading GLEW: %s\n", glewGetErrorString(err));
		return -1;
	}

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST); // gestion de la profondeur ZBuffer
	//glEnable(GL_CULL_FACE);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	
	CAM_Init();

	// Chargement des models
	MODEL_Load(&Model_Torus, &Light_Test, "./Assets/obj/Torus.obj", "./Assets/Shader/Default.vs", "./Assets/Shader/Default.fs");
	MODEL_Load(&Model_Ground, &Light_Test, "./Assets/obj/Ground.obj", "./Assets/Shader/Default.vs", "./Assets/Shader/Default.fs");
	LIGHT_Create(&Light_Test, 1.2f,1,2,
							0,0,0,
							0.3f,0.3f,0.3f,
							0.3f,0.3f,0.3f,
							0.3f,0.3f,0.3f,
							2
	);

	return 0;
}

void S_DemoOpengl_Quit(void)
{
	MODEL_Free(&Model_Ground);
	MODEL_Free(&Model_Torus);
	SDL_GL_DeleteContext(openglContext);
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

	if(Keys[SDLK_SPACE] == 1)
		CAM_Up(0.1f);
	
	if(Keys[SDLK_LSHIFT] == 1)
		CAM_Up(-0.1f);


	if(Keys[SDLK_KP_PLUS] == 1)
	{
		Light_Test.diffuse[0] += 0.01; // TODO: A remplacer par une fonciton
		Light_Test.diffuse[1] += 0.01; // pour une meilleur lisibilité
		Light_Test.diffuse[2] += 0.01;

		Light_Test.specular[0] += 0.01; // TODO: A remplacer par une fonciton
		Light_Test.specular[1] += 0.01; // pour une meilleur lisibilité
		Light_Test.specular[2] += 0.01;
	}

	if(Keys[SDLK_KP_MINUS] == 1)
	{
		Light_Test.diffuse[0] -= 0.01; // TODO: ""
		Light_Test.diffuse[1] -= 0.01;
		Light_Test.diffuse[2] -= 0.01;

		Light_Test.specular[0] -= 0.01; // TODO: A remplacer par une fonciton
		Light_Test.specular[1] -= 0.01; // pour une meilleur lisibilité
		Light_Test.specular[2] -= 0.01;
	}
	if(Keys[SDLK_KP_6] == 1)
		Light_Test.pos[0] +=0.1;
	if(Keys[SDLK_KP_4] == 1)
		Light_Test.pos[0] -=0.1;
	if(Keys[SDLK_KP_8] == 1)
		Light_Test.pos[2] +=0.1;
	if(Keys[SDLK_KP_2] == 1)
		Light_Test.pos[2] -=0.1;
	if(Keys[SDLK_KP_9] == 1)
		Light_Test.pos[1] +=0.1;
	if(Keys[SDLK_KP_3] == 1)
		Light_Test.pos[1] -=0.1;
	
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

	//MODEL_Display(&Model_Triangle);
	MODEL_Display(&Model_Ground);
	MODEL_Display(&Model_Torus);

	//glFlush();
	SDL_GL_SwapWindow(Window);
}