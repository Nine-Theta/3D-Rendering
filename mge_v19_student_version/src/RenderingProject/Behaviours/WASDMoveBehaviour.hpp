#ifndef WASDMOVEBEHAVIOR_HPP
#define WASDMOVEBEHAVIOR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

namespace RP {

	class WASDMoveBehaviour : public MGE::AbstractBehaviour {

	public:
		WASDMoveBehaviour(float pMoveSpeed = 5, float pTurnSpeed = 45);
		virtual ~WASDMoveBehaviour();

		virtual void update(float pStep);

	protected:

	private:
		float _moveSpeed;
		float _turnSpeed;

	};
}

#endif // !WASDMOVEBEHAVIOR_HPP

