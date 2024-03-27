#ifndef WORLD_HPP
#define WORLD_HPP

#include "mge/core/GameObject.hpp"

namespace MGE {
    class Camera;
    class Light;

    class World : public GameObject
    {
    public:
        World();

        void setMainCamera(Camera* pCamera);
        Camera* getMainCamera();

        //only used internally, do not use from outside
        void registerLight(Light* pLight);
        void unregisterLight(Light* pLight);

        Light* getLightAt(int pIndex);
        int getLightCount();

        void setAmbientLightColor(glm::vec3 pAmbientColor);
        void setAmbientLightIntensity(float pIntensity);
        glm::vec3 getAmbientLight();


    private:
        Camera* _mainCamera;
        std::vector<Light*> _lights;

        glm::vec4 _ambientLight = glm::vec4(1, 1, 1, 1);

        World(const World&);
        World& operator=(const World&);
    };
}
#endif // WORLD_HPP
