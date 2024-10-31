#include <iostream>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "shaders/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

const int WIDTH = 1280;
const int HEIGHT = 720;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

struct Vertex{
	glm::vec3 position;
	glm::vec3 normal;
};

int main(){
	unsigned int VBO, VAO, EBO;
	unsigned int lightVBO, lightVAO, lightEBO;
	unsigned int fboVBO, fboVAO;

	float fboQuad[24] ={
		-1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
	};
	
	std::vector<Vertex> vertices;
	std::vector<glm::uvec3> indices;

	std::vector<Vertex> lightVertices;
	std::vector<glm::uvec3> lightIndices;
	//Floor
	vertices.push_back({glm::vec3(-1.0f, -1.0f, 0.501f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(-1.0f, 1.0f, 0.501f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(1.0f, -1.0f, 0.501f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(-1.0f, 1.0f, 0.501f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(1.0f, -1.0f, 0.501f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(1.0f, 1.0f, 0.501f), glm::vec3(0.0f, 1.0f, 0.0f)});

	vertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	vertices.push_back({glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	vertices.push_back({glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	vertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	vertices.push_back({glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	vertices.push_back({glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	vertices.push_back({glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	vertices.push_back({glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	vertices.push_back({glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	vertices.push_back({glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0, 0.0f)});


	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	lightVertices.push_back({glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	lightVertices.push_back({glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)});
	lightVertices.push_back({glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0, 0.0f)});

	for(int i = 0; i < vertices.size()/3; i++)
		indices.push_back(glm::uvec3(i*3, i*3+1, i*3+2));

	for(int i = 0; i < lightVertices.size()/3; i++)
		lightIndices.push_back(glm::uvec3(i*3, i*3+1, i*3+2));

	if(SDL_Init(SDL_INIT_VIDEO) > 0){
		std::cout << "SDL_Init ERROR: " << SDL_GetError() << std::endl;	
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window *window = SDL_CreateWindow("Post Processing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(!window){
		std::cout << "Failed to initialize window" << std::endl;
		return -1;	
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if(!glContext){
		std::cout << "Failed to initialize GLContext" << std::endl;
		return -1;	
	}

	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;	
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//Scene buffers
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec3), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	//Light buffers
	glGenBuffers(1, &lightVBO);
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightEBO);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, lightVertices.size() * sizeof(Vertex), lightVertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, lightIndices.size() * sizeof(glm::uvec3), lightIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Framebuffer buffers
	glGenBuffers(1, &fboVBO);
	glGenVertexArrays(1, &fboVAO);

	glBindVertexArray(fboVAO);
	glBindBuffer(GL_ARRAY_BUFFER, fboVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fboQuad), fboQuad, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader sceneShader("./shaders/shader.ver", "./shaders/shader.frag");
	Shader lightShader("./shaders/lightShader.ver", "./shaders/lightShader.frag");
	Shader fboShader("./shaders/fboShader.ver", "./shaders/fboShader.frag");

	//Framebuffer and Texture
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	glBindBuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	GLuint length = (GLuint)indices.size() * 3;
	GLuint lightLength = (GLuint)lightIndices.size() * 3;

	glEnable(GL_DEPTH_TEST);

	bool isRunning = true;
	SDL_Event event;

	//Camera
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 objectColor = glm::vec3(0.7f, 0.3f, 0.4f);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);	
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH/HEIGHT, 0.1f, 100.0f);

	glm::mat4 mvp = proj * view * model;

	glm::mat4 model2 = model;
	model2 = glm::scale(model2, glm::vec3(20.0f, 1.0f, 20.0f));
	model2 = glm::rotate(model2, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 mvp2 = proj * view * model2;

	//Light model
	glm::mat4 lightModel = glm::mat4(1.0f);
	glm::vec3 lightPos = glm::vec3(2.0f, 2.0f, 1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	lightModel = glm::scale(lightModel, glm::vec3(0.4f, 0.4f, 0.4f));

	glm::mat4 lightMvp = proj * view * lightModel;

	GLint mvpLoc = glGetUniformLocation(sceneShader.ID, "mvp");
	GLint mvp2Loc = glGetUniformLocation(sceneShader.ID, "mvp2");
	GLint modelLoc = glGetUniformLocation(sceneShader.ID, "model");
	GLint model2Loc = glGetUniformLocation(sceneShader.ID, "model2");
	GLint objectColorLoc = glGetUniformLocation(sceneShader.ID, "objectColor");
	GLint lightPosLoc = glGetUniformLocation(sceneShader.ID, "lightPos");
	GLint viewPosLoc = glGetUniformLocation(sceneShader.ID, "viewPos");
	GLint lightMvpLoc = glGetUniformLocation(lightShader.ID, "lightMvp");

	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	float yaw = -90.0f;
	float pitch = 0.0f;

	glm::vec3 direction;

	int lastX = WIDTH/2;
	int lastY = HEIGHT/2;
	float sensitivity = 0.1f;
	float speed;
	Uint32 mouseState;

	std::vector<bool*> effects;
	bool inverse = false;
	bool blur = false;
	bool g_blur = false;

	effects.push_back(&inverse);
	effects.push_back(&blur);
	effects.push_back(&g_blur);
	GLint inverseLoc = glGetUniformLocation(fboShader.ID, "inverse");
	GLint blurLoc = glGetUniformLocation(fboShader.ID, "blur");
	GLint g_blurLoc = glGetUniformLocation(fboShader.ID, "g_blur");

	while(isRunning){
		Uint32 currentFrame = SDL_GetTicks();
		deltaTime = (currentFrame - lastFrame) / 1000.0f;
		lastFrame = currentFrame;
		speed = 5.0f * deltaTime;

		mvp = proj * view * model;
		mvp2 = proj * view * model2;
		lightMvp = proj * view * lightModel;
		view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);

		//Framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glClearColor(155.0f/255.0f, 136.0f/255.0f, 120.0f/255.0f, 1.0f);	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);


		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_w)
						cameraPos += cameraFront*speed;
					if(event.key.keysym.sym == SDLK_s)
						cameraPos -= cameraFront*speed;
					if(event.key.keysym.sym == SDLK_a)
						cameraPos -= glm::cross(cameraFront, cameraUp)*speed;
					if(event.key.keysym.sym == SDLK_d)
						cameraPos += glm::cross(cameraFront, cameraUp)*speed;
					if(event.key.keysym.sym == SDLK_SPACE)
						cameraPos += cameraUp*speed;
					
					if(event.key.keysym.sym == SDLK_1)
						for(int i = 0; i < effects.size(); i++)
							if(i == 0)
								*effects[i] = !*effects[i];
							else
								*effects[i] = false;
					if(event.key.keysym.sym == SDLK_2)
						for(int i = 0; i < effects.size(); i++)
							if(i == 1)
								*effects[i] = !*effects[i];
							else
								*effects[i] = false;
					if(event.key.keysym.sym == SDLK_3)
						for(int i = 0; i < effects.size(); i++)
							if(i == 2)
								*effects[i] = !*effects[i];
							else
								*effects[i] = false;
				
					//For screenshots
					//cameraPos = glm::vec3(-0.978296, 1.31187, 5.00944);
					break;
				case SDL_MOUSEMOTION:
					int x, y, offsetX, offsetY;
					mouseState = SDL_GetRelativeMouseState(&x, &y);
					offsetX = x - lastX;
					offsetY = lastY - y;
					lastX = x;
					lastY = y;

					yaw += x * sensitivity;
					pitch += -y * sensitivity;
					if(pitch > 89.0f)
						pitch =  89.0f;
					if(pitch < -89.0f)
						pitch = -89.0f;

					direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
					direction.y = sin(glm::radians(pitch));
					direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

					cameraFront = glm::normalize(direction);

					//For screenshots
					//cameraFront = glm::vec3(0.467069f, -0.101056f, -0.878427f);
				     	break;
				default:
					break;	
			}	
		}
		
		sceneShader.use();
		glBindVertexArray(VAO);
		
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(mvp2Loc, 1, GL_FALSE, &mvp2[0][0]);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(model2Loc, 1, GL_FALSE, &model2[0][0]);
		glUniform3fv(objectColorLoc, 1, &objectColor[0]);
		glUniform3fv(viewPosLoc, 1, &cameraPos[0]);
		glUniform3fv(lightPosLoc, 1, &lightPos[0]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, length, GL_UNSIGNED_INT, 0);

		lightShader.use();
		glBindVertexArray(lightVAO);
		
		glUniformMatrix4fv(lightMvpLoc, 1, GL_FALSE, &lightMvp[0][0]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
		glDrawElements(GL_TRIANGLES, lightLength, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//Drawing quad texture
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		fboShader.use();
		glBindVertexArray(fboVAO);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, texture);

		glUniform1i(inverseLoc, inverse);
		glUniform1i(blurLoc, blur);
		glUniform1i(g_blurLoc, g_blur);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		SDL_GL_SwapWindow(window);
	}

	return 0;
}

