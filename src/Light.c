#include "Light.h"

#include <string.h>
#include <stdio.h>

void LIGHT_Create(Light *light, float posX, float posY, float posZ,
								float directionX, float directionY, float directionZ,
								float diffuseR, float diffuseG, float diffuseB,
								float intensity)
{
	light->pos[0] = posX;
	light->pos[1] = posY;
	light->pos[2] = posZ;

	light->direction[0] = directionX;
	light->direction[1] = directionY;
	light->direction[2] = directionZ;

	light->diffuse[0] = diffuseR;
	light->diffuse[1] = diffuseG;
	light->diffuse[2] = diffuseB;

	light->intensity = intensity;
	/* 

	printf("[INFO]\tLight created:\n");
	printf("[INFO]\tPos: %f %f %f\n", light->pos[0], light->pos[1], light->pos[2]);
	printf("[INFO]\tDirection:%f %f %f\n", light->direction[0], light->direction[1], light->direction[2]);
	printf("[INFO]\tColor: %f %f %f\n", light->color[0], light->color[1], light->color[2]);
	printf("[INFO]\tIntensity: %f\n", light->intensity);
	
	*/
}

void LIGHT_LoadUniform(Light_ID *light_id, GLuint shaderID)
{
	glUseProgram(shaderID);
	light_id->intensity = glGetUniformLocation(shaderID, "light.intensity");
	light_id->pos = glGetUniformLocation(shaderID, "light.pos");
	light_id->direction  = glGetUniformLocation(shaderID, "light.direction");
	light_id->diffuse = glGetUniformLocation(shaderID, "light.diffuse");
}

void LIGHT_SendUniform(GLuint shaderID, Light_ID *light_id, Light *light)
{
	glUseProgram(shaderID);
	glProgramUniform3f(shaderID, light_id->pos, light->pos[0], light->pos[1], light->pos[2]);
	glProgramUniform3f(shaderID, light_id->direction, light->direction[0], light->direction[1], light->direction[2]);
	glProgramUniform3f(shaderID, light_id->diffuse, light->diffuse[0], light->diffuse[1], light->diffuse[2]);
	glProgramUniform1f(shaderID, light_id->intensity, light->intensity);
}