#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include"Component.h"


class Texture;

class Sprite : public Component {

public:
	Sprite();
	~Sprite();

	void Init();
	void Update();

	void Serialize(std::ifstream &inFile);
	void Serialize(rapidjson::Document& objectFile);
	
	Texture* mpTexture;
	int uCoord = 0;
	int vCoord = 0;
};