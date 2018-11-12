#pragma once

#include <GLAD/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <String>
#include <vector>
#include "..\Components\GameObject.h"
#include <glm/glm.hpp>


class Shader;
class Texture;

class GraphicsManager
{
public:
	GraphicsManager();
	virtual ~GraphicsManager();
	void Init();
	void Update();

	void clearColor();
	void refreshWindow();
	void Draw(GameObject* go);
	bool isError();
	std::string getError();

	int getWindowWidth() { return SCR_WIDTH; }
	int getWindowHeight() { return SCR_HEIGHT; }

private:
	void AllocateConsole();
	void InitSDLWindow();
	void CreateQuadBuffer();

	

private:
	SDL_Window* pWindow = nullptr;		// Window object pointer
	Shader* textureShader = nullptr;	// programShader pointer
	Shader* polygonShader = nullptr;
	

	SDL_GLContext context =  0 ;
	
	int SCR_WIDTH =	 800 ;
	int SCR_HEIGHT =  600 ;

	glm::vec3 camPosition = { 0.0f , -(float)SCR_HEIGHT / 2.0f, 1.0f };

	bool errorFlag =  false;
	std::string errorString = "" ;
	bool debugModeFlag = false;
	
	Uint32 vertBuffer[3], faceBuffer[3], textureBuffer, VAO[3];
	Uint32 apersp_matrix, aview_matrix, amodel_matrix, acolor;
	
	int aPos = 0;
	int aColor = 1;
	int aTexCoord = 2;
};

