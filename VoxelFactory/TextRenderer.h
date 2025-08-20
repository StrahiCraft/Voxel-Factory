#pragma once
#include "Component.h"
#include "Sprite.h"
#include <vector>

class TextRenderer :
    public Component
{
private:
	Sprite* _fontSheet = new Sprite("Sprites/font.png", glm::vec2(32), 1, glm::vec2(15, 8), true);
	int _characterOffset = 27;
	int _firstCharacterASCIIOffset = 32;
	std::vector<Sprite*> _characterSprites;
	glm::vec3 _textColor = glm::vec3(1);
	std::string _text;
public:
	TextRenderer(std::string text);
	void setText(std::string newText);
	void setTextColor(glm::vec3 color);
	void render();

	Component* copy();
};

