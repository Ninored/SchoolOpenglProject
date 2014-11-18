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

	vec3 ambiant;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

uniform mat4 CameraMatrix;
uniform vec3 CameraPos;

in vec4 Color;
in vec3 Normal;
in vec3 Position;

out vec4 ColorOut;

void main() {
	// Transformation du repère (Camera au centre 0,0,0)
	vec3 lightPos = vec3( CameraMatrix * vec4(light.pos, 1.0));
	
	// Précalcule des vecteurs necessaire
	vec3 E  = normalize(-Position);
	vec3 N = normalize(Normal);
	vec3 L = normalize(lightPos - Position);
	vec3 R = normalize(reflect(-L, N));

	// Calcul de la lummière ambiante
	vec3 Camb = light.ambiant * material.Ka;
	Camb = clamp(Camb, 0.0, 1.0);

	// Calcul de la lumière diffuse
	vec3 Cdiff = material.Kd * light.diffuse * max(0.0, dot(L, N));
	Cdiff = clamp(Cdiff, 0.0, 1.0);

	//Calcul de la lumière spéculaire 
	vec3 Cspec;
	if(dot(L,N) < 0) // Vérif direction de vue
	{
		// Si la camera pointe dans la direction contraire
		// a la lumière pas de lumière spéculaire.
		// (évite la présence de lumière spéculaire a l'arrière d'un objet)
		Cspec = vec3(0.0);
	}
	else
	{
		// Si tout est OK Calcul
		Cspec = light.specular * material.Ks * pow( max( 0.0, dot(E, R)), material.Ns);
		Cspec = clamp(Cspec, 0.0, 1.0);
	}

	// Adition de tout les lumières
	vec4 Cfinal = (vec4(Camb, 1.0) + vec4(Cdiff, 1.0) + vec4(Cspec,1.0)) * light.intensity;
	ColorOut = Cfinal;
}
