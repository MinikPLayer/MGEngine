#version 450

layout (location = 0) in vec3 FragPos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UV;

layout (location = 0) out vec4 FragColor;

layout (location = 3) uniform sampler2D albedoTexture;

void main() {
	// FragColor = vec4(Normal, 1.0);
	FragColor = texture(albedoTexture, UV);
//	FragColor = vec4(albedoTexture, 0.0, 0.0, 1.0);
}