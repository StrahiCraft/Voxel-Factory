#pragma once
#include "Component.h"
#include <glm.hpp>

class BoundingBox : public Component {
private:
	glm::vec3 _maxPosition = glm::vec3(0);
	glm::vec3 _minPosition = glm::vec3(0);

public:
	void render();

	void setBounds(glm::vec3 maxPosition, glm::vec3 minPosition);
	bool pointInBoundingBox(glm::vec3 point);

	/// <summary>
	/// Only sets the position if the new position is greater than the old one.
	/// Use void setBounds(glm::vec3 maxPosition, glm::vec3 minPosition) to set new bounds
	/// without limits.
	/// </summary>
	/// <param name="position">Position of the coordinate to be checked and set as the new max bound.</param>
	void setNewMaxPosition(glm::vec3 position);

	/// <summary>
	/// Only sets the position if the new position is less than the old one.
	/// Use void setBounds(glm::vec3 maxPosition, glm::vec3 minPosition) to set new bounds
	/// without limits.
	/// </summary>
	/// <param name="position">Position of the coordinate to be checked and set as the new min bound.</param>
	void setNewMinPosition(glm::vec3 position);
};