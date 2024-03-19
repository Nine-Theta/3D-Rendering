#include "MouselookBehaviour.hpp"

#include "mge/core/GameObject.hpp"
#include <SFML/Window/Mouse.hpp>

#include "mge/core/Camera.hpp"



namespace RP {

	MouselookBehaviour::MouselookBehaviour(MGE::Camera* pCamera) : MGE::AbstractBehaviour() {
		glm::ivec2 _mousePos = glm::ivec2(0,0);
		glm::ivec2 _oldMousePos = glm::ivec2(0,0);
		glm::vec2 _mouseDelta = glm::vec2(0.0f, 0.0f);
		glm::vec2 _nMouseDelta = glm::vec2(0.0f, 0.0f);

		glm::mat4 _rotationTotal = glm::mat4();

		_camera = pCamera;
	}

	MouselookBehaviour::~MouselookBehaviour() {

	}

	void MouselookBehaviour::setOwner(MGE::GameObject* pOwner) {
		_owner = pOwner;
	}

	void MouselookBehaviour::update(float pStep) {
		_mousePos = glm::ivec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
			_mouseDelta = _mousePos - _oldMousePos;

			/*
			if (_mouseDelta.x == 0 && _mouseDelta.y == 0)
				return;
				/**/

			//glm::vec3 temp = _owner->getLocalPosition() - _owner->getParent()->getLocalPosition();

			//_owner->setLocalPosition(_owner->getParent()->getLocalPosition());

			//_owner->rotate(glm::radians( 1 * pStep), glm::vec3(0,-1,0));

			//_rotationTotal *= _mouseDelta.y;

			//_rotationTotal += 5 * pStep;
			//_owner->rotate(glm::rotate(_rotationTotal, glm::radians(_mouseDelta.y * 20 * pStep), glm::vec3(-1, 0, 0)));
			//_owner->rotate(_rotationTotal);

			//_mouseDelta = glm::normalize(_mouseDelta);



			/*
			_camera->rotate(glm::radians(5.0f * 20 * pStep), glm::vec3(-_mouseDelta.y, -_mouseDelta.x,0));
			std::cout << "mouseD: " << _mouseDelta.x << " : " << _mouseDelta.y << std::endl;
			/**/

			_camera->rotate(glm::radians(_mouseDelta.y * 20 * pStep), glm::vec3(-1,0,0));
			_owner->rotate(glm::radians(_mouseDelta.x * 20 * pStep), glm::vec3(0,-1,0));
			/**/

		}

		_oldMousePos = _mousePos;
	}
}