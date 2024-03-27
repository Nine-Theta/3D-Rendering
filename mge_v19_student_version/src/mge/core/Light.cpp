#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"


namespace MGE {
    Light::Light(const std::string& pName, const glm::vec3& pPosition, const glm::vec3& pColor, const float& pRange, const glm::vec3& pAttenuation) :
        GameObject(pName, pPosition), _color(pColor), _range(pRange), _attenuation(pAttenuation)
    {}

    Light::~Light() {
    }

    //Override setWorldRecursively to make sure we are registered
    //to the world we are a part of.
    void Light::_setWorldRecursively(World* pWorld) {

        //store the previous and new world before and after storing the given world
        World* previousWorld = _world;
        GameObject::_setWorldRecursively(pWorld);
        World* newWorld = _world;

        //check whether we need to register or unregister
        if (previousWorld != nullptr) previousWorld->unregisterLight(this);
        if (newWorld != nullptr) newWorld->registerLight(this);
    }

    void Light::setColor(const glm::vec3& pColor) { _color = pColor; }
    glm::vec3 Light::getColor() const { return _color; }

    void Light::setRange(const float& pRange) { _range = pRange; }
    float Light::getRange() const { return _range; }

    void Light::setAttenuation(const glm::vec3& pAttenuation) { _attenuation = pAttenuation; }
    glm::vec3 Light::getAttenuation() const { return _attenuation; }
}
