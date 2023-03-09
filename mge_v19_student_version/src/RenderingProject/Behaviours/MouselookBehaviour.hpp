#ifndef MOUSELOOKBEHAVIOR_HPP
#define MOUSELOOKBEHAVIOR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

#include "RenderingProject_Engine/Core/GameObject.hpp"

#include "glm.hpp"

namespace RP {

	class MouselookBehaviour : public MGE::AbstractBehaviour {

	public:
		MouselookBehaviour();
		virtual ~MouselookBehaviour();

		virtual void setOwner(RPEngine::GameObject* pGameObject);

		virtual void update(float pStep);

	protected:
		//RPEngine::GameObject* _owner;

	private:
		glm::ivec2 _mousePos;
		glm::ivec2 _mouseOldPos;
		glm::vec2 _mouseDelta;
		glm::mat4 _rotationTotal;
	};
}
#endif // !MOUSELOOKBEHAVIOR_HPP



