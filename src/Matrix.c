#include "Matrix.h"
#include <stdio.h>
#include <math.h>

/*
	produit matriciel
	out = InA * InB
 */
void MAT_Mult(Mat4f out, Mat4f InA, Mat4f InB)
{
	unsigned int col;
	unsigned int row;
	unsigned int i;
	for(row = 0; row <= 3; row++)
		for(col = 0; col <= 3; col++)
			for(i = 0; i <= 3; i++)
				out[row][col] += InA[row][i] * InB[i][col];
}

/*
	[1 0 0 0]
	[0 1 0 0]
	[1 0 1 0]
	[0 0 0 1]
 */
void MAT_Identity(Mat4f matrix)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;

	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;

	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}


void MAT_Projection(Mat4f matrix, int w, int h, int f, int n, int fov)
{
	float d = 1/(tan((fov/2)));

	matrix[0][0] = d/(w/h);
	matrix[0][1] = 0.0f;
	matrix[0][2] = 0.0f;
	matrix[0][3] = 0.0f;

	matrix[1][0] = 0.0f;
	matrix[1][1] = d;
	matrix[1][2] = 0.0f;
	matrix[1][3] = 0.0f;

	matrix[2][0] = 0.0f;
	matrix[2][1] = 0.0f;
	matrix[2][2] = (n + f) / (n - f);
	matrix[2][3] = (2.0f * f * n) / (n - f);

	matrix[3][0] = 0.0f;
	matrix[3][1] = 0.0f;
	matrix[3][2] = -1.0f;
	matrix[3][3] = 0.0f;
}

void MAT_Translate(Mat4f matrix, float x, float y, float z)
{

}

void MAT_Rotate(Mat4f matrix, float deg, int x, int y, int z)
{

}

void MAT_Print(Mat4f matrix)
{
	unsigned int r = 0;
	unsigned int c = 0;
	for(r = 0; r < 4; r++)
		for(c = 0; c < 4; c++)
			printf("[%d][%d]: %lf\n",r, c, matrix[r][c]);
	printf("\n\n");
}
