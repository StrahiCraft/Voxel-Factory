#include "SphereRenderer.h"

SphereRenderer::SphereRenderer(float radius, int slices, int stacks) :
	_radius(radius), _slices(slices), _stacks(stacks) {}

void SphereRenderer::render() {
	glutSolidSphere(_radius, _slices, _stacks);
}

const float& SphereRenderer::getRadius() const {
	return this->_radius;
}

void SphereRenderer::setRadius(const float& radius) {
	_radius = radius; 
}

const int& SphereRenderer::getSlices() const {
	return _slices; 
}

void SphereRenderer::setSlices(const int& slices) {
	_slices = slices; 
}

const int& SphereRenderer::getStacks() const { 
	return _stacks; 
}

void SphereRenderer::setStacks(const int& stacks) { 
	_stacks = stacks; 
}

Component* SphereRenderer::copy() {
	return new SphereRenderer(_radius, _stacks, _slices);
}