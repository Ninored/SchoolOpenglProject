#version 400
// #extension GL_ARB_explicit_attrib_location : require

layout(location = 0)in vec3 vert;
layout(location = 1)in vec3 colorVertex;

//attribute vec3 vert;
//attribute vec3 colorVertex;

out vec3 colorFragment;

void main() {
	gl_Position = vec4(vert, 1);
	colorFragment = colorVertex;
}
