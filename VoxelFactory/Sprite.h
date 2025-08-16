#pragma once
#include "Component.h"
#include "Time.h"

#include "SOIL2.h"
#include "glut.h"
#include "glm.hpp"

#include <iostream>

class Sprite :
    public Component
{
private:
	const char* _fileName;

	GLuint* _textures;
	unsigned int _textureIndex;
	unsigned int _currentFrame;
	unsigned int _numberOfTextures;
	glm::vec2 _numberOfFrames;

	GLfloat _animationDelay;
	GLfloat _animationElapsedTime;

	GLboolean _isTransparent;
	GLboolean _isSpriteSheet;
	GLboolean _isAnimated = false;

	glm::vec2 _spriteFlip;
	glm::vec2 _size;

public:
	Sprite() = default;
	Sprite(const char* fileName, glm::vec2 size, GLuint numberOfTextures = 1,
		glm::vec2 numberOfFrames = glm::vec2(1), GLboolean isTransparent = true);
	~Sprite();

	const bool addTexture(const char* fileName, const bool useTransparency);

	void update();
	void render();

	GLuint* getTextures() const;
	void setTextures(const GLuint* textures);

	void setIsAnimated(const bool& isAnimated);

	unsigned int getTextureIndex() const;
	void setTextureIndex(const unsigned int& textureIndex);

	unsigned int getCurrentFrame() const;
	void setCurrentFrame(const unsigned int& currentFrame);

	unsigned int getNumberOfTextures() const;
	void setNumberOfTextures(const unsigned int& numberOfTextures);

	glm::vec2 getNumberOfFrames() const;
	void setNumberOfFrames(const glm::vec2& numberOfFrames);

	GLfloat getAnimationDelay() const;
	void setAnimationDelay(const GLfloat& animationDelay);

	GLfloat getAnimationElapsedTime() const;
	void setAnimationElapsedTime(const GLfloat& animationElapsedTime);

	GLboolean getIsTransparent() const;
	void setIsTransparent(const GLboolean& isTransparent);

	GLboolean getIsSpriteSheet() const;
	void setIsSpriteSheet(const GLboolean& isSpriteSheet);

	glm::vec2 getSpriteFlip() const;
	void setSpriteFlip(const glm::vec2& spriteFlip);

	glm::vec2 getSize() const;
	void setSize(const glm::vec2& size);

	Component* copy();
};

