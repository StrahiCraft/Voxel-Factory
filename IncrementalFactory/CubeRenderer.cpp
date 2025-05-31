#include "CubeRenderer.h"

CubeRenderer::CubeRenderer(float size) : _size(size) {}

void CubeRenderer::render() {
	glutSolidCube(_size);
}

const float& CubeRenderer::getSize() const {
	return _size; 
}

void CubeRenderer::setSize(const float& size) {
	_size = size; 
}