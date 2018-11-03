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
	void clearColor();
	void refreshWindow();
	void Draw(GameObject* go);
	bool isError();
	std::string getError();

private:
	void AllocateConsole();
	void InitSDLWindow();
	void CreateQuadBuffer();

	

private:
	SDL_Window* pWindow = nullptr;		// Window object pointer
	Shader* programShader = nullptr;	// programShader pointer
	

	SDL_GLContext context =  0 ;
	
	int SCR_WIDTH =	 800 ;
	int SCR_HEIGHT =  600 ;

	bool errorFlag = { false };
	std::string errorString = { "" };
	
	Uint32 vertBuffer, faceBuffer, textureBuffer, VAO;
	Uint32 apersp_matrix, aview_matrix, amodel_matrix, acolor;
	
	int aPos = 0;
	int aColor = 1;
	int aTexCoord = 2;
};

