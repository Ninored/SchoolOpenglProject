#include "Camera.h"
#include "Matrix.h"
#include "GameState.h"
#include <math.h>

static Mat4f cameraMatrixMove;
static Mat4f cameraMatrixRot;
static Mat4f cameraMatrixRotYaw;
static Mat4f cameraMatrixRotPitch;

static Mat4f cameraMatrix;
static Mat4f projectionMatrix;

/* Variables propre a la position et direction de la camera*/
static GLfloat Pitch;
static GLfloat Yaw;

//static const float degrad = 3.141592654 / 180;

/**
 * TODO:
 * ID:T:0.1
 * Créer une fonction quit
 */


void CAM_Init(void)
{
	// initialisation des matricees.
	MAT_Identity(cameraMatrixMove);
	MAT_Identity(cameraMatrixRot);
	MAT_Identity(cameraMatrixRotYaw);
	MAT_Identity(cameraMatrixRotPitch);

	MAT_Identity(cameraMatrix);
	MAT_Identity(projectionMatrix);
	//Pitch = Yaw = 0;

	// Création de la matrice de projection.
	MAT_Projection(projectionMatrix, WINDOWS_W, WINDOWS_H, 100, 0.1f, 45);
}	

void CAM_Display(Model *model)
{
	MAT_Mult(cameraMatrixRot, cameraMatrixRotPitch, cameraMatrixRotYaw);
	MAT_Mult(cameraMatrix, cameraMatrixRot, cameraMatrixMove);

//	MAT_Print(projectionMatrix);

	glUniformMatrix4fv(model->shader.UniformPerspectiveMatrix, 1, GL_TRUE, &projectionMatrix);
	glUniformMatrix4fv(model->shader.UniformCamMatrix, 1, GL_TRUE, &cameraMatrix);
}

void CAM_Restart(void)
{
	MAT_Identity(cameraMatrix);
}

void CAM_RebuildProjection(void)
{
	MAT_Projection(projectionMatrix, WINDOWS_W, WINDOWS_H, 1000, 0.1f, 45);
}


void CAM_Forward(GLfloat val)
{
	// trigonométrie de base
	float posX = cos((Yaw + 90) * degrad) * val;
	float posZ = sin((Yaw + 90) * degrad) * val;
	MAT_Translate(cameraMatrixMove, posX, 0, posZ);
}

void CAM_Right(GLfloat val)
{
	// trigonométrie de base
	float posX = cos(Yaw * degrad) * val;
	float posZ = sin(Yaw * degrad) * val;
	MAT_Translate(cameraMatrixMove, -posX, 0, -posZ);
}


void CAM_Pitch(GLfloat val)
{
	Pitch += 0.1f * val;
	if(Pitch > 89)
		Pitch = 89;
	if(Pitch < -89)
		Pitch = -89;
	MAT_Rotate(cameraMatrixRotPitch, Pitch, 1, 0, 0);
}

void CAM_Yaw(GLfloat val)
{
	Yaw += 0.1f * val;
	if(Yaw > 360)
		Yaw = 0;
	if(Yaw < 0)
		Yaw = 360;
	MAT_Rotate(cameraMatrixRotYaw, Yaw, 0, 1, 0);
}