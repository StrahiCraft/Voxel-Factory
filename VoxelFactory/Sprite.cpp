#include "Sprite.h"

Sprite::Sprite(const char* fileName, glm::vec2 size, GLuint numberOfTextures,
	glm::vec2 numberOfFrames, GLboolean isTransparent) :
	_fileName(fileName), _size(size), _numberOfFrames(numberOfFrames), _animationDelay(0.25f),
	_animationElapsedTime(0.0f), _isTransparent(isTransparent), _spriteFlip(false) {

	this->_numberOfTextures = static_cast<unsigned int>(numberOfFrames.x * numberOfFrames.y);
	_textures = new GLuint[this->_numberOfTextures];

	_textureIndex = 0;
	_currentFrame = 0;

	if (!addTexture(fileName, isTransparent))
		std::cout << "Texture loading failed: " << SOIL_last_result() << std::endl;
}

Sprite::~Sprite() {
	delete this;
}

const bool Sprite::addTexture(const char* fileName, const bool useTransparency) {
	GLuint texture = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);

	if (texture == 0)
		return false;

	_textures[_textureIndex] = texture;
	_textureIndex++;

	_isSpriteSheet = (_textureIndex == 1 && _numberOfTextures > 1);

	this->_isTransparent = useTransparency;

	return true;
}

void Sprite::update() {
	if (!_isAnimated) {
		return;
	}

	_animationElapsedTime += Time::getDeltaTime();
	if (_animationElapsedTime >= _animationDelay) {
		_currentFrame++;
		if (_currentFrame >= _numberOfTextures)
			_currentFrame = 0;
		_animationElapsedTime = 0.0f;
	}
}

void Sprite::render() {
	if (_isTransparent) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glBindTexture(GL_TEXTURE_2D, _textures[0]);

	GLfloat x = 0;
	GLfloat y = 0;

	GLfloat w = _size.x;
	GLfloat h = _size.y;

	GLfloat textureWidth = (GLfloat)_textureIndex / _numberOfFrames.x;
	GLfloat textureHeight = (GLfloat)_textureIndex / _numberOfFrames.y;

	if (!_isSpriteSheet)
		textureHeight = 1;

	GLfloat u = 0.0f;
	GLfloat v = 0.0f;

	if (_textureIndex < _numberOfFrames.x * _numberOfFrames.y) {
		GLuint currentY = _currentFrame / _numberOfFrames.x;
		GLuint currentX = _currentFrame - currentY * _numberOfFrames.x;

		u = static_cast<GLfloat>(currentX) * textureWidth;
		v = static_cast<GLfloat>(currentY) * textureHeight;
	}

	glBegin(GL_QUADS);

	// Default
	if (!_spriteFlip.y && !_spriteFlip.x) {
		glTexCoord2f(u, v + textureHeight);					glVertex2f(x, y);
		glTexCoord2f(u + textureWidth, v + textureHeight);	glVertex2f(x + w, y);
		glTexCoord2f(u + textureWidth, v);						glVertex2f(x + w, y + h);
		glTexCoord2f(u, v);										glVertex2f(x, y + h);
	}
	// Horizontal flip
	if (_spriteFlip.y && !_spriteFlip.x) {
		glTexCoord2f(u, v);										glVertex2f(x, y);
		glTexCoord2f(u + textureWidth, v);						glVertex2f(x + w, y);
		glTexCoord2f(u + textureWidth, v + textureHeight);	glVertex2f(x + w, y + h);
		glTexCoord2f(u, v + textureHeight);					glVertex2f(x, y + h);
	}
	// Vertical flip
	if (!_spriteFlip.y && _spriteFlip.x) {
		glTexCoord2f(u + textureWidth, v + textureHeight);	glVertex2f(x, y);
		glTexCoord2f(u, v + textureHeight);					glVertex2f(x + w, y);
		glTexCoord2f(u, v);										glVertex2f(x + w, y + h);
		glTexCoord2f(u + textureWidth, v);						glVertex2f(x, y + h);
	}
	// Horizontal && Vertical flip
	if (_spriteFlip.y && _spriteFlip.x) {
		glTexCoord2f(u + textureWidth, v);						glVertex2f(x, y);
		glTexCoord2f(u, v);										glVertex2f(x + w, y);
		glTexCoord2f(u, v + textureHeight);					glVertex2f(x + w, y + h);
		glTexCoord2f(u + textureWidth, v + textureHeight);	glVertex2f(x, y + h);
	}

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	if (_isTransparent) {
		glDisable(GL_BLEND);
	}
}

GLuint* Sprite::getTextures() const { return _textures; }

void Sprite::setTextures(const GLuint* textures) {
	if (textures == nullptr) {
		std::cerr << "Error: set_textures received a null pointer." << std::endl;
		return;
	}

	for (unsigned int i = 0; i < _numberOfTextures; ++i) {
		this->_textures[i] = textures[i];
	}
}

void Sprite::setIsAnimated(const bool& isAnimated) { this->_isAnimated = isAnimated; }

unsigned int Sprite::getTextureIndex() const { return _textureIndex; }
void Sprite::setTextureIndex(const unsigned int& textureIndex) { this->_textureIndex = textureIndex; }

unsigned int Sprite::getCurrentFrame() const { return _currentFrame; }
void Sprite::setCurrentFrame(const unsigned int& currentFrame) { this->_currentFrame = currentFrame; }

unsigned int Sprite::getNumberOfTextures() const { return _numberOfTextures; }
void Sprite::setNumberOfTextures(const unsigned int& numberOfTextures) { this->_numberOfTextures = numberOfTextures; }

glm::vec2 Sprite::getNumberOfFrames() const { return _numberOfFrames; }
void Sprite::setNumberOfFrames(const glm::vec2& numberOfFrames) { this->_numberOfFrames = numberOfFrames; }

GLfloat Sprite::getAnimationDelay() const { return _animationDelay; }
void Sprite::setAnimationDelay(const GLfloat& animationDelay) { this->_animationDelay = animationDelay; }

GLfloat Sprite::getAnimationElapsedTime() const { return _animationElapsedTime; }
void Sprite::setAnimationElapsedTime(const GLfloat& animationElapsedTime) { this->_animationElapsedTime = animationElapsedTime; }

GLboolean Sprite::getIsTransparent() const { return _isTransparent; }
void Sprite::setIsTransparent(const GLboolean& isTransparent) { this->_isTransparent = isTransparent; }

GLboolean Sprite::getIsSpriteSheet() const { return _isSpriteSheet; }
void Sprite::setIsSpriteSheet(const GLboolean& isSpriteSheet) { this->_isSpriteSheet = isSpriteSheet; }

glm::vec2 Sprite::getSpriteFlip() const { return _spriteFlip; }
void Sprite::setSpriteFlip(const glm::vec2& spriteFlip) { this->_spriteFlip = spriteFlip; }

glm::vec2 Sprite::getSize() const { return _size; }
void Sprite::setSize(const glm::vec2& size) { this->_size = size; }