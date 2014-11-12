#include "DynArray.h"

/**************************************
 * tableau dynamique de GLfloat (float)
 */
void ARRAY_GLFLOAT_INIT(ARRAY_GLFLOAT *a)
{
	a->size  = 1; // initialisation de la taille.
	a->used  = 0; // initialisation des case utilisé.
	a->array = (GLfloat*)malloc(sizeof(GLfloat)); // mise en place d'une case
}

void ARRAY_GLFLOAT_ADD(ARRAY_GLFLOAT *a, GLfloat num)
{
	if(a->size == a->used)	// si taille du tableau = taille utilisé
	{
		a->size++;	// augmante la taille
		a->array = (GLfloat*)realloc(a->array, a->size * sizeof(GLfloat)); // réalou la mémoire
	}
	a->array[a->used++] = num; // ajout de la valeur dans la case suivante
}

void ARRAY_GLFLOAT_DESTROY(ARRAY_GLFLOAT *a)
{
	free(a->array); // libération du tableau
	a->array = NULL; // pointeur sur NULL
	a->size = a->used = 0; // mise a 0 des variables
}

/**************************************
 * tableau dynamique d' unsigned int
 */
void ARRAY_UINT_INIT(ARRAY_UINT *a)
{
	a->size  = 1; // initialisation de la taille.
	a->used  = 0; // initialisation des case utilisé.
	a->array = (unsigned int*)malloc(sizeof(unsigned int)); // mise en place d'une case
}

void ARRAY_UINT_ADD(ARRAY_UINT *a, unsigned int num)
{
	if(a->size == a->used)	// si taille du tableau = taille utilisé
	{
		a->size++;	// augmante la taille
		a->array = (unsigned int*)realloc(a->array, a->size * sizeof(unsigned int)); // réalou la mémoire
	}
	a->array[a->used++] = num; // ajout de la valeur dans la case suivante
}

void ARRAY_UINT_DESTROY(ARRAY_UINT *a)
{
	free(a->array); // libération du tableau
	a->array = NULL; // pointeur sur NULL
	a->size = a->used = 0; // mise a 0 des variables
}
