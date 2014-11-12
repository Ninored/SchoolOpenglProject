#include "Model.h"
#include "Camera.h"
#include "WavefrontLoader.h"
#include "Light.h"

#include <stdio.h>

void MODEL_Load(Model *model, const char* filepath, const char* vertexShader, const char* fragmentShader)
{
	WAVEFRONT_Load(model, filepath);
	SH_Load(&model->shader, vertexShader, fragmentShader);
}

void MODEL_Free(Model *model)
{
	glDeleteBuffers(1, &model->vbo); // vbo free
	glDeleteBuffers(1, &model->tbo); // tbo free // TODO: ID:T:0.2 a remplacer par le texture plus tard
	glDeleteBuffers(1, &model->nbo); // nbo free
	glDeleteVertexArrays(1, &model->vao); // vao free
	glDeleteProgram(model->shader.shaderID); // shader free
	                                
}

void MODEL_Display(Model *model)
{
	
	glUseProgram(model->shader.shaderID);
	
	// envoi des info camera au shader
	CAM_Display(model);
	//envoi des info material au shader
	glProgramUniform1f(model->shader.shaderID, model->shader.UniformNs, model->material.Ns);
	glProgramUniform3f(model->shader.shaderID, model->shader.UniformKa, model->material.Ka[0], model->material.Ka[1], model->material.Ka[2]);
	glProgramUniform3f(model->shader.shaderID, model->shader.UniformKd, model->material.Kd[0], model->material.Kd[1], model->material.Kd[2]);
	glProgramUniform3f(model->shader.shaderID, model->shader.UniformKs, model->material.Ks[0], model->material.Ks[1], model->material.Ks[2]);

	glBindVertexArray(model->vao);
	int size;  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawArrays(GL_TRIANGLES, 0, ((size) / sizeof(GL_FLOAT)));
	glBindVertexArray(0);
}

void MODEL_TEST_Triangle(Model *model)
{
	GLfloat vertex[9] = {
		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f
		};

	GLfloat color[9] = {
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f
		};

	glGenBuffers(1, &model->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model->tbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &model->vao);
	glBindVertexArray(model->vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model->tbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	glBindVertexArray(0);

	SH_Load(&model->shader, "./Assets/Shader/Default.vs", "./Assets/Shader/Default.fs");
}


void MODEL_TEST_Cube(Model *model)
{
	GLfloat vertex[] = {
		// face 1
		0,0,0,
		0,1,0,
		1,0,0,
		1,0,0,
		1,1,0,
		0,1,0,

		//face 2
		0,0,1,
		0,1,1,
		1,0,1,
		1,0,1,
		1,1,1,
		0,1,1,

		//face 3
		1,0,0,
		1,0,1,
		1,1,0,
		1,1,0,
		1,0,1,
		1,1,1,

		0,0,0,
		0,0,1,
		0,1,0,
		0,1,0,
		0,0,1,
		0,1,1,

		0,1,0,
		0,1,1,
		1,1,0,
		1,1,0,
		0,1,1,
		1,1,1,

		0,0,0,
		0,0,1,
		1,0,0,
		1,0,0,
		0,0,1,
		1,0,1
		};

	GLfloat color[] = {
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f
		};

	glGenBuffers(1, &model->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model->tbo);
	glBindBuffer(GL_ARRAY_BUFFER, model->tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &model->vao);
	glBindVertexArray(model->vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model->tbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	SH_Load(&model->shader, "./Assets/Shader/Default.vs", "./Assets/Shader/Default.fs");
}