#include "ShaderHandler.h"
#include <stdio.h>
#include <stdlib.h>

static GLuint LoadShader(const char* vertexFile, const char* fragmentFile);
static void printShaderLog(GLuint shader);

/**
 * Fonction de chargement d'un shader 
 * @param shad
 * @param vertexFile
 * @param fragmentFile
 */
void SH_Load(Shader *shad, const char* vertexFile, const char* fragmentFile)
{
	shad->shaderID = LoadShader(vertexFile, fragmentFile);
	shad->UniformCamMatrix = glGetUniformLocation(shad->shaderID, "CameraMatrix");
	shad->UniformPerspectiveMatrix = glGetUniformLocation(shad->shaderID, "PerspectiveMatrix");
}

/**
 * Fonction de destruction d'un shader
 * @param shad
 */
void SH_Destroy(Shader *shad)
{
	glDeleteShader(shad->shaderID);
}


/**
 * Fonction de compilation d'un shader
 * @param  vertexFilePath
 * @param  fragmentFilePath
 * @return Id du shader GLuint
 */
GLuint LoadShader(const char* vertexFilePath, const char* fragmentFilePath)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Chargement du fichier VertexShader
	int filesizeVertex = 0;
	char* vertexCode = NULL;
	FILE* vertexFile = fopen(vertexFilePath, "rb");
	if(vertexFile != NULL)
	{
		// Detection de la taille du fichier
		fseek(vertexFile, 0, SEEK_END);	// met le curseur a la fin du fichier
		filesizeVertex = ftell(vertexFile);	// retourne la position du curseur
		rewind(vertexFile);

		// Allocation de la mémoire pour son utilisation ('+1' bite de fin EOF EndOfFile)
		vertexCode = (char*)malloc( sizeof(char) * (filesizeVertex + 1));

		// Lecture du fichier et mise de celui ci dans vertexCode
		fread(vertexCode, 1, filesizeVertex, vertexFile);
		vertexCode[filesizeVertex] = '\0';

		// fermeture du fichier
		fclose(vertexFile);
	}
	else{
		printf("[ERROR]\tError while loading VertexShader: %s\n", vertexFilePath);
		exit(1);
	}


	// Chargement du fichier FragmentShader
	int filesizeFragment = 0;
	char* fragmentCode = NULL;
	FILE* fragmentFile = fopen(fragmentFilePath, "rb");
	if(fragmentFile != NULL)
	{
		// Detection de la taille du fichier
		fseek(fragmentFile, 0, SEEK_END);
		filesizeFragment = ftell(fragmentFile);
		rewind(fragmentFile);

		// Allocation de la mémoire pour son utilisation (+1 bite de fin)
		fragmentCode = (char*)malloc(sizeof(char)* (filesizeFragment + 1));

		// Lecture du fichier et mise de celui ci dans vertexCode
		fread(fragmentCode, 1, filesizeFragment, fragmentFile);
		fragmentCode[filesizeFragment] = '\0';

		// Fermeture du fichier
		fclose(fragmentFile);
	}
	else{
		printf("[ERROR]\tError while loading FragmentShader: %s\n", fragmentFilePath);
		exit(1);
	}

	// Compilation du Vertex shader
	glShaderSource(VertexShaderID, 1, &vertexCode, NULL);
	glCompileShader(VertexShaderID);
		// Verification d'erreur
		int param = 0;
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &param);
		if(param != GL_TRUE)
		{
			printf("[ERROR]\tError VertexShader[%i] not compiled : %s\n", VertexShaderID, vertexFilePath);
			printShaderLog(VertexShaderID);
			return -1;
		}

	//Compilation du Fragment Shader
	glShaderSource(FragmentShaderID, 1, &fragmentCode, NULL);
	glCompileShader(FragmentShaderID);
		// Verification d'erreur
		param = 0;
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &param);
		if(param != GL_TRUE)
		{
			printf("[ERROR]\tError FragmentShader[%i] not compiled : %s\n", FragmentShaderID, fragmentFilePath);
			printShaderLog(FragmentShaderID);
			return -1;
		}

	// Creation du programme et linkage de celui ci dans la memoire de la GPU
	GLuint programShader = glCreateProgram();
	glAttachShader(programShader, VertexShaderID);
	glAttachShader(programShader, FragmentShaderID);
	glLinkProgram(programShader);

	free(vertexCode);
	free(fragmentCode);

	return programShader;
}

/**
 * Affichage des erreur suite a l'echec de compilation d'un shader.
 * @param shader
 */
void printShaderLog(GLuint shader)
{
  int max_length = 2048;
  int actual_length = 0;
  char log[2048];
  glGetShaderInfoLog (shader, max_length, &actual_length, log);
  printf ("shader info log for GL index %u:\n%s\n", shader, log);
  //getc();
  exit(1);
}
