
#include "MouselookBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include <SFML/Window/Mouse.hpp>


#include "mge/behaviours/AbstractBehaviour.hpp"



namespace RP {

	MouselookBehaviour::MouselookBehaviour() : MGE::AbstractBehaviour() {
		glm::ivec2 _mousePos = glm::ivec2(0,0);
		glm::ivec2 _mouseOldPos = glm::ivec2(0,0);
		glm::vec2 _mouseDelta = glm::vec2(0.0f, 0.0f);
		glm::mat4 _rotationTotal = glm::mat4(1.0f);
	}

	MouselookBehaviour::~MouselookBehaviour() {

	}

	void MouselookBehaviour::setOwner(RPEngine::GameObject* pOwner) {
		_owner = pOwner;
	}

	void MouselookBehaviour::update(float pStep) {
		_mousePos = glm::ivec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
			_mouseDelta = _mousePos - _mouseOldPos;
			//glm::vec3 temp = _owner->getLocalPosition() - _owner->getParent()->getLocalPosition();

			//_owner->setLocalPosition(_owner->getParent()->getLocalPosition());

			_owner->rotate(glm::radians( 1 * pStep), glm::vec3(0,-1,0));

			//_rotationTotal * 5;

			_owner->rotate(_rotationTotal);


			//_owner->rotate(glm::radians(_mouseDelta.y * 20 * pStep), glm::vec3(-1,0,0));
		}

		_mouseOldPos = _mousePos;
	}
}