#include "ConeRenderer.h"

ConeRenderer::ConeRenderer(float base, float height, int slices, int stacks) :
	_base(base), _height(height), _slices(slices), _stacks(stacks) {}

void ConeRenderer::render() {
	glutSolidCone(_base, _height, _slices, _stacks);
}

const float& ConeRenderer::getBase() const {
	return _base; 
}

void ConeRenderer::setBase(const float& base) {
	_base = base; 
}

const float& ConeRenderer::getHeight() const {
	return _height; 
}

void ConeRenderer::setHeight(const float& height) { 
	_height = height; 
}

const int& ConeRenderer::getSlices() const {
	return _slices; 
}

void ConeRenderer::setSlices(const int& slices) {
	_slices = slices; 
}

const int& ConeRenderer::getStacks() const {
	return _stacks;
}

void ConeRenderer::setStacks(const int& stacks) {
	_stacks = stacks;
}

Component ConeRenderer::copy() {
	return ConeRenderer(_base, _height, _slices, _stacks);
}