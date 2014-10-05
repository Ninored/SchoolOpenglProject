#ifndef TEXTURES_H
#define TEXTURES_H

#include "ImageLoader.h"

typedef struct {
	SDL_Texture *tex;	// La texture au format pixels
	int w, h;	// Taille de la texture
} Texture;

void TEX_Load(const char *path, SDL_Renderer *renderer, Texture *tex);
void TEX_Destroy(Texture *tex);
void TEX_Apply(SDL_Renderer *rederer, Texture* tex, int posX, int posY, int width, int height);

#endif // TEXTURES_H
