#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include"Component.h"


class Texture;

class Sprite : public Component {

public:
	Sprite();
	~Sprite();

	void Update();

	void Serialize(std::ifstream &inFile);
	
	Texture* mpTexture;
	int uCoord = 0;
	int vCoord = 0;
};