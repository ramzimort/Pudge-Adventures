#include "GraphicsManager.h"
#include <Windows.h>
#include <SDL2\SDL.h>
#include "Resource Manager.h"
#include "Input Manager.h"
#include "GameObjectManager.h"
#include "..\Components\Sprite.h"
#include "..\Components\Transform.h"
#include "..\Components\Body.h"
#include "..\Components\Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/constants.hpp>


extern ResourceManager* gpResourceManager;
extern GameObjectManager* gpGameObjectManager;
extern Input_Manager* gpInputManager;


Shader::Shader(const char* vertexShaderName, const char* fragmentShaderName)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertShaderPath = vertexShaderName; vertShaderPath = "Shaders\\" + vertShaderPath;
	std::string fragShaderPath = fragmentShaderName; fragShaderPath = "Shaders\\" + fragShaderPath;

	std::string vertexCode = loadFile(vertShaderPath);
	std::string fragmentCode = loadFile(fragShaderPath);

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	Program = glCreateProgram();
	glAttachShader(Program, vertexShader);
	glAttachShader(Program, fragmentShader);
	glLinkProgram(Program);
	// check for linking errors
	glGetProgramiv(Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(Program);
}
void Shader::use()
{
	glUseProgram(Program);
}
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(Program, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(Program, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(Program, name.c_str()), value);
}
std::string Shader::loadFile(std::string& filePath) {
	std::string out;
	std::string	line;
	std::ifstream in(filePath.c_str());
	getline(in, line);
	while (in) {
		out += line + "\n";
		getline(in, line);
	}
	return out;
}

GraphicsManager::GraphicsManager()
{
	Init();
}
GraphicsManager::~GraphicsManager() 
{
	glDeleteBuffers(3, VAO);
	glDeleteBuffers(3, vertBuffer);
	glDeleteBuffers(3, faceBuffer);
	glDeleteBuffers(1, &textureBuffer);
	delete textureShader;
	delete polygonShader;

	SDL_GL_DeleteContext(context);
	SDL_Quit();
}
void GraphicsManager::Init()
{
	AllocateConsole();
	InitSDLWindow();
	textureShader = new Shader("TextureShader.vert", "TextureShader.frag");
	polygonShader = new Shader("TextureShader.vert", "PolygonShader.frag");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	apersp_matrix = glGetUniformLocation(textureShader->Program, "persp_matrix");
	aview_matrix = glGetUniformLocation(textureShader->Program, "view_matrix");
	amodel_matrix = glGetUniformLocation(textureShader->Program, "model_matrix");

	CreateQuadBuffer();
}
void GraphicsManager::Update()
{
	clearColor();
	if (gpInputManager->isTriggered(SDL_SCANCODE_TAB))
		debugModeFlag = !debugModeFlag;

	// Update all game objects
	for (auto go : gpGameObjectManager->mGameObjects)
		Draw(go);
	
	refreshWindow();
}
void GraphicsManager::Draw(GameObject* go)
{
	Transform* pTr = static_cast<Transform*>(go->GetComponent(TRANSFORM));
	Sprite* pSpr = static_cast<Sprite*>(go->GetComponent(SPRITE));
	if (pTr != nullptr && pSpr != nullptr)
	{
		textureShader->use();
		glBindVertexArray(VAO[0]);

		/* TEXTURE START */
		float textCoords[] = {
			 1.0f, 1.0f,  // top right
			 1.0f, 0.0f,  // bottom right
			 0.0f, 0.0f,  // bottom left
			 0.0f, 1.0f,  // top left 
		};
		glBindTexture(GL_TEXTURE_2D, pSpr->mpTexture->textureID);
		glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textCoords), textCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(aTexCoord);
		/* TEXTURE END */

		/* TRANSFORM START */
		glm::mat4 Model = 
			glm::translate(glm::mat4(), glm::vec3(pTr->mPosition.x, pTr->mPosition.y, 0.0f))*
			glm::scale(glm::mat4(), glm::vec3(pTr->mScale.x, pTr->mScale.y, 0.0f))*
			glm::translate(glm::mat4(), glm::vec3(pTr->mRotationCenter.x, pTr->mRotationCenter.y, 0.0f))*
			glm::rotate(glm::mat4(), pTr->mAngle, glm::vec3(0.0f, 0.0f, 1.0f))*
			glm::translate(glm::mat4(), glm::vec3(-1.f*pTr->mRotationCenter.x, -1.f*pTr->mRotationCenter.y, 0.0f));

		glm::mat4 Persp = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);

		Camera* pCamera = static_cast<Camera*>(go->GetComponent(CAMERA));
		if (pCamera != nullptr)
			camPosition = glm::vec3(pCamera->mCameraCenter.x - SCR_WIDTH / 2.0f, pCamera->mCameraCenter.y - SCR_HEIGHT / 2.0f, 1.0f);
		glm::mat4 View = glm::lookAt(camPosition, camPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(amodel_matrix, 1, false, (float*)&Model);
		glUniformMatrix4fv(apersp_matrix, 1, false, (float*)&Persp);
		glUniformMatrix4fv(aview_matrix, 1, false, (float*)&View);
		/* TRANSFORM END */
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Debug Mode:
		if (debugModeFlag)
		{
			Body* pBody = static_cast<Body*>(go->GetComponent(BODY));
			if (pBody != nullptr)
			{
				polygonShader->use();
				glUniformMatrix4fv(apersp_matrix, 1, false, (float*)&Persp);
				glUniformMatrix4fv(aview_matrix, 1, false, (float*)&View);
				
				if (pBody->mpShape->mType == AABB)
				{					
					ShapeAABB* pShape = static_cast<ShapeAABB*>(pBody->mpShape);
					Model = 
						glm::translate(glm::mat4(), glm::vec3(pBody->mColliderCenter.x, pBody->mColliderCenter.y,  0.f))*
						glm::scale(glm::mat4(), glm::vec3(pShape->mWidth, pShape->mHeight, 0.0f));
						
					glUniformMatrix4fv(amodel_matrix, 1, false, (float*)&Model);
					glBindVertexArray(VAO[1]);
					glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
				}
				else if (pBody->mpShape->mType == CIRCLE)
				{
					ShapeCircle* pShape = static_cast<ShapeCircle*>(pBody->mpShape);
					Model =
						glm::translate(glm::mat4(), glm::vec3(pBody->mColliderCenter.x, pBody->mColliderCenter.y, 0.f))*
						glm::scale(glm::mat4(), glm::vec3(2 * pShape->mRadius, 2 * pShape->mRadius, 0.0f));
					glUniformMatrix4fv(amodel_matrix, 1, false, (float*)&Model);
					glBindVertexArray(VAO[2]);
					glDrawElements(GL_LINES, 40, GL_UNSIGNED_INT, 0);
				}				
			}
		}
	}	
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

	pWindow = SDL_CreateWindow("Pudge Adventures",					// window title
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
		 0.5f,  0.5f,  // top right
		 0.5f, -0.5f,  // bottom right
		-0.5f, -0.5f,  // bottom left
		-0.5f,  0.5f,  // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	
	unsigned int quadIndices[] = {  // note that we start from 0!
	0, 1, 
	1, 2, 
	2, 3, 
	3, 0
	};

	const int numVertices = 20;
	float circleVertices[2* numVertices];
	unsigned int circleIndices[2 * numVertices];
	float toRad = (float) glm::radians(360.f / numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		circleVertices[2 * i] =		0.5f*cosf(i*toRad);
		circleVertices[2 * i + 1] =	0.5f*sinf(i*toRad);
		circleIndices[2 * i] = i;
		circleIndices[2 * i + 1] = i + 1;
	}
	circleIndices[2*numVertices - 1] = 0;

	glGenVertexArrays(3, VAO);
	glGenBuffers(3, vertBuffer);
	glGenBuffers(3, faceBuffer);
	glGenBuffers(1, &textureBuffer);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(aPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(aPos);

	// note that this is allowed, the call to glVertexAttribPointer registered vertBuffer as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(aPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(aPos);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circleIndices), circleIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(aPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(aPos);
}
void GraphicsManager::clearColor()
{
	glClearColor(0.53f, 0.807f, 0.9215f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
}
void GraphicsManager::refreshWindow()
{
	SDL_GL_SwapWindow(pWindow);
}