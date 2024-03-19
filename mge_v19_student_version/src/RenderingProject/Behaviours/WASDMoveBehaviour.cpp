#include "WASDMoveBehaviour.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace RP {

	WASDMoveBehaviour::WASDMoveBehaviour(float pMoveSpeed) : MGE::AbstractBehaviour()
	{
		_moveSpeed = pMoveSpeed;
	}

	WASDMoveBehaviour::~WASDMoveBehaviour() {

	}

	void WASDMoveBehaviour::update(float pStep)
	{
		glm::vec3 movement = glm::vec3(0.0f, 0.0f, 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			movement.z -= _moveSpeed * pStep;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			movement.z += _moveSpeed * pStep;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			movement.x -= _moveSpeed * pStep;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			movement.x += _moveSpeed * pStep;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			movement.y += _moveSpeed * pStep;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			movement.y -= _moveSpeed * pStep;
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			movement *= 3;
		}

		//translate the object in its own local space
		//_owner->translate(glm::vec3(0.0f, 0.0f, moveSpeed * pStep));

		//we can also translate directly, basically we take the z axis from the matrix
		//which is normalized and multiply it by moveSpeed*step, then we add it to the
		//translation component

		_owner->translate(movement);

		//glm::mat4 transform = _owner->getTransform();
		//transform[3] += transform[2] * moveSpeed * pStep;
		//_owner->setTransform(transform);


		//NOTE:
		//The reason the above happens in the local space of the object and not in the world space
		//is that we use the _owner->translate / rotate shortcuts which in turn call glm::rotate / glm::translate
		//The methods multiply the current transform with the translation/rotation matrix from left to right
		//meaning everything happens in local space.
	}
}