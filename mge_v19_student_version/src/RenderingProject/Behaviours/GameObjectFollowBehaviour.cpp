#include "GameObjectFollowBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include <SFML/Window/Mouse.hpp>

namespace RP {

	GameObjectFollowBehaviour::GameObjectFollowBehaviour(MGE::GameObject* pTarget, glm::vec3 pFollowOffset) : MGE::AbstractBehaviour()
	{
		_followTarget = pTarget;
		_followOffset = pFollowOffset;
	}

	GameObjectFollowBehaviour::~GameObjectFollowBehaviour() {

	}

	void GameObjectFollowBehaviour::update(float pStep)
	{
		_owner->setLocalPosition(_followTarget->getWorldPosition() + _followOffset);

		/*
		//Slow, but proper fix requires changing a lot about the engine
		glm::vec3 targetPos = _followTarget->getWorldPosition();
		glm::vec3 myPos = _owner->getWorldPosition();

		std::cout << "follow pos: " << targetPos << " | " << myPos << " | " << glm::length(myPos - targetPos) << std::endl;

		if (glm::length2(myPos - targetPos) > (_followDistance * _followDistance)) {
			_owner->setLocalPosition(glm::normalize(targetPos - myPos) * _followDistance); //doesn't work
		}
		*/

	}
}