#ifndef SHADER_HANDLER_H
#define SHADER_HANDLER_H

#include <GL/glew.h>
// #include "ShaderLoader.h"

typedef struct {
	GLuint shaderID;
	GLuint UniformCamMatrix; // matrice camera
	GLuint UniformPerspectiveMatrix; // matrice perspective
}Shader;

void SH_Load(Shader *shad, const char* vertexFilePath, const char* fragmentFilePath);	 // Charger un shader
void SH_Destroy(Shader *shad); // detruire un shader

#endif // SHADER_HANDLER_H
