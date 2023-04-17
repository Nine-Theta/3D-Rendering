#ifndef RP_GAMEOBJECT_HPP
#define RP_GAMEOBJECT_HPP

#include "mge/core/GameObject.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

#include "RenderingProject_Engine/Core/Model.hpp"

namespace RP {
	namespace RPEngine {

		class Model;

		class GameObject : public MGE::GameObject
		{
		public:
			GameObject(const std::string& pName = nullptr, const glm::vec3& pPosition = glm::vec3(0.0f, 0.0f, 0.0f));
			GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::GameObject* pParent);
			GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::Mesh* pMesh, MGE::AbstractMaterial* pMaterial, MGE::GameObject* pParent);
			GameObject(const std::string& pName, const glm::vec3& pPosition, Model* pModel , MGE::GameObject* pParent);
			virtual ~GameObject();


			void setBehaviour(MGE::AbstractBehaviour* pBehaviour);

			void setLocalPosition(glm::vec3 pPosition);
			glm::vec3 getLocalPosition();

			void setLocalRotation(glm::vec4 pRotation);
			void setLocalRotation(glm::vec3 pAxis, float pAngle);
			glm::vec4 getLocalRotation();

			void translate(glm::vec3 pTranslation);
			void rotate(float pAngle, glm::vec3 pAxis);
			void rotate(glm::mat4 pRotation);

		protected:
			/// <summary>
			/// Axis(xyz) Angle(w)
			/// </summary>
			glm::vec4 _rotation;
			glm::vec3 _position;


		private:
			GameObject(const GameObject&);
			GameObject& operator= (const GameObject&);
		};
	}
}

#endif //RP_GAMEOBJECT_HPP