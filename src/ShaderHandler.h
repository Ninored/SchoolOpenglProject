#ifndef SHADER_HANDLER_H
#define SHADER_HANDLER_H

#include <GL/glew.h>
#include "Light.h"

typedef struct {
	GLuint shaderID;
	GLuint UniformCamMatrix; // matrice camera
	GLuint UniformPerspectiveMatrix; // matrice perspective
	GLuint UniformCameraPos; // cameraPos

	GLuint UniformNs;
	GLuint UniformKa;
	GLuint UniformKd;
	GLuint UniformKs;
	Light_ID UniformLight;
}Shader;

void SH_Load(Shader *shad, const char* vertexFilePath, const char* fragmentFilePath);	 // Charger un shader
void SH_Destroy(Shader *shad); // detruire un shader

#endif // SHADER_HANDLER_H
