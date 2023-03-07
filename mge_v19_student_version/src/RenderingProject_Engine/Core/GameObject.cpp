#include <iostream>

#include "RenderingProject_Engine/Core/GameObject.hpp"

namespace RP {
	namespace RPEngine {
		
		GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition)
			: MGE::GameObject(pName, pPosition)
		{

		}

		GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::GameObject* pParent)
			: MGE::GameObject(pName, pPosition)
		{
			setParent(pParent);
		}

		GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::Mesh* pMesh, MGE::AbstractMaterial* pMaterial, MGE::GameObject* pParent)
			: MGE::GameObject(pName, pPosition)
		{
			setMesh(pMesh);
			setMaterial(pMaterial);
			setParent(pParent);
		}

		GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition, Model* pModel, MGE::GameObject* pParent)
			: MGE::GameObject(pName, pPosition)
		{
			setMesh(pModel->getMesh());
			setMaterial(pModel->getMaterial());
			scale(pModel->getScale());
			setParent(pParent);
		}

		GameObject::~GameObject()
		{

		}
	}
}
