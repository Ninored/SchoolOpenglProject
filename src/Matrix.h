#ifndef MATRIX_H
#define MATRIX_H
	
#include <GL/glew.h>

/*
	Utilisation:
		- Matrice a priorité par ligne
 */
typedef float Mat4f[4][4];
static const float degrad = 3.141592654 / 180;

////////////////////////////////////
// Opération basique sur matrices //
////////////////////////////////////
void MAT_Mult(Mat4f out, Mat4f InA, Mat4f InB); // multiplication matriciel

//////////////////////
// Matrices de base //
//////////////////////
void MAT_Identity(Mat4f matrix); // matrice d'identité
void MAT_Projection(Mat4f matrix, float w, float h, float f, float n, float fov); // Créateur de matrice de projection

///////////////////////////////////
// Opération sur matrices OPENGL //
///////////////////////////////////
void MAT_Translate(Mat4f matrix, float x, float y, float z); // Op de translation
void MAT_Rotate(Mat4f matrix, float deg, float x, float y, float z); // Op de rotation
// void MAT_Scale(Mat4f matrix, float x, float y, float z); Pas besoins pour l'instant


///////////////////////////
// Outils de maintenance //
///////////////////////////
void MAT_Print(Mat4f matrix);
void MAT_PrintFancy(Mat4f matrix);

#endif // MATRIX_H
	
