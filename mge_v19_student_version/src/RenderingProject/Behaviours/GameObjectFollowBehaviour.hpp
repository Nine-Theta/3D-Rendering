#ifndef GAMEOBJECTFOLLOWBEHAVIOR_HPP
#define GAMEOBJECTFOLLOWBEHAVIOR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

namespace RP {
	class GameObjectFollowBehaviour : public MGE::AbstractBehaviour {

	public:
		GameObjectFollowBehaviour(MGE::GameObject* pTarget, glm::vec3 pFollowOffset);
		virtual ~GameObjectFollowBehaviour();

		virtual void update(float pStep);

	protected:

	private:
		glm::vec3 _followOffset;
		MGE::GameObject* _followTarget;

	};
}

#endif // !GAMEOBJECTFOLLOWBEHAVIOR_HPP

