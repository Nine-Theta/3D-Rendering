#include <iostream>

#include "glm.hpp"

#include "RenderingProject_Engine/Core/GameObject.hpp"
#include "RenderingProject/Behaviours/MouselookBehaviour.hpp"

namespace RP {
	namespace RPEngine {

		GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition)
			: MGE::GameObject(pName, pPosition)
		{
			_position = pPosition;
		}

		GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::GameObject* pParent)
			: MGE::GameObject(pName, pPosition)
		{
			setParent(pParent);
		}

		GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::Mesh* pMesh, MGE::AbstractMaterial* pMaterial, MGE::GameObject* pParent)
			: MGE::GameObject(pName, pPosition)
		{
			_position = pPosition;

			setMesh(pMesh);
			setMaterial(pMaterial);
			setParent(pParent);
		}

		GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition, Model* pModel, MGE::GameObject* pParent)
			: MGE::GameObject(pName, pPosition)
		{
			_position = pPosition;

			setMesh(pModel->getMesh());
			setMaterial(pModel->getMaterial());
			scale(pModel->getScale());
			setParent(pParent);
		}

		GameObject::~GameObject()
		{

		}

		void GameObject::setBehaviour(MGE::AbstractBehaviour* pBehaviour)
		{
			_behaviour = pBehaviour;
			_behaviour->setOwner(this);
		}

		void GameObject::setLocalPosition(glm::vec3 pPosition) {
			glm::mat4 temp = glm::mat4(1);
			glm::rotate(temp, _rotation.w, glm::vec3(_rotation));
			_position = pPosition;
			temp[3] = glm::vec4(pPosition, 1);
			setTransform(temp);
		}

		glm::vec3 GameObject::getLocalPosition() {
			return _position;
		}

		/// <summary>
		/// Axis(xyz) Angle(w)
		/// </summary>
		void GameObject::setLocalRotation(glm::vec4 pRotation) {
			glm::mat4 temp = glm::mat4(1);
			glm::rotate(temp, pRotation.w, glm::vec3(pRotation));
			_rotation = pRotation;
			temp[3] = glm::vec4(_position, 1);
			setTransform(temp);
		}

		void GameObject::setLocalRotation(glm::vec3 pAxis, float pAngle) {
			glm::mat4 temp = glm::mat4(1);
			glm::rotate(temp, pAngle, glm::vec3(pAxis));
			_rotation = glm::vec4(pAxis, pAngle);
			temp[3] = glm::vec4(_position, 1);
			setTransform(temp);
		}

		glm::vec4 GameObject::getLocalRotation() {
			return _rotation;
		}


		void GameObject::rotate(float pAngle, glm::vec3 pAxis)
		{
			setLocalRotation(glm::normalize(glm::vec3(_rotation) * pAxis), pAngle + _rotation.w );
			//_rotation * glm::vec4(pAxis, pAngle);



			//MGE::GameObject::rotate(pAngle, pAxis);

			//glm::inv

			//setTransform(glm::rotate(_transform, pAngle, pAxis));
		}

		void GameObject::translate(glm::vec3 pPosition) {

		}

		void GameObject::rotate(glm::mat4 pRotation) {
			//setTransform(_transform += pRotation);
			//setTransform(_transform);
		}
	}
}
