#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aUV;

layout (location = 0) out vec3 FragPos;
layout (location = 1) out vec2 UV;

void main() {
	gl_Position = vec4(aPos, 1.0);
	FragPos = aPos;
	UV = aUV;
}