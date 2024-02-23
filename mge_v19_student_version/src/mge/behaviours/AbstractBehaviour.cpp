#include "AbstractBehaviour.hpp"

namespace MGE {
	AbstractBehaviour::AbstractBehaviour() :_owner(nullptr) {}

	AbstractBehaviour::~AbstractBehaviour()
	{
		_owner = nullptr;
	}

	void AbstractBehaviour::setOwner(MGE::GameObject* pOwner) {
		_owner = pOwner;
	}

	//Added:

	MGE::GameObject* AbstractBehaviour::getOwner() {
		return _owner;
	}
	//
}
