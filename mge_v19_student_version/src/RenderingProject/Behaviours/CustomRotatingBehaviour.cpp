#include "CustomRotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"


namespace RP {

	CustomRotatingBehaviour::CustomRotatingBehaviour(float pRotationSpeed, glm::vec3 pAxis) : MGE::AbstractBehaviour(), _axisAngle(pAxis, pRotationSpeed) {
	}

	CustomRotatingBehaviour::~CustomRotatingBehaviour()	{
	}

	void CustomRotatingBehaviour::update(float pStep)
	{
		_owner->rotate(pStep * glm::radians(_axisAngle.w), glm::vec3(_axisAngle));
	}
}
