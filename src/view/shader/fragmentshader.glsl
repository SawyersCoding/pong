#version 330 core

in vec3 norm;
in vec3 objpos;

uniform vec3 objcolor;
uniform vec3 lightcolor;
uniform vec3 lightPos;

out vec4 FragColor;

void main(){
	float ambient_strength = 0.1;
	vec3 ambient = lightcolor * ambient_strength;
	
	vec3 n = normalize(norm);
	vec3 lightDir = normalize(lightPos - objpos);

	float diff = max(dot(n, lightDir), 0.0);
	vec3 diffuse = diff * lightcolor;

	vec3 result = objcolor * (ambient + diffuse);
	FragColor = vec4(result, 1.0f);
}