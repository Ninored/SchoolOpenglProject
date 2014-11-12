#include "Matrix.h"
#include <stdio.h>
#include <math.h>

/*
	produit matriciel
	out = InA * InB
 */
void MAT_Mult(Mat4f out, Mat4f InA, Mat4f InB)
{
	
	// FIXME:
	/*unsigned int col;
	unsigned int row;
	unsigned int i;
	for(row = 0; row < 3; row++)
		for(col = 0; col < 3; col++)
			for(i = 0; i < 3; i++)
				out[row][col] += InA[row][i] * InB[i][col]; */

	out[0][0] = InA[0][0] * InB[0][0] + InA[0][1] * InB[1][0] + InA[0][2] * InB[2][0] + InA[0][3] * InB[3][0];	// Gx
	out[0][1] = InA[0][0] * InB[0][1] + InA[0][1] * InB[1][1] + InA[0][2] * InB[2][1] + InA[0][3] * InB[3][1];	// Gy
	out[0][2] = InA[0][0] * InB[0][2] + InA[0][1] * InB[1][2] + InA[0][2] * InB[2][2] + InA[0][3] * InB[3][2];	// Gz
	out[0][3] = InA[0][0] * InB[0][3] + InA[0][1] * InB[1][3] + InA[0][2] * InB[2][3] + InA[0][3] * InB[3][3];	// Vx

	out[1][0] = InA[1][0] * InB[0][0] + InA[1][1] * InB[1][0] + InA[1][2] * InB[2][0] + InA[1][3] * InB[3][0];	// Hx
	out[1][1] = InA[1][0] * InB[0][1] + InA[1][1] * InB[1][1] + InA[1][2] * InB[2][1] + InA[1][3] * InB[3][1];	// Hy
	out[1][2] = InA[1][0] * InB[0][2] + InA[1][1] * InB[1][2] + InA[1][2] * InB[2][2] + InA[1][3] * InB[3][2];	// Hz
	out[1][3] = InA[1][0] * InB[0][3] + InA[1][1] * InB[1][3] + InA[1][2] * InB[2][3] + InA[1][3] * InB[3][3];	// Vy

	out[2][0] = InA[2][0] * InB[0][0] + InA[2][1] * InB[1][0] + InA[2][2] * InB[2][0] + InA[2][3] * InB[3][0];	// Ix
	out[2][1] = InA[2][0] * InB[0][1] + InA[2][1] * InB[1][1] + InA[2][2] * InB[2][1] + InA[2][3] * InB[3][1];	// Iy
	out[2][2] = InA[2][0] * InB[0][2] + InA[2][1] * InB[1][2] + InA[2][2] * InB[2][2] + InA[2][3] * InB[3][2];	// Iz
	out[2][3] = InA[2][0] * InB[0][3] + InA[2][1] * InB[1][3] + InA[2][2] * InB[2][3] + InA[2][3] * InB[3][3];	// Vz

	out[3][0] = InA[3][0] * InB[0][0] + InA[3][1] * InB[1][0] + InA[3][2] * InB[2][0] + InA[3][3] * InB[3][0];	// 0
	out[3][1] = InA[3][0] * InB[0][1] + InA[3][1] * InB[1][1] + InA[3][2] * InB[2][1] + InA[3][3] * InB[3][1];	// 0
	out[3][2] = InA[3][0] * InB[0][2] + InA[3][1] * InB[1][2] + InA[3][2] * InB[2][2] + InA[3][3] * InB[3][2];	// 0
	out[3][3] = InA[3][0] * InB[0][3] + InA[3][1] * InB[1][3] + InA[3][2] * InB[2][3] + InA[3][3] * InB[3][3];	// 1
	                                                                                                          	
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


void MAT_Projection(Mat4f matrix, float w, float h, float f, float n, float fov)
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
	printf("\nMatrice de projection genere: \n");
	MAT_PrintFancy(matrix);
}

void MAT_Translate(Mat4f matrix, float x, float y, float z)
{
	matrix[0][3] += -x;
	matrix[1][3] += -y;
	matrix[2][3] += -z;
}

void MAT_Rotate(Mat4f matrix, float deg, float x, float y, float z)
{
	/*
		[x²(1-c)+c	|	xy(1-c)-zs	|	xz(1-c)+ys	|	0]
		[yx(1-c)+zs	|	y²(1-c)+c	|	yz(1-c)-xs	|	0]
		[xz(1-c)-ys	|	yz(1-c)+xs	|	z²(1-c)+c	|	0]
		[	0		|		0		|		0		|	1]
	*/
	float angle = deg * degrad;
	matrix[0][0] = (float)(x*x)*(1 - cos(angle)) + cos(angle);
	matrix[0][1] = (float)(x*y)*(1 - cos(angle)) - z*sin(angle);
	matrix[0][2] = (float)(x*z)*(1 - cos(angle)) + y*sin(angle);

	matrix[1][0] = (float)(y*x)*(1 - cos(angle)) + z*sin(angle);
	matrix[1][1] = (float)(y*y)*(1 - cos(angle)) + cos(angle);
	matrix[1][2] = (float)(y*z)*(1 - cos(angle)) - x*sin(angle);


	matrix[2][0] = (float)(x*z)*(1 - cos(angle)) - y*sin(angle);
	matrix[2][1] = (float)(y*z)*(1 - cos(angle)) + x*sin(angle);
	matrix[2][2] = (float)(z*z)*(1 - cos(angle)) + cos(angle);
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

void MAT_PrintFancy(Mat4f matrix)
{
	unsigned int r = 0;
	printf("%10s | %8d | %8d | %8d | %8d\n", "[4*4]", 0, 1, 2, 3);
	for(r = 0; r < 4; r++)
		printf("[%8d] | %8.4f | %8.4f | %8.4f | %8.4f\n", r, matrix[r][0], matrix[r][1], matrix[r][2], matrix[r][3]);
	printf("\n\n");
}