/*
 * ImageLoader.h
 *
 *  Created on: 13 sept. 2014
 *      Author: Ulysse
 */

#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

#include <SDL2/SDL.h>

int IL_Init(void);	// Fonction d'initialisation du chargeur d'image
SDL_Surface* IL_Load(const char *path);
void IL_Destroy(SDL_Surface *surface);
const char* IL_GetError(void);

#endif /* IMAGELOADER_H_ */
