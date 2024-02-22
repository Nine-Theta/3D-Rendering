#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include "glm.hpp"

//#include "mge/behaviours/AbstractBehaviour.hpp"

//#include "RenderingProject_Engine/Core/Model.hpp"

namespace RP {
	namespace RPEngine {
		class Model;
	}
}

namespace MGE {

	class AbstractCollider;
	class AbstractBehaviour;
	class AbstractMaterial;
	class World;
	class Mesh;


	/**
	 * A GameObject wraps all data required to display an object, but knows nothing about OpenGL or rendering.
	 */
	class GameObject
	{
	public:
		GameObject(const std::string& pName = nullptr, const glm::vec3& pPosition = glm::vec3(0.0f, 0.0f, 0.0f));
		
		//Added:
		GameObject(const std::string& pName, const glm::vec3& pPosition, RP::RPEngine::Model* pModel, MGE::GameObject* pParent = nullptr);
		GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::GameObject* pParent, MGE::Mesh* pMesh = nullptr, MGE::AbstractBehaviour* pBehaviour = nullptr, MGE::AbstractMaterial* pMaterial = nullptr, MGE::World* pWorld = nullptr);
		//
		
		virtual ~GameObject();

		void setName(const std::string& pName);
		std::string getName() const;

		//contains local rotation, scale, position
		void setTransform(const glm::mat4& pTransform);
		const glm::mat4& getTransform() const;

		//access just the local position
		void setLocalPosition(glm::vec3 pPosition);
		glm::vec3 getLocalPosition() const;

		//get the objects world position by combining transforms, SLOW use with care
		glm::vec3 getWorldPosition() const;
		glm::mat4 getWorldTransform() const;

		//change LOCAL position, rotation, scaling
		void translate(glm::vec3 pTranslation);
		void rotate(float pAngle, glm::vec3 pAxis);
		void scale(glm::vec3 pScale);

		//mesh and material should be shared as much as possible
		void setMesh(Mesh* pMesh);
		Mesh* getMesh() const;

		//mesh and material should be shared as much as possible
		void setMaterial(AbstractMaterial* pMaterial);
		AbstractMaterial* getMaterial() const;

		//behaviour is expected to be unique per game object, in general do NOT share them between objects
		//void setBehaviour(AbstractBehaviour* pBehaviour);
		AbstractBehaviour* getBehaviour() const;

		virtual void update(float pStep);

		//child management, note that add/remove and setParent are closely coupled.
		//a.add(b) has the same effect as b.setParent(a)
		//Adding a gameobject or resetting the parent, recursively passes on the world pointer to all child objects

		//shortcut to set the parent of pChild to ourselves
		void add(GameObject* pChild);
		//shortcut to set the parent of pChild to nullptr
		void remove(GameObject* pChild);

		void setParent(GameObject* pGameObject);
		GameObject* getParent() const;

		int getChildCount() const;
		GameObject* getChildAt(int pIndex) const;

		//Added:
		void setBehaviour(MGE::AbstractBehaviour* pBehaviour);
		
		void setLocalRotation(glm::vec4 pRotation);
		void setLocalRotation(float pAngle, glm::vec3 pAxis);
		glm::vec4 getLocalRotation();

		//void rotate(glm::mat4 pRotation);

	protected:
		std::string _name;
		glm::mat4 _transform;

		GameObject* _parent;
		std::vector<GameObject*> _children;

		Mesh* _mesh;
		AbstractBehaviour* _behaviour;
		AbstractMaterial* _material;
		World* _world;

		//update children list administration
		void _innerAdd(GameObject* pChild);
		void _innerRemove(GameObject* pChild);

		//used to pass on pointer to the world to a gameobject
		virtual void _setWorldRecursively(World* pWorld);

		//Added:

		glm::vec3 _position;

		/// <summary>
		/// Axis(xyz) Angle(w)
		/// </summary>
		glm::vec4 _rotation;

	private:
		GameObject(const GameObject&);
		GameObject& operator= (const GameObject&);
	};
}
#endif // GAMEOBJECT_HPP
