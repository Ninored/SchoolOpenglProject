#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>

void CAM_Init(void);	// fonction d'initialisation
void CAM_Restart(void); // fonction de réinitialisation

void CAM_Forward(GLfloat val); // deplacement frontales
void CAM_Right(GLfloat val); // deplacements latérales

void CAM_Pitch(GLfloat val); // Rotation axeX
void CAM_Yaw(GLfloat val); //Rotation axeY

#endif // CAMERA_H