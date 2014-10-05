/*
 * GameState.h
 *
 *  Created on: 13 sept. 2014
 *      Author: Ulysse
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <SDL2/SDL.h>

// TODO: Changer les define par des variables
int WINDOWS_W;
int WINDOWS_H;


enum EN_STATE {
	STATE_MAINMENU,
	STATE_OPENGL,
	STATE_UNKNOW
};

SDL_Window *Window;	// Fenetre SDL Tout le long de notre programme

int running;

void _ExitGame(void);

void _StateEvent(void);
void _StateCompute(void);
void _StateDraw(void);

void _StateChange(enum EN_STATE newState);

#endif /* GAMESTATE_H_ */
