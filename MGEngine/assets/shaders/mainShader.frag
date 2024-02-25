#version 450

layout (location = 0) in vec3 FragPos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UV;

layout (location = 0) out vec4 FragColor;

void main() {
	 FragColor = vec4(Normal, 1.0);
}