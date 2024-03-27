#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"


namespace MGE {

	/**
	 * Exercise for the student: implement the Light class...
	 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
	 */
	class Light : public GameObject
	{
	public:
		Light(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(2.0f, 10.0f, 5.0f), const glm::vec3& pColor = glm::vec3(1.f,1.f,1.f), const float& pRange = 1.f, const glm::vec3& pAttenuation = glm::vec3(0, .15f, .005f));
		virtual ~Light();

		//override set parent to register/deregister light...
		virtual void _setWorldRecursively(World* pWorld) override;


		void setColor(const glm::vec3& pColor);
		glm::vec3 getColor() const;

		void setRange(const float& pRange);
		float getRange() const;

		void setAttenuation(const glm::vec3& pAttenuation);
		glm::vec3 getAttenuation() const;

	private:
		float _range;
		glm::vec3 _color;
		glm::vec3 _attenuation;
	};
}
#endif // LIGHT_HPP
