#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>

typedef struct {
	GLfloat pos[3];
	GLfloat direction[3];
	GLfloat diffuse[3];
	GLfloat intensity;
} Light;

typedef struct {
	GLuint pos;
	GLuint direction;
	GLuint diffuse;
	GLuint intensity;
} Light_ID;

void LIGHT_Create(Light *light, float posX, float posY, float posZ,
								float directionX, float directionY, float directionZ,
								float diffuseR, float diffuseG, float diffuseB,
								float intensity);
void LIGHT_LoadUniform(Light_ID *light_id, GLuint shaderID);
void LIGHT_SendUniform(GLuint shaderID, Light_ID *light_id, Light *light);

#endif // LIGHT_H
