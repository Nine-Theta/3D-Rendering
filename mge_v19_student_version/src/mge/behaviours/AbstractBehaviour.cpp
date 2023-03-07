#include "AbstractBehaviour.hpp"

namespace MGE {
	AbstractBehaviour::AbstractBehaviour() :_owner(nullptr) {}

	AbstractBehaviour::~AbstractBehaviour()
	{
		_owner = nullptr;
	}

	void AbstractBehaviour::setOwner(GameObject* pOwner) {
		_owner = pOwner;
	}
}
