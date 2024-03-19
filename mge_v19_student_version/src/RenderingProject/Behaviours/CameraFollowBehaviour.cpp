#include "CameraFollowBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

namespace RP {

	CameraFollowBehaviour::CameraFollowBehaviour(MGE::GameObject* pTarget, glm::vec3 pFollowOffset, float pRotationSpeed) : MGE::AbstractBehaviour(),
		_followTarget(pTarget), _followOffset(pFollowOffset), _rotationSpeed(pRotationSpeed)
	{
	}

	CameraFollowBehaviour::~CameraFollowBehaviour() {

	}

	void CameraFollowBehaviour::update(float pStep)
	{
		_mousePos = glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

		_owner->setLocalPosition(_followTarget->getWorldPosition());

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {

			_mouseDelta = _mousePos - _oldMousePos;

			_owner->rotate(_mouseDelta.x* _rotationSpeed *pStep, glm::vec3(0, 1, 0));
		}

		//Mouse scroll requires a bit more work
		//sf::Event ev;
		//ev.mou

		_owner->translate(_followOffset);

		std::cout << "cont " << _owner->getLocalPosition() << " : " << std::endl;

		_oldMousePos = _mousePos;
	}
}