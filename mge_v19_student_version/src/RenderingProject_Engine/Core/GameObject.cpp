#include <iostream>

#include "glm.hpp"

#include "RenderingProject_Engine/Core/GameObject.hpp"
#include "RenderingProject/Behaviours/MouselookBehaviour.hpp"

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


		void GameObject::setBehaviour(RP::MouselookBehaviour* pBehaviour)
		{
			_behaviour = pBehaviour;
			_behaviour->setOwner(this);
		}

		/*
		void GameObject::rotate(float pAngle, glm::vec3 pAxis, bool f)
		{
			setTransform(glm::rotate(_transform, pAngle, pAxis));
		}*/

		//void GameObject::rotate(glm::mat4 pRotation) {
			//setTransform(_transform);
		//}
	}
}
