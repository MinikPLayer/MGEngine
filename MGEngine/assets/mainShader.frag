#version 450

layout (location = 0) in vec3 FragPos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 UV;

layout (location = 0) out vec4 FragColor;

void main() {
	// FragColor = vec4(Normal, 1.0);
	// FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	 float x = float(int(FragPos.x * 1000) % 1000) / 1000;
	 float y = float(int(FragPos.y * 1000) % 1000) / 1000;
	 float z = float(int(FragPos.z * 1000) % 1000) / 1000;
//	float x = Normal.x;
//	float y = Normal.y;
//	float z = Normal.z;

//	FragColor = vec4(x, y, z, 1.0);
	 FragColor = vec4(1.0, 0.0, 0.0, 1.0) * vec4(Normal, 1.0);
}