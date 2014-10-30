#include "Model.h"
#include "Camera.h"

void MODEL_Load(Model *model, const char* shadersFiles)
{

}

void MODEL_Display(Model *model)
{
	
	glUseProgram(model->shader.shaderID);
	CAM_Display(model);

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

	glGenBuffers(1, &model->vco);
	glBindBuffer(GL_ARRAY_BUFFER, model->vco);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &model->vao);
	glBindVertexArray(model->vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model->vco);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	glBindVertexArray(0);

	SH_Load(&model->shader, "./Assets/Shader/Default.vs", "./Assets/Shader/Default.fs");
}


// TODO: ID:T:0.1
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

		//face 4
		0,0,0,
		0,0,1,
		0,1,0,
		0,1,0,
		0,0,1,
		0,1,1,

		//face 5
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

	glGenBuffers(1, &model->vco);
	glBindBuffer(GL_ARRAY_BUFFER, model->vco);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &model->vao);
	glBindVertexArray(model->vao);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model->vco);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	SH_Load(&model->shader, "./Assets/Shader/Default.vs", "./Assets/Shader/Default.fs");
}