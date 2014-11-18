#ifndef LIGHT_HANDLER_H
#define LIGHT_HANDLER_H

#include "Light.h"

typedef struct {
	Light *array;
	unsigned int used;
	unsigned int size;
} ARRAY_LIGHT;

void ARRAY_LIGHT_INIT(ARRAY_LIGHT *a);
void ARRAY_LIGHT_ADD(ARRAY_LIGHT *a, 
					float posX, float posY, float posZ,
					float directionX, float directionY, float directionZ,
					float ambiantR, float ambiantG, float ambiantB,
					float diffuseR, float diffuseG, float diffuseB,
					float specularR, float specularG, float specularB,
					float intensity);
void ARRAY_LIGHT_DESTROY(ARRAY_LIGHT *a);
void ARRAY_LIGHT_SEND_UNIFORM(ARRAY_LIGHT *a);

#endif // LIGHT_HANDLER_H
