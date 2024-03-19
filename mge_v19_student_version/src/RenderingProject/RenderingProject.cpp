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
#include "RenderingProject/Behaviours/WASDMoveBehaviour.hpp"
#include "RenderingProject/Behaviours/GameObjectFollowBehaviour.hpp"
#include "RenderingProject/Behaviours/CameraFollowBehaviour.hpp"

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

		MGE::Mesh* sphereMeshF = MGE::Mesh::load(config::MGE_MODEL_PATH + "sphere_flat.obj");
		MGE::Mesh* planeMeshLarge = MGE::Mesh::load(config::MGE_MODEL_PATH + "plane20x20_2tris_aligned_uvs.obj");

		//MATERIALS

		//create some materials to display the cube, the plane and the light

		MGE::AbstractMaterial* lightMaterial = new MGE::ColorMaterial(glm::vec3(1, 1, 0));
		MGE::AbstractMaterial* runicStoneMaterial = new MGE::TextureMaterial(MGE::Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
		MGE::AbstractMaterial* landMaterial = new MGE::TextureMaterial(MGE::Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
		MGE::AbstractMaterial* brickMaterial = new MGE::TextureMaterial(MGE::Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));

		//set Models

		RPEngine::Model* sphereModel = new RPEngine::Model(sphereMeshS, runicStoneMaterial, glm::vec3(2.5, 2.5, 2.5));
		RPEngine::Model* floorModel = new RPEngine::Model(planeMeshDefault, runicStoneMaterial, glm::vec3(5, 1, 5));
		RPEngine::Model* lightModel = new RPEngine::Model(cubeMeshF, lightMaterial, glm::vec3(0.1f, 0.1f, 0.1f));
		RPEngine::Model* cubeModel = new RPEngine::Model(cubeMeshF, runicStoneMaterial, glm::vec3(0.1f, 0.1f, 0.1f));

		RPEngine::Model* terrainModel = new RPEngine::Model(planeMeshLarge, landMaterial, glm::vec3(2, 1, 2));
		RPEngine::Model* pedestalModel = new RPEngine::Model(cubeMeshF, runicStoneMaterial, glm::vec3(5, 0.1f, 5));

		//SCENE SETUP

	   //add camera first (it will be updated last)
		MGE::Camera* camera = new MGE::Camera("camera", glm::vec3(0, 8, 15));
		_world->add(camera);
		_world->setMainCamera(camera);

		MGE::GameObject* camParent = new MGE::GameObject("CamParent", glm::vec3(0, 8, 17), _world);
		//camera->setParent(camParent);
		//camParent->setBehaviour(new RP::MouselookBehaviour(camera));
		camParent->addBehaviour(new RP::WASDMoveBehaviour(10.0f));

		//add the floor
		MGE::GameObject* plane = new MGE::GameObject("plane", glm::vec3(0, 0.05f, 0), floorModel, _world);

		MGE::GameObject* cubey = new MGE::GameObject("cubey", glm::vec3(0, 5, 0), cubeModel, _world);
		cubey->scale(glm::vec3(10, 10, 10));



		//add a spinning sphere
		MGE::GameObject* sphere = new MGE::GameObject("sphere", glm::vec3(0, 0, 0), sphereModel, _world);
		sphere->setBehaviour(new MGE::RotatingBehaviour());

		//add a light. Note that the light does ABSOLUTELY ZIP! NADA ! NOTHING !
		//It's here as a place holder to get you started.
		//Note how the texture material is able to detect the number of lights in the scene
		//even though it doesn't implement any lighting yet!
		
		
		MGE::Light* light = new MGE::Light("light", glm::vec3(5, 3, 1));
		light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
		light->setMesh(cubeMeshF);
		light->setMaterial(lightMaterial);
		light->setBehaviour(new MGE::KeysBehaviour(25));
		_world->add(light);

		MGE::GameObject* lightFollow = new MGE::GameObject("follower", glm::vec3(0, 4, 0), cubeModel, light);

		lightFollow->scale(glm::vec3(10.0f, 10.0f, 10.0f));

		//MGE::GameObject* camFocus = new MGE::GameObject("focus", glm::vec3(0, 2, 0), _world);
		//camFocus->setBehaviour(new MGE::KeysBehaviour(5));
		//light->setParent(camFocus);

		//MGE::GameObject* cubeChild = new MGE::GameObject("focus", glm::vec3(4, 0, 0), cubeModel, camFocus);

		//camera->setParent(camFocus);

		//camParent->addBehaviour(new RP::GameObjectFollowBehaviour(light, glm::vec3(0, 1, 10)));


		camera->addBehaviour(new RP::CameraFollowBehaviour(light, glm::vec3(0, 0, 10)));

		MGE::GameObject* spawn= new MGE::GameObject("pedestal", glm::vec3(0, 0.1f, 15),pedestalModel, _world);



		MGE::GameObject* terrain = new MGE::GameObject("terrain", glm::vec3(0, 0, 0), _world);

		MGE::GameObject* terrain00 = new MGE::GameObject("terrain", glm::vec3(0, 0, 0), terrainModel, terrain);
		MGE::GameObject* terrain01 = new MGE::GameObject("terrain", glm::vec3(0, 0, -40), terrainModel, terrain);
		MGE::GameObject* terrain10 = new MGE::GameObject("terrain", glm::vec3(40, 0, 0), terrainModel, terrain);
		MGE::GameObject* terrain11 = new MGE::GameObject("terrain", glm::vec3(40, 0, -40), terrainModel, terrain);

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
