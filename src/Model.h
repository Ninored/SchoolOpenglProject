#ifndef MODEL_H
#define MODEL_H

#include "ShaderHandler.h"
#include "Matrix.h"

// voir fichier ObjLoaderExplain.txt pour les notations.
typedef struct{
	GLfloat Ns;
	GLfloat Ka[3];
	GLfloat Kd[3];
	GLfloat Ks[3];
	unsigned int illum;
} Material;

typedef struct {
	GLuint vao; // buffer array contiens tout les info de ce qui suit
	GLuint vbo; // buffer vertex (position dans carde graphique)
	GLuint tbo; // buffer texture ("")
	GLuint nbo; // buffer normals ("")

	Shader shader; // shader utilisé.

	Mat4f matrix; // matrice du model
	Material material;
} Model;

void MODEL_Load(Model *model, const char* shadersFiles, const char* vertexShader, const char* fragmentShader);
void MODEL_Free(Model *model);
void MODEL_Display(Model *model);

void MODEL_TEST_Triangle(Model *model);
void MODEL_TEST_Cube(Model *model);

#endif // MODEL_H
