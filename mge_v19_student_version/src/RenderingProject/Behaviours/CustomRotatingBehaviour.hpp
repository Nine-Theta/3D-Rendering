#ifndef CUSTOMROTATINGBEHAVIOUR_HPP
#define CUSTOMROTATINGBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

namespace RP {
	/**
	 * Simply rotates the object around its origin with a fixed speed.
	 */
	class CustomRotatingBehaviour : public MGE::AbstractBehaviour
	{
	public:
		CustomRotatingBehaviour(float pRotationSpeed, glm::vec3 pAxis);
		virtual ~CustomRotatingBehaviour();

		virtual void update(float pStep);

	protected:
		glm::vec4 _axisAngle;

	};
}
#endif // CUSTOMROTATINGBEHAVIOUR_HPP
