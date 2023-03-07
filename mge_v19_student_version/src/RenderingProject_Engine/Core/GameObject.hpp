#ifndef RP_GAMEOBJECT_HPP
#define RP_GAMEOBJECT_HPP

#include "mge/core/GameObject.hpp"
#include "RenderingProject_Engine/Core/Model.hpp"

namespace RP {
	namespace RPEngine {

		class GameObject : public MGE::GameObject
		{
		public:
			GameObject(const std::string& pName = nullptr, const glm::vec3& pPosition = glm::vec3(0.0f, 0.0f, 0.0f));
			GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::GameObject* pParent);
			GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::Mesh* pMesh, MGE::AbstractMaterial* pMaterial, MGE::GameObject* pParent);
			GameObject(const std::string& pName, const glm::vec3& pPosition, Model* pModel , MGE::GameObject* pParent);
			virtual ~GameObject();

			

		private:
			GameObject(const GameObject&);
			GameObject& operator= (const GameObject&);
		};
	}
}

#endif //RP_GAMEOBJECT_HPP