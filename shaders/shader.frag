#version 330 core

out vec4 FragColor;

in vec3 color;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	
	float ambientStrength = 0.1;
	vec3 ambient = lightColor * ambientStrength;

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = objectColor * (ambient+diffuse+specular) * color;
	FragColor = vec4(result, 1.0);
}
