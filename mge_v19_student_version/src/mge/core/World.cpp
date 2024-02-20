#include <iostream>
#include <algorithm>

#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"

namespace MGE {
    World::World() :GameObject("root"), _mainCamera(0)
    {
        _world = this;
        std::cout << " Current lightcount: " << getLightCount() << std::endl;

    }

    void World::setMainCamera(Camera* pCamera) {
        if (pCamera != NULL) _mainCamera = pCamera;
    }

    Camera* World::getMainCamera() {
        return _mainCamera;
    }


    void World::registerLight(Light* pLight) {
        std::cout << "Registering light: " << pLight->getName() << " | Current lightcount: " << getLightCount() << std::endl;
        _lights.push_back(pLight);
    }

    void World::unregisterLight(Light* pLight) {
        std::cout << "Unregistering light " << pLight->getName() << " | Current lightcount: " << getLightCount() << std::endl;
        if (_lights.size() == 0) return;
        _lights.erase(std::remove(_lights.begin(), _lights.end(), pLight), _lights.end());
    }

    Light* World::getLightAt(int pIndex) {
        return _lights[pIndex];
    }

    int World::getLightCount() {
        if (_lights.size() == 0) return 0;
        return _lights.size();
    }
}