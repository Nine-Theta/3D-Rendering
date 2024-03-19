#ifndef WASDMOVEBEHAVIOR_HPP
#define WASDMOVEBEHAVIOR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

namespace RP {

	class WASDMoveBehaviour : public MGE::AbstractBehaviour {

	public:
		WASDMoveBehaviour(float pMoveSpeed);
		virtual ~WASDMoveBehaviour();

		virtual void update(float pStep);

	protected:

	private:
		float _moveSpeed;

	};
}

#endif // !WASDMOVEBEHAVIOR_HPP

