#include "WavefrontLoader.h"
#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include "DynArray.h"

/*
	TODO: ID:T:0.1 commenter les strcmp pour annoncer l'action
 */

static void S_init(void);
static void S_free(void);
static int S_MaterialLoad(Model *model, const char* filepath, const char* materialName);

// tableaux dynamiques temporaires
static ARRAY_GLFLOAT vertices; // tableau des vertices (points)
static ARRAY_GLFLOAT textures; // tableua coordonnées textures
static ARRAY_GLFLOAT normals; // tableau des normales

static ARRAY_GLFLOAT vertexArray;
static ARRAY_GLFLOAT textureArray;
static ARRAY_GLFLOAT normalArray;

static char materialFilePath[1024]; // fichier matériaux
static char materialToUse[1024];

int WAVEFRONT_Load(Model *model, const char* filepath)
{
	//initialisation des tableau
	S_init();

	FILE* file = fopen(filepath, "r");
	if(file == NULL)
	{
		printf("[ERROR]\tFailed to load: %s", filepath);
		S_free();
		return -1;
	}

	while(1)
	{
		char buffer[1024];
		int str = fscanf(file, "%s", buffer); // lecture du premier caractère de la ligne
		
		if(str == EOF) // fin du fichier ?
			break; // quite le fichier fin de la boucle

		if(strcmp(buffer, "mtllib") == 0)
			fscanf(file, "%s\n", materialFilePath);

		if(strcmp(buffer, "v") == 0)
		{
			GLfloat tmp[3];
			fscanf(file, "%f %f %f \n", &tmp[0], &tmp[1], &tmp[2]); // lecture de la ligne
			ARRAY_GLFLOAT_ADD(&vertices, tmp[0]); // ajout de la coordonnée
			ARRAY_GLFLOAT_ADD(&vertices, tmp[1]); // ""
			ARRAY_GLFLOAT_ADD(&vertices, tmp[2]); // ""
		}

		if(strcmp(buffer, "vn") == 0)
		{
			GLfloat tmp[3];
			fscanf(file, "%f %f %f \n", &tmp[0], &tmp[1], &tmp[2]); // lecture de la ligne
			ARRAY_GLFLOAT_ADD(&normals, tmp[0]); // ajout de la coordonnée
			ARRAY_GLFLOAT_ADD(&normals, tmp[1]); // ""
			ARRAY_GLFLOAT_ADD(&normals, tmp[2]); // ""
		}

		if(strcmp(buffer, "vt") == 0)
		{ 	
			GLfloat tmp[3];
			fscanf(file, "%f %f %f \n", &tmp[0], &tmp[1], &tmp[2]); // lecture de la ligne
			ARRAY_GLFLOAT_ADD(&textures, tmp[0]); // ajout de la coordonnée
			ARRAY_GLFLOAT_ADD(&textures, tmp[1]); // ""
			ARRAY_GLFLOAT_ADD(&textures, tmp[2]); // ""
		}

		if(strcmp(buffer, "usemtl") == 0)
		{
			fscanf(file, "%s\n", materialToUse);
			if( S_MaterialLoad(model, materialFilePath, materialToUse) == -1)
				S_free();
		}

		if(strcmp(buffer, "f") == 0)
		{
			/* 
				Le model de fichier utilise des références, Càd qu'en début du fichier nous
				avons tout les coordonnées dont le model est composé, le fichier va ensuite
				construire le model en donnant l'indice de la coordonnée. Nous allons ensuite
				l'ajouter a un tableau qui contient les coordonnées des faces dans l'ordre.
				Le tableau (vertexArray) ressemblera a ça: X1 | Y1 | Z1 | X2 | Y2 | Z2 ....
				Toutes les trois coordonnées une face est produite.
			*/
			unsigned int v[3], t[3], n[3];
			fscanf(file, "%i/%i/%i %i/%i/%i %i/%i/%i\n", 
				         &v[0], &t[0], &n[0],
				         &v[1], &t[1], &n[1],
				         &v[2], &t[2], &n[2]
			);

			// ajout des coordonnées dans l'ordre dans un tableau dynamique
			unsigned int i;
			for(i = 0; i < 3 ; i++)
			{
				// ajout de la coordonnée du point dans le tableau pour les points du model
				ARRAY_GLFLOAT_ADD(&vertexArray, vertices.array[(v[i] - 1 ) * 3 + 0] );
				ARRAY_GLFLOAT_ADD(&vertexArray, vertices.array[(v[i] - 1 ) * 3 + 1] );
				ARRAY_GLFLOAT_ADD(&vertexArray, vertices.array[(v[i] - 1 ) * 3 + 2] );

				// ajout de la coordonnée texture dans le tableau pour les Cood textures
				ARRAY_GLFLOAT_ADD(&textureArray, textures.array[(t[i] - 1) * 2 + 0] );
				ARRAY_GLFLOAT_ADD(&textureArray, textures.array[(t[i] - 1) * 2 + 1] );

				// ajout de la coordonnée de la normal dans le tableau pour les normales
				ARRAY_GLFLOAT_ADD(&normalArray, normals.array[(n[i] - 1) * 3 + 0]);
				ARRAY_GLFLOAT_ADD(&normalArray, normals.array[(n[i] - 1) * 3 + 1]);
				ARRAY_GLFLOAT_ADD(&normalArray, normals.array[(n[i] - 1) * 3 + 2]);
			}
		}
	}
	fclose(file); // fermeture du fichier.


	/**
	 * Mise en mémoire dans la carte graphique des tableau pour l'utilisation des shaders.
	 */
	
	// creation de la mémoire pour les vertex
	glGenBuffers(1, &model->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexArray.used, vertexArray.array, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// création de la memoire pour les coordonnées textures
	glGenBuffers(1, &model->tbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * textureArray.used, textureArray.array, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// création de la mémoire doordonnées des normales
	glGenBuffers(1, &model->nbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->nbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normalArray.used, normalArray.array, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// mise des mémoire dans une autre pour une utilisation simplifié
	glGenVertexArrays(1, &model->vao);
	glBindVertexArray(model->vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // indication sur la mise en forme de la mémoire

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model->tbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0); // ""

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, model->nbo);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0); // ""
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	model->numPoints = vertexArray.used/3;
	//destruction des tableaux
	S_free();
	return 0;
}


int S_MaterialLoad(Model *model, const char* filepath, const char* materialName)
{
	FILE* file = fopen(filepath, "r");
	if(file == NULL)
	{
		printf("[ERROR]\tFailed to load: %s", filepath);
		S_free();
		return -1;
	}
	while(1){
		char buffer[1024];
		char tmpMtl[1024];
		int str = fscanf(file, "%s", buffer); // lecture du premier caractère de la ligne
		
		if(str == EOF) // fin du fichier ?
			break; // quite le fichier fin de la boucle

		if(strcmp(buffer, "newmtl") == 0)
			fscanf(file, "%s\n", tmpMtl);

		if(strcmp(tmpMtl, materialName) == 0)
		{
			if(strcmp(buffer, "Ns") == 0)
				fscanf(file, "%f\n", &model->material.Ns);

			if(strcmp(buffer, "Ka") == 0)
				fscanf(file, "%f %f %f\n", &model->material.Ka[0], &model->material.Ka[1], &model->material.Ka[2]);

			if(strcmp(buffer, "Kd") == 0)
				fscanf(file, "%f %f %f\n", &model->material.Kd[0], &model->material.Kd[1], &model->material.Kd[2]);

			if(strcmp(buffer, "Ks") == 0)
				fscanf(file, "%f %f %f\n", &model->material.Ks[0], &model->material.Ks[1], &model->material.Ks[2]);

			if(strcmp(buffer, "illum") == 0)
				fscanf(file, "%i\n", &model->material.illum);
		}

	}	
	return 0;
}

void S_init(void)
{	
	ARRAY_GLFLOAT_INIT(&vertices);      // initialisation
	ARRAY_GLFLOAT_INIT(&textures);      // ""
	ARRAY_GLFLOAT_INIT(&normals);       // ""
	ARRAY_GLFLOAT_INIT(&vertexArray);   // ""
	ARRAY_GLFLOAT_INIT(&textureArray); // ""
	ARRAY_GLFLOAT_INIT(&normalArray);   // ""
}

void S_free(void)
{
	ARRAY_GLFLOAT_DESTROY(&vertices);       // destruction
	ARRAY_GLFLOAT_DESTROY(&textures);       // ""
	ARRAY_GLFLOAT_DESTROY(&normals);        // ""
	ARRAY_GLFLOAT_DESTROY(&vertexArray);    // ""
	ARRAY_GLFLOAT_DESTROY(&textureArray);  // ""
	ARRAY_GLFLOAT_DESTROY(&normalArray);    // ""
}