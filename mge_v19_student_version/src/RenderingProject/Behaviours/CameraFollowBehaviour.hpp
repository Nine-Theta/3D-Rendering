#ifndef CAMERAFOLLOWBEHAVIOR_HPP
#define CAMERAFOLLOWBEHAVIOR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

namespace RP {
	class CameraFollowBehaviour : public MGE::AbstractBehaviour	{

	public:
		CameraFollowBehaviour(MGE::GameObject* pTarget, glm::vec3 pFollowOffset, float pRotationSpeed = 0.5f);
		virtual ~CameraFollowBehaviour();

		virtual void update(float pStep);

	protected:

	private:
		MGE::GameObject* _followTarget;

		glm::vec3 _followOffset;

		float _rotationSpeed;

		glm::vec2 _mousePos;
		glm::vec2 _oldMousePos;
		glm::vec2 _mouseDelta;
	};
}

#endif // !CameraFOLLOWBEHAVIOR_HPP




