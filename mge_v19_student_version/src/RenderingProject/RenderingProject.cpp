#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"


#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "RenderingProject/config.hpp"
#include "RenderingProject/RenderingProject.hpp"

#include "RenderingProject/Behaviours/MouselookBehaviour.hpp"
#include "RenderingProject_Engine/Core/Model.hpp"

namespace RP {
    //construct the game class into _window, _renderer and hud (other parts are initialized by build)
    RenderingProject::RenderingProject() : MGE::AbstractGame(), _hud(0)
    {
    }

    void RenderingProject::initialize() {
        //setup the core part
        MGE::AbstractGame::initialize();

        //setup the custom part so we can display some text
        std::cout << "Initializing HUD" << std::endl;
        _hud = new MGE::DebugHud(_window);

        std::cout << "HUD initialized." << std::endl << std::endl;
    }

    //build the game _world
    void RenderingProject::_initializeScene()
    {
        //MESHES

        //load a bunch of meshes we will be using throughout this demo
        //each mesh only has to be loaded once, but can be used multiple times:
        //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
        MGE::Mesh* planeMeshDefault = MGE::Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
        MGE::Mesh* cubeMeshF = MGE::Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
        MGE::Mesh* sphereMeshS = MGE::Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

        //MATERIALS

        //create some materials to display the cube, the plane and the light

        MGE::AbstractMaterial* lightMaterial = new MGE::ColorMaterial(glm::vec3(1, 1, 0));
        MGE::AbstractMaterial* runicStoneMaterial = new MGE::TextureMaterial(MGE::Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));

        //set Models

        RPEngine::Model* sphereModel = new RPEngine::Model(sphereMeshS, runicStoneMaterial, glm::vec3(2.5, 2.5, 2.5));
        RPEngine::Model* floorModel = new RPEngine::Model(planeMeshDefault, runicStoneMaterial, glm::vec3(5, 5, 5));
        RPEngine::Model* lightModel = new RPEngine::Model(cubeMeshF, lightMaterial, glm::vec3(0.1f, 0.1f, 0.1f));
        RPEngine::Model* cubeModel = new RPEngine::Model(cubeMeshF, runicStoneMaterial, glm::vec3(0.1f, 0.1f, 0.1f));

        //SCENE SETUP

       //add camera first (it will be updated last)
        MGE::Camera* camera = new MGE::Camera("camera", glm::vec3(0, 6, 17));
        camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
        _world->add(camera);
        _world->setMainCamera(camera);

        //add the floor
        MGE::GameObject* plane = new MGE::GameObject("plane", glm::vec3(0, 0, 0), _world, floorModel);


        //add a spinning sphere
        MGE::GameObject* sphere = new MGE::GameObject("sphere", glm::vec3(0, 0, 0), _world, sphereModel);
        sphere->setBehaviour(new MGE::RotatingBehaviour());

        //add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
        //It's here as a place holder to get you started.
        //Note how the texture material is able to detect the number of lights in the scene
        //even though it doesn't implement any lighting yet!

        MGE::Light* light = new MGE::Light("light", glm::vec3(0, 0, -5));
        light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
        light->setMesh(cubeMeshF);
        light->setMaterial(lightMaterial);
        //light->setBehaviour(new MGE::KeysBehaviour(25));
        _world->add(light);

        MGE::GameObject* camFocus = new MGE::GameObject("focus", glm::vec3(0, 2, 0), _world);
        camFocus->setBehaviour(new MGE::KeysBehaviour(5));
        light->setParent(camFocus);

        MGE::GameObject* cubeChild = new MGE::GameObject("focus", glm::vec3(4, 0, 0), camFocus, cubeModel);

        camera->setParent(camFocus);
        camera->setBehaviour(new RP::MouselookBehaviour());

        

    }

    void RenderingProject::_render() {
        MGE::AbstractGame::_render();
        _updateHud();
    }

    void RenderingProject::_updateHud() {
        std::string debugInfo = "";
        debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

        _hud->setDebugInfo(debugInfo);
        _hud->draw();
    }

    RenderingProject::~RenderingProject()
    {
        //dtor
    }
}
