#version 330 core

out vec4 FragColor;

void main()
{
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	FragColor = vec4(lightColor, 1.0);
}
