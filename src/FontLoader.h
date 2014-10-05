/*
 * FontLoader.h
 *
 *  Created on: 13 sept. 2014
 *      Author: Ulysse
 */

#ifndef FONTLOADER_H_
#define FONTLOADER_H_

#include <SDL2/SDL_ttf.h>

typedef struct
{
		TTF_Font *font;
}Font;

int FL_Init(void);
void FL_Load(const char *file, Font* font, int size);
void FL_Destroy(Font *FONT);
void FL_Apply(SDL_Renderer *renderer, Font* FONT, const char* text, int posX, int posY);
void FL_ApplyColored(SDL_Renderer *renderer, Font* FONT, const char* text, int posX, int posY, int r, int g, int b, int a);

#endif /* FONTLOADER_H_ */
