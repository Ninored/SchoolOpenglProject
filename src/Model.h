#ifndef MODEL_H
#define MODEL_H

#include "ShaderHandler.h"
typedef struct {
	GLuint vao;
	GLuint vbo;
	GLuint vco;

	Shader shader; 
}Model;

void MODEL_Load(Model *model, const char* shadersFiles);
void MODEL_Display(Model *model);

void MODEL_TEST_Triangle(Model *model);
void MODEL_TEST_Cube(Model *model);

#endif // MODEL_H
