#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 norm;
out vec3 objpos;

void main(){
	gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);
	norm = aNorm;
	objpos = vec3(model * vec4(aPos.xyz, 1.0));
}