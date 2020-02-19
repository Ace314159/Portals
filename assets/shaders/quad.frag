#version 330

out vec4 FragColor;

uniform vec4 color;

void main() {
	if(color.a == 0) discard;
	FragColor = color;
}