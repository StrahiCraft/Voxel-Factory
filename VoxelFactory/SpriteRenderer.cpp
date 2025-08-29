#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Sprite* sprite, glm::vec3 color) {
	_sprite = sprite;
	_color = color;
}

void SpriteRenderer::render() {
	glPushMatrix();

	glColor3f(_color.r, _color.g, _color.b);
	_sprite->render();
	glColor3f(1, 1, 1);

	glPopMatrix();
}

Sprite* SpriteRenderer::getSprite() {
	return _sprite;
}

void SpriteRenderer::setSprite(Sprite* newSprite) {
	_sprite = newSprite;
}

void SpriteRenderer::setColor(glm::vec3 color) {
	_color = color;
}

Component* SpriteRenderer::copy() {
	return new SpriteRenderer(_sprite, _color);
}
