#ifndef MOUSELOOKBEHAVIOR_HPP
#define MOUSELOOKBEHAVIOR_HPP

#include "glm.hpp"

#include "mge/behaviours/AbstractBehaviour.hpp"

#include "mge/core/GameObject.hpp"

namespace MGE {
	class Camera;
}

namespace RP {

	class MouselookBehaviour : public MGE::AbstractBehaviour {

	public:
		MouselookBehaviour(MGE::Camera* pCamera);
		virtual ~MouselookBehaviour();

		virtual void setOwner(MGE::GameObject* pGameObject);

		virtual void update(float pStep);

	protected:

	private:
		glm::ivec2 _mousePos;
		glm::ivec2 _oldMousePos;
		glm::vec2 _mouseDelta;
		glm::mat4 _rotationTotal;
		glm::vec2 _nMouseDelta;

		MGE::Camera* _camera;
	};
}
#endif // !MOUSELOOKBEHAVIOR_HPP



