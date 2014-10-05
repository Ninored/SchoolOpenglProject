#include "GameState.h"
#include <stdio.h>
#include <stdlib.h>

// include States
#include "MainMenu.h"
#include "DemoOpengl.h"


WINDOWS_W = 800;
WINDOWS_H = 600;

static void (*eventState)(void) = NULL;
static void (*computeState)(void) = NULL;
static void (*drawState)(void) = NULL;

static int (*initState)(void) = NULL;
static void (*quitState)(void) = NULL;

static enum EN_STATE currentState = STATE_UNKNOW;



void _ExitGame(void)
{
	if (quitState != NULL && currentState != STATE_UNKNOW)
	{
		quitState();
	}
	printf("Programme Exit\n");
	exit(0);
}

void _StateEvent(void)
{
	if (eventState == NULL | currentState == STATE_UNKNOW)
	{
		printf("[ERROR]\teventState() is NULL, no instance selected\n");
		//getc();
		exit(1);
	}
	else
		eventState();
}

void _StateCompute(void)
{
	if (computeState == NULL | currentState == STATE_UNKNOW)
	{
		printf("[ERROR]\tcomputeState is NULL, no instance selected\n");
		//getc();
		exit(1);
	}
	else
		computeState();
}

void _StateDraw(void)
{
	if (drawState == NULL | currentState == STATE_UNKNOW)
	{
		printf("[ERROR]\tcrawState() is NULL, no instance selected\n");
		//getc();
		exit(1);
	}
	else
		drawState();
}

void _StateChange(enum EN_STATE newState)
{
	if (quitState != NULL | currentState != STATE_UNKNOW)
		quitState();

	switch (newState)
	{
		case STATE_MAINMENU:	// MenuPrincipal
		currentState = STATE_MAINMENU;
		initState = S_MainMenu_Init;
		quitState = S_MainMenu_Quit;

		eventState = S_MainMenu_Event;
		computeState = S_MainMenu_Compute;
		drawState = S_MainMenu_Draw;
		if (initState() == -1)
		{
			printf("[ERROR]\tError while initializing state Menu\n");
			exit(1);
		}
		break;
		case STATE_OPENGL:
			// OPENGL state
		currentState = STATE_OPENGL;
		initState = S_DemoOpengl_Init;
		quitState = S_DemoOpengl_Quit;

		eventState = S_DemoOpengl_Event;
		computeState = S_DemoOpengl_Compute;
		drawState = S_DemoOpengl_Draw;
		if (initState() == -1)
		{
			printf("[ERROR]\tError while initializing state OPENGL\n");
			exit(1);
		}
		break;

		case STATE_UNKNOW:
		default:
		printf("[WARN]\tnewState is invalid\n");
		currentState = STATE_UNKNOW;
		eventState = computeState = drawState = initState = quitState = NULL;
	}
}
