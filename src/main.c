/**
 *	Programme de présentation pour l'option ISN.
 *	Desc: Affichage d'un objet texturé et shadé a l'ecran avec les lib SDL et OPENGL.
 *	Createur: FONTAINE Ulysse
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "GameState.h"
#include "ImageLoader.h"
#include "FontLoader.h"

static void beginState(void);
static void endState(void);

int main(int argc, char **argv)
{
	printf("Démarrage...\n");
	beginState();	// fonction d'initialisation du programme

	while (1)
	{
		_StateEvent();
		_StateCompute();
		_StateDraw();
	}

	exit(1);
}

/// Fonction d'initialiqation du programme
void beginState(void)
{
	// initialisation de la SLD, et de la fenetre
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		printf("Error while loading SDL: %s\n", SDL_GetError());
		exit(1);
	}
	Window = SDL_CreateWindow("Demo Opengl",	// creation de la fenetre
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOWS_W, WINDOWS_H,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (Window == NULL)	// En cas d'erreur
	{
		printf("[ERROR]\tError while creating Window: %s\n", SDL_GetError());
		exit(1);
	}
	printf("[INFO]\tFenetre de [%i]x[%i] pixels cree \n", WINDOWS_W, WINDOWS_H);
	atexit(endState);

	// Initialisation du chargeur d'image
	IL_Init();

	// Initialisation du chargeur de police
	FL_Init();

	_StateChange(STATE_MAINMENU);
}


// Fonction de fermeture du programme
void endState(void)
{
	SDL_DestroyWindow(Window); // destruction de la fenetre.
	SDL_Quit();	// Quitter la SDL.
}
