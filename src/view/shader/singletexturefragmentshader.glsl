#version 330 core

in vec2 TexCoord;

uniform sampler2D digit_texture;

out vec4 FragColor;

void main(){
	FragColor = texture(digit_texture, TexCoord);
}