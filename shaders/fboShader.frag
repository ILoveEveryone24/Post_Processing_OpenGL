#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
	if(gl_FragCoord.x < 400 || gl_FragCoord.x > 800){
		FragColor = texture(screenTexture, TexCoords);
	}
	else{
		FragColor = texture(screenTexture, TexCoords)*0.4;
	}
}
