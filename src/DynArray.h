#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <GL/glew.h>
#include <stdlib.h>
#include "Light.h"

/**************************************
 * tableau dynamique de GLfloat (float)
 */
typedef struct {
	GLfloat *array;
	unsigned int used;
	unsigned int size;
} ARRAY_GLFLOAT;

void ARRAY_GLFLOAT_INIT(ARRAY_GLFLOAT *a);
void ARRAY_GLFLOAT_ADD(ARRAY_GLFLOAT *a, GLfloat num);
void ARRAY_GLFLOAT_DESTROY(ARRAY_GLFLOAT *a);

/**************************************
 * tableau dynamique d' unsigned int
 */
typedef struct {
	unsigned int *array;
	unsigned int used;
	unsigned int size;
} ARRAY_UINT;

void ARRAY_UINT_INIT(ARRAY_UINT *a);
void ARRAY_UINT_ADD(ARRAY_UINT *a, unsigned int num);
void ARRAY_UINT_DESTROY(ARRAY_UINT *a);

#endif // DYN_ARRAY_H
