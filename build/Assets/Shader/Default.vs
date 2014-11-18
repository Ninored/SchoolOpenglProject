#version 400
// #extension GL_ARB_explicit_attrib_location : require

layout(location = 0)in vec3 vert;
layout(location = 1)in vec3 textureVertex;
layout(location = 2)in vec3 normalVertex;

uniform mat4 PerspectiveMatrix;
uniform mat4 CameraMatrix;
uniform vec3 CameraPos;

out vec4 Color;
out vec3 Normal;
out vec3 Position;
//out vec3 camPos;

mat4 MVP;

void main() {

	Color = vec4(0, 1.0, 0, 1); // vert
	Position = vec3(CameraMatrix * vec4(vert,1.0));
	Normal   = vec3(CameraMatrix * vec4(normalVertex, 0.0));

	MVP = PerspectiveMatrix * CameraMatrix;
	gl_Position = MVP * vec4(vert, 1.0);
}
