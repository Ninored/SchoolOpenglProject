#include "FontLoader.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

static void FL_Quit(void); // Fonction quitter le FontLoader

int FL_Init(void)
{
	if (TTF_Init() == -1)
	{
		printf("[ERROR]\tError while loading FontLoader: %s\n", TTF_GetError());
		return -1;	// retourn une erreur
	}
	atexit(FL_Quit);
	printf("[INFO]\tFontLoader initialized\n");
	return 0; // success initialisation
}

void FL_Quit(void)
{
	TTF_Quit();
}

void FL_Load(const char *file, Font *FONT, int size)
{
	FONT->font = TTF_OpenFont(file, size);
	if(FONT->font == NULL)
	{
		printf("[ERROR]\tERROR while loading font: %s\n", file);
		exit(1);
	}
	printf("[INFO]\tFont Loaded %s [%i]\n", file, size);
}

void FL_Destroy(Font *FONT)
{
	TTF_CloseFont(FONT->font);
	FONT->font = NULL;
}

void FL_Apply(SDL_Renderer *renderer, Font* FONT, const char* text, int posX, int posY)
{

	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;

	SDL_Color white = {255,255,255,0};
	SDL_Surface *_surf = TTF_RenderUTF8_Solid(FONT->font, text, white);
	if(_surf == NULL)
	{
		printf("[ERROR]\tError TTF can't apply font: %s\n", TTF_GetError());
		exit(1);
	}
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, _surf);
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);

	rect.x -= rect.w/2;
	rect.y -= rect.h/2;

	if(SDL_RenderCopy(renderer, tex, NULL, &rect) == -1)
	{
		printf("[ERROR]\tError while writing font: %s\n", text);
		exit(1);
	}

	SDL_FreeSurface(_surf);
}

void FL_ApplyColored(SDL_Renderer *renderer, Font* FONT, const char* text, int posX, int posY, int r, int g, int b, int a)
{

	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;

	SDL_Color white = {r,g,b,a};
	SDL_Surface *_surf = TTF_RenderUTF8_Solid(FONT->font, text, white);
	if(_surf == NULL)
	{
		printf("[ERROR]\tError TTF can't apply font: %s\n", TTF_GetError());
		exit(1);
	}
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, _surf);
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);

	rect.x -= rect.w/2;
	rect.y -= rect.h/2;

	if(SDL_RenderCopy(renderer, tex, NULL, &rect) == -1)
	{
		printf("[ERROR]\tError while writing font: %s\n", text);
		exit(1);
	}

	SDL_FreeSurface(_surf);
}