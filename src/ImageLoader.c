#include "ImageLoader.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL_image.h>

static void IL_Quit(void);	// Fonction pour quitter le chargeur d'image

int IL_Init(void)
{
	int flag = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG); // initialisation de tout les chargeurs d'images
	if ((flag & (IMG_INIT_JPG | IMG_INIT_PNG)) != flag)
	{
		printf("[ERROR]\tError while loading Image loader: %s\n", IMG_GetError());
		return -1; //erreur dans le chargement
	}
	atexit(IL_Quit);
	printf("[INFO]\tChargeur d'image Initialise avec [FLAG:%i]\n", flag);
	return 0; // tout c'est bien passé
}

void IL_Quit(void)
{
	IMG_Quit();
}

SDL_Surface* IL_Load(const char *path)
{
	// INFO: Ne peut pas etre changer par autre chose.
	SDL_Surface *srf = IMG_Load(path);
	return srf;
}

void IL_Destroy(SDL_Surface *surface)
{
	SDL_FreeSurface(surface);
}

const char *IL_GetError(void)
{
	return IMG_GetError();
}