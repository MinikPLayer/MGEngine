#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 VP;
layout (location = 2) uniform mat4 modelInvTrans;

layout (location = 0) out vec3 FragPos;
layout (location = 1) out vec3 Normal;
layout (location = 2) out vec2 UV;

void main() {
	UV = aUV;
	Normal = mat3(modelInvTrans) * aNormal;

	FragPos = vec3(model * vec4(aPos, 1.0));
	gl_Position = VP * vec4(FragPos, 1.0);
}