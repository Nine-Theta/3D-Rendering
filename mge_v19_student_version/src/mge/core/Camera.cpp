#include "glm.hpp"
#include "mge/core/Camera.hpp"


namespace MGE {
	Camera::Camera(std::string pName, glm::vec3 pPosition, glm::mat4 pProjectionMatrix)
		: GameObject(pName, pPosition), _projection(pProjectionMatrix)
	{
	}

	Camera::~Camera()
	{
		//dtor
	}

	glm::mat4& Camera::getProjection() {
		return _projection;
	}
}
