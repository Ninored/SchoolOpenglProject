#include "Textures.h"
#include "ImageLoader.h"

#include <stdio.h>
#include <stdlib.h>

//#include <SDL2/SDL.h>

void TEX_Load(const char *path, SDL_Renderer *renderer, Texture *tex)
{
	SDL_Surface* _surf = IL_Load(path);	// creation d'une surface temporaire
	
	if(_surf == NULL)				// Gestion des erreurs lors du chargement
	{
		printf("[ERROR]\tError lors du chargement de l'image: %s\n %s", path, IL_GetError());
		exit(1);
	}

	tex->tex = SDL_CreateTextureFromSurface(renderer, _surf);
	SDL_QueryTexture(tex->tex, NULL, NULL, &tex->w, &tex->h);

	printf("[INFO]\tTexture charge: %s [%ix%i]\n", path, tex->w, tex->h);

	IL_Destroy(_surf);			// desttruction de l'image temporaire
}

void TEX_Destroy(Texture *tex)
{
	SDL_DestroyTexture(tex->tex);
	tex->w = tex->h =0;
}

void TEX_Apply(SDL_Renderer *renderer, Texture* tex, int posX, int posY, int width, int height)
{
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = width;
	rect.h = height;

	SDL_RenderCopy(renderer, tex->tex, NULL, &rect);
}

