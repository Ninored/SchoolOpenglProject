#version 400
// #extension GL_ARB_explicit_attrib_location : require

layout(location = 0)in vec3 vert;
layout(location = 1)in vec3 colorVertex;

uniform mat4 PerspectiveMatrix;
uniform mat4 CameraMatrix;


out vec3 colorFragment;

mat4 MVP;

void main() {
	MVP = PerspectiveMatrix * CameraMatrix;
	gl_Position = MVP * vec4(vert, 1.0);
	colorFragment = colorVertex;
}
