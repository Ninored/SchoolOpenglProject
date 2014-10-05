
// TOP Include
#include "MainMenu.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "GameState.h"

// Mid Include
#include "Textures.h"
#include "FontLoader.h"

// Static Variables
static SDL_Event event;
static SDL_Renderer *renderer = NULL;	// render pour afficher a l'ecran

// Font
static Font Font_Menu;

// Textures
static Texture Texture_Background;	// Background
static Texture Texture_Bouton;	// Bouton
static Texture Texture_BoutonClick; // TODO: BoutonCliqué

// Variables de fonctionnement
static int selector = 0;


int S_MainMenu_Init(void)
{
	renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	// creation du render
	if (renderer == NULL)	// gestion d'erreur
	{
		printf("[ERROR]\tError while creating renderer\n");
		return -1;
	}

	// Chargement de la texture
	TEX_Load("./Assets/MainMenu/Background.jpg", renderer, &Texture_Background);
	TEX_Load("./Assets/MainMenu/Button.jpg", renderer, &Texture_Bouton);
	TEX_Load("./Assets/MainMenu/ButtonClick.jpg", renderer, &Texture_BoutonClick);
	FL_Load("./Assets/MainMenu/Font.ttf", &Font_Menu, 22);
	return 0;
}

void S_MainMenu_Quit(void)
{
	// Destruction des textures et polices utilisé
	TEX_Destroy(&Texture_Background);
	TEX_Destroy(&Texture_Bouton);
	TEX_Destroy(&Texture_BoutonClick);
	FL_Destroy(&Font_Menu);
	// Destruction du renderer
	SDL_DestroyRenderer(renderer);	// destruction du renderer
}

void S_MainMenu_Event(void)	// lors d'un evenement
{
	SDL_WaitEvent(&event);

	// Gestion de l'evenement
	switch (event.type)
	{
	case SDL_QUIT:		// fermeture de la fenetre
		_ExitGame();
		break;
	case SDL_WINDOWEVENT:
		if(event.window.event == SDL_WINDOWEVENT_RESIZED)
			SDL_GetWindowSize(Window, &WINDOWS_W, &WINDOWS_H);
		break;

	case SDL_KEYDOWN:	// Touche pressé
		switch(event.key.keysym.sym)
		{
		case SDLK_ESCAPE: 	// ESC
			_ExitGame();
			break;
		case SDLK_DOWN:
			selector++;
			if(selector >= 2) selector = 0;
			break;
		case SDLK_UP:
			selector--;
			if(selector <=-1) selector = 1;
			break;
		case SDLK_RETURN:
			if(selector == 0) _StateChange(STATE_OPENGL);
			if(selector == 1) _ExitGame();
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if(
		   event.button.x >  ((WINDOWS_W / 2) - (WINDOWS_W / 3)) &&                                                                                                                                                                                                                                                                                                                                                                                                                      
		   event.button.x <= ((WINDOWS_W/2) - (WINDOWS_W/3) + ((WINDOWS_W / 3) * 2)) &&                                                                                                                                                                                                                                                                                                                                                                                                                      
		   event.button.y >  ((WINDOWS_H / 2) - (Texture_Bouton.h / 2) - (Texture_Bouton.h *4)) &&                                                                                                                                                                                                                                                                          
		   event.button.y <= ((WINDOWS_H / 2) - (Texture_Bouton.h / 2) - (Texture_Bouton.h * 4) + Texture_Bouton.h) 
		   )
			_StateChange(STATE_OPENGL);

		if(
		   event.button.x >  ((WINDOWS_W / 2) - (WINDOWS_W / 3)) &&
		   event.button.x <= ((WINDOWS_W/2) - (WINDOWS_W/3) + ((WINDOWS_W / 3) * 2)) &&
		   event.button.y >  ((WINDOWS_H / 2) - (Texture_Bouton.h / 2) - (Texture_Bouton.h * 2)) &&
		   event.button.y <= ((WINDOWS_H / 2) - (Texture_Bouton.h / 2) - (Texture_Bouton.h * 2) + Texture_Bouton.h)
		   )
			_ExitGame();
		break;
	}
}

void S_MainMenu_Compute(void)
{

}

void S_MainMenu_Draw(void)
{
	// Afficher la texture.
	TEX_Apply(renderer, &Texture_Background, 0, 0, WINDOWS_W, WINDOWS_H);	// Application de la texture sur tout l'ecran

	if(selector == 0)
	{
		TEX_Apply(renderer, &Texture_BoutonClick, 		// Bouton demo.
		          ((WINDOWS_W/2)-(WINDOWS_W/3)),
		          ((WINDOWS_H/2) - (Texture_Bouton.h/2) - (Texture_Bouton.h*4)),
		          ((WINDOWS_W/3)*2),
		          Texture_Bouton.h
	      );
	}
	else{
		TEX_Apply(renderer, &Texture_Bouton, 		// Bouton demo.
		          ((WINDOWS_W/2)-(WINDOWS_W/3)),
		          ((WINDOWS_H/2) - (Texture_Bouton.h/2) - (Texture_Bouton.h*4)),
		          ((WINDOWS_W/3)*2),
		          Texture_Bouton.h
		          );		
	}
	if(selector == 1)
	{
		TEX_Apply(renderer, &Texture_BoutonClick,		// Bouton quitter
		          ((WINDOWS_W/2)-(WINDOWS_W/3)),
		          ((WINDOWS_H/2) - (Texture_Bouton.h/2) - (Texture_Bouton.h*2)),
		          ((WINDOWS_W/3)*2),
		          Texture_Bouton.h
		          );
	}
	else 
	{
		TEX_Apply(renderer, &Texture_Bouton,		// Bouton quitter
		          ((WINDOWS_W/2)-(WINDOWS_W/3)),
		          ((WINDOWS_H/2) - (Texture_Bouton.h/2) - (Texture_Bouton.h*2)),
		          ((WINDOWS_W/3)*2),
		          Texture_Bouton.h
		          );
	}

	FL_Apply(renderer, &Font_Menu, "Lancer la démo", 
	         (WINDOWS_W/2),
	         ((WINDOWS_H/2) - (Texture_Bouton.h * 4))
	         );

	FL_Apply(renderer, &Font_Menu, "Quitter",
	         (WINDOWS_W/2),
	         ((WINDOWS_H/2) - (Texture_Bouton.h * 2))
	         );

	// TODO: Flush
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(Window);
}
