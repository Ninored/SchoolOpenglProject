#include "Light.h"

#include <string.h>
#include <stdio.h>

void LIGHT_Create(Light *light, float posX, float posY, float posZ,
								float directionX, float directionY, float directionZ,
								float ambiantR, float ambiantG, float ambiantB,
								float diffuseR, float diffuseG, float diffuseB,
								float specularR, float specularG, float specularB,
								float intensity)
{
	light->pos[0] = posX;
	light->pos[1] = posY;
	light->pos[2] = posZ;

	light->direction[0] = directionX;
	light->direction[1] = directionY;
	light->direction[2] = directionZ;

	light->ambiant[0] = ambiantR;
	light->ambiant[1] = ambiantG;
	light->ambiant[2] = ambiantB;

	light->diffuse[0] = diffuseR;
	light->diffuse[1] = diffuseG;
	light->diffuse[2] = diffuseB;

	light->specular[0] = specularR;
	light->specular[1] = specularG;
	light->specular[2] = specularB;

	light->intensity = intensity;
}

void LIGHT_LoadUniform(Light_ID *light_id, GLuint shaderID)
{
	glUseProgram(shaderID);
	light_id->intensity = glGetUniformLocation(shaderID, "light.intensity");
	light_id->pos = glGetUniformLocation(shaderID, "light.pos");
	light_id->direction  = glGetUniformLocation(shaderID, "light.direction");
	light_id->ambiant = glGetUniformLocation(shaderID, "light.ambiant");
	light_id->diffuse = glGetUniformLocation(shaderID, "light.diffuse");
	light_id->specular = glGetUniformLocation(shaderID, "light.specular");
}

void LIGHT_SendUniform(GLuint shaderID, Light_ID *light_id, Light *light)
{
	glProgramUniform3f(shaderID, light_id->pos, light->pos[0], light->pos[1], light->pos[2]);
	glProgramUniform3f(shaderID, light_id->direction, light->direction[0], light->direction[1], light->direction[2]);
	glProgramUniform3f(shaderID, light_id->ambiant, light->ambiant[0], light->ambiant[1], light->ambiant[2]);
	glProgramUniform3f(shaderID, light_id->diffuse, light->diffuse[0], light->diffuse[1], light->diffuse[2]);
	glProgramUniform3f(shaderID, light_id->specular, light->specular[0], light->specular[1], light->specular[2]);
	glProgramUniform1f(shaderID, light_id->intensity, light->intensity);
}