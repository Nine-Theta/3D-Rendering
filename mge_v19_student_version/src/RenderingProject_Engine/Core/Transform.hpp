#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

//#include <vector>
#include "glm.hpp"


namespace RP {
	namespace RPEngine {
		class Transform
		{
		public:
			Transform();
			virtual ~Transform();

			/*
			glm::vec3 right;
			glm::vec3 up;
			glm::vec3 forward;
			*/

		protected:
			glm::mat4 _matrix;

			glm::vec3 _position;

			/// <summary>
			/// Axis(xyz) Angle(w)
			/// </summary>
			glm::quat _rotation;

		private:
			Transform(const Transform&);
			Transform& operator= (const Transform&);
		};
	}
}

#endif // TRANSFORM_HPP