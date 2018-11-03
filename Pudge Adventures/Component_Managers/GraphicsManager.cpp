#include "GraphicsManager.h"
#include <Windows.h>
#include <SDL2\SDL.h>
#include <iostream>
#include "..\Components\Shader.h"
#include "Resource Manager.h"
#include "..\Components\Sprite.h"
#include "..\Components\Transform.h"
#include "..\Components\TextureObject.h"

#include <glm/gtc/matrix_transform.hpp>


extern ResourceManager* gpResourceManager;

GraphicsManager::GraphicsManager()
{
	AllocateConsole();
	InitSDLWindow();
	programShader = new Shader("VertShader.txt", "FragShader.txt");
	

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	apersp_matrix = glGetUniformLocation(programShader->Program, "persp_matrix");
	aview_matrix = glGetUniformLocation(programShader->Program, "view_matrix");
	amodel_matrix = glGetUniformLocation(programShader->Program, "model_matrix");

	CreateQuadBuffer();
}

GraphicsManager::~GraphicsManager() 
{
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &vertBuffer);
	glDeleteBuffers(1, &faceBuffer);
	glDeleteBuffers(1, &textureBuffer);
	delete programShader;

	SDL_GL_DeleteContext(context);
	SDL_Quit();
}



void GraphicsManager::Draw(GameObject* go)
{

	programShader->use();
	glBindVertexArray(VAO);

	/* TEXTURE START */
	float textCoords[] = {
		 1.0f, 1.0f,  // top right
		 1.0f, 0.0f,  // bottom right
		 0.0f, 0.0f,  // bottom left
		 0.0f, 1.0f,  // top left 
	};
	glBindTexture(GL_TEXTURE_2D, static_cast<Sprite*>(go->GetComponent(SPRITE))->mpTexture->textureID);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textCoords), textCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(aTexCoord);
	/* TEXTURE END */

	/* TRANSFORM START */
	Transform* pTr = static_cast<Transform*>(go->GetComponent(TRANSFORM));
	glm::mat4 Model =	glm::translate(glm::mat4(), pTr->mPosition)*
						glm::rotate(glm::mat4(), glm::radians(pTr->mAngle), glm::vec3(0.0f, 0.0f, 1.0f))*
						glm::scale(glm::mat4(), pTr->mScale);
	glUniformMatrix4fv(amodel_matrix, 1, false, (float*)&Model);

	glm::mat4 Persp = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT), 0.1f,100.0f);
	glUniformMatrix4fv(apersp_matrix, 1, false, (float*)&Persp);

	glm::vec3 camPosition = glm::vec3(0.0f, -(float)SCR_HEIGHT/2.0f, 1.0f);
	glm::mat4 View = glm::lookAt(camPosition, camPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(aview_matrix, 1, false, (float*)&View);
	/* TRANSFORM END */

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool GraphicsManager::isError()
{
	return errorFlag;
}

std::string GraphicsManager::getError()
{
	return errorString;
}

void GraphicsManager::AllocateConsole()
{
	if (AllocConsole())
	{
		FILE* file;
		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}
}

void GraphicsManager::InitSDLWindow()
{
	int error = 0;
	error = SDL_Init(SDL_INIT_VIDEO);
	if (error < 0)				// Initialize SDL
	{
		errorFlag = true;
		errorString = "Couldn't initialize SDL, error: " + std::to_string(error);
		std::cout << errorString << std::endl;
		system("Pause");
		return;
	}

	SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.
	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	pWindow = SDL_CreateWindow("SDL2 window",					// window title
		SDL_WINDOWPOS_UNDEFINED,								// initial x position
		SDL_WINDOWPOS_UNDEFINED,								// initial y position
		SCR_WIDTH,													// width, in pixels
		SCR_HEIGHT,													// height, in pixels
		SDL_WINDOW_OPENGL);
	if (pWindow == NULL)										// Check that the window was successfully made
	{
		errorFlag = true;
		errorString = "Could not create window: " + std::string(SDL_GetError());
		std::cout << errorString << std::endl;
		return;
	}

	context = SDL_GL_CreateContext(pWindow);
	if (context == NULL)
	{
		errorFlag = true;
		errorString = "Failed to create OpenGL context: " + std::string(SDL_GetError());
		std::cout << errorString << std::endl;
		return;
	}

	printf("OpenGL loaded\n");
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));
	SDL_GL_SetSwapInterval(1);
}

void GraphicsManager::CreateQuadBuffer()
{
	// set up vertex buffer for quad
// ------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertBuffer);
	glGenBuffers(1, &faceBuffer);
	glGenBuffers(1, &textureBuffer);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(aPos);

	// note that this is allowed, the call to glVertexAttribPointer registered vertBuffer as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GraphicsManager::clearColor()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsManager::refreshWindow()
{
	SDL_GL_SwapWindow(pWindow);
}