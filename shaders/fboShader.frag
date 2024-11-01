#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform int inverse;
uniform int blur;
uniform int g_blur;
uniform sampler2D screenTexture;

const float offset = 1.0 / 150;
const float PI = 3.141592653589793;

vec3 inverse_func(){
	vec3 col = vec3(1.0 - texture(screenTexture, TexCoords));
	return col;
}

vec3 blur_func(){
	vec2 offsets[25] = vec2[](
		vec2(-offset * 2, offset * 2),  // 0, 0
		vec2(-offset * 2, offset),      // 0, 1
		vec2(-offset * 2, 0.0f),        // 0, 2
		vec2(-offset * 2, -offset),     // 0, 3
		vec2(-offset * 2, -offset * 2), // 0, 4
		vec2(-offset, offset * 2),      // 1, 0
		vec2(-offset, offset),          // 1, 1
		vec2(-offset, 0.0f),            // 1, 2
		vec2(-offset, -offset),         // 1, 3
		vec2(-offset, -offset * 2),     // 1, 4
		vec2(0.0f, offset * 2),         // 2, 0
		vec2(0.0f, offset),             // 2, 1
		vec2(0.0f, 0.0f),               // 2, 2
		vec2(0.0f, -offset),            // 2, 3
		vec2(0.0f, -offset * 2),        // 2, 4
		vec2(offset, offset * 2),       // 3, 0
		vec2(offset, offset),           // 3, 1
		vec2(offset, 0.0f),             // 3, 2
		vec2(offset, -offset),          // 3, 3
		vec2(offset, -offset * 2),      // 3, 4
		vec2(offset * 2, offset * 2),   // 4, 0
		vec2(offset * 2, offset),       // 4, 1
		vec2(offset * 2, 0.0f),         // 4, 2
		vec2(offset * 2, -offset),      // 4, 3
		vec2(offset * 2, -offset * 2)   // 4, 4
	);

	vec3 sampleTex[25];
	for(int i = 0; i < 25; i++)
	{
		sampleTex[i] = vec3(texture(screenTexture, TexCoords + offsets[i]));
	}

	vec3 col = vec3(0.0);
	for(int i = 0; i < 25; i++){
		col += sampleTex[i];
	}
	col /= 25;

	return col;
}

void test_func(){
	vec2 offsets[9] = vec2[](
		vec2(-offset,  offset), // top-left
		vec2( 0.0f,    offset), // top-center
		vec2( offset,  offset), // top-right
		vec2(-offset,  0.0f),   // center-left
		vec2( 0.0f,    0.0f),   // center-center
		vec2( offset,  0.0f),   // center-right
		vec2(-offset, -offset), // bottom-left
		vec2( 0.0f,   -offset), // bottom-center
		vec2( offset, -offset)  // bottom-right    
	);
	float kernel[9] = float[](
		 4,  0,  0,
		 0,  0,  0,
		 0,  0, -4
	    );

	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(screenTexture, TexCoords + offsets[i]));
	}

	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; i++){
		col += sampleTex[i] * kernel[i];
	}
	//col /= 9;

	FragColor = vec4(col, 1.0);
}
		
vec3 g_blur_func(float standard_dev){
	vec3 sampleTex = vec3(0.0);
	float weights = 0.0;
	int kernelSize = 4;
	for(int x = -kernelSize; x <= kernelSize; x++) {
		for(int y = -kernelSize; y <= kernelSize; y++) {
			vec2 current_pixel = TexCoords + vec2(x * offset, y * offset);
			float weight = (1.0/(2*PI*pow(standard_dev, 2.0))) * (exp(-((pow(x, 2.0) + pow(y, 2.0)) / (2.0 * pow(standard_dev, 2.0)))));

			sampleTex += vec3(texture(screenTexture, current_pixel)) * weight;
			weights += weight;
		}
	}
	vec3 col = vec3(0.0);

	if(weights > 0.0){
		col = sampleTex / weights;
	}
	else{
		col = sampleTex;
	}

	return col;
}

void main()
{
	vec3 col;
	if(inverse != 0){
		col = inverse_func();
		FragColor = vec4(col, TexCoords);
	}
	else if(blur != 0){
		col = blur_func();
		FragColor = vec4(col, TexCoords);
	}
	else if(g_blur != 0){
		col = g_blur_func(4.0);
		FragColor = vec4(col, TexCoords);
	}
	else{
		FragColor = texture(screenTexture, TexCoords);
	}
}
