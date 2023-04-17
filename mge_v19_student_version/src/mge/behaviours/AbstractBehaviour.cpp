#include "AbstractBehaviour.hpp"

namespace MGE {
	AbstractBehaviour::AbstractBehaviour() :_owner(nullptr) {}

	AbstractBehaviour::~AbstractBehaviour()
	{
		_owner = nullptr;
	}

	void AbstractBehaviour::setOwner(RP::RPEngine::GameObject* pOwner) {
		_owner = pOwner;
	}
}
