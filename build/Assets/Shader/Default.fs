#version 400

// Structure matériaux
struct Material {
	float Ns;
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
};
uniform Material material;

// structure lumière
struct Light {
	float intensity;
	vec3 pos;
	vec3 direction; // Pour les spotes

	vec3 diffuse;
};
uniform Light light;

uniform mat4 CameraMatrix;
uniform vec3 CameraPos;

in vec4 Color;
in vec3 Normal;
in vec3 Position;
//in vec3 camPos;

out vec4 ColorOut;


vec3 tmpSpecular = vec3(0.7,0.7,0.0);

void main() {
//	vec3 lightPos =  vec3(CameraMatrix * vec4(light.pos, 1.0));
	vec3 lightPos = light.pos;

	vec3 n = normalize(Normal);
	vec3 l =  normalize(lightPos - Position);

	vec3 Cdiff = light.diffuse * max(0.0, dot(n, l));
	Cdiff = clamp(Cdiff, 0.0, 1.0);

	vec3 vue = normalize(CameraPos - Position);
	vec3 reflection = normalize(reflect(l, n));
	vec3 Cspec;
	if(dot(l, n) < 0.0)
	{
		Cspec = vec3(0.0);
	}
	else
	{

		Cspec = tmpSpecular * pow( max(0.0, dot(vue, reflection)), 16);
		Cspec = clamp(Cspec, 0.0, 1.0);
	}

	vec4 Cfinal = vec4(Cdiff, 1.0) + vec4(Cspec, 1.0);
	ColorOut = vec4(5.0,5.0,5.0,1.0);
	ColorOut = Cfinal;
}
