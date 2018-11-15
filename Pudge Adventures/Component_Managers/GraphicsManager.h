#pragma once

#include <GLAD/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <String>
#include <fstream>
#include "..\Components\GameObject.h"
#include <glm/glm.hpp>
#include <iostream>

class Shader
{
public:
	// the program ID
	int Program;
	// constructor reads and builds the shader
	Shader(const char* vertexShaderName, const char* fragmentShaderName);
	~Shader();
	// use/activate the shader
	void use();
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
private:
	std::string loadFile(std::string& fileName);
};

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
	
	int SCR_WIDTH =	 1600 ;
	int SCR_HEIGHT =  900 ;

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

