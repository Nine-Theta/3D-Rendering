#include <iostream>
#include "GameObject.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "RenderingProject_Engine/Core/Model.hpp"


namespace MGE {

	GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition)
		: _name(pName), _transform(glm::translate(pPosition)), _parent(nullptr), _children(),
		_mesh(nullptr), _behaviours(), _material(nullptr), _world(nullptr), _position(pPosition)
	{
	}

	GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition, RP::RPEngine::Model* pModel, MGE::GameObject* pParent)
		: _name(pName), _transform(glm::translate(pPosition)), _parent(pParent), _children(),
		_mesh(pModel->getMesh()), _material(pModel->getMaterial()), _behaviours(), _position(pPosition)
	{
		setParent(pParent);
		scale(pModel->getScale());
	}

	GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition, MGE::GameObject* pParent,
		MGE::Mesh* pMesh, MGE::AbstractMaterial* pMaterial, MGE::AbstractBehaviour* pBehaviour, MGE::World* pWorld)
		: _name(pName), _transform(glm::translate(pPosition)), _parent(pParent), _children(),
		_mesh(pMesh), _material(pMaterial), _behaviours(), _world(pWorld), _position(pPosition)

	{
		setParent(pParent);
		addBehaviour(pBehaviour);
	}

	GameObject::~GameObject()
	{
		//detach all children
		std::cout << "GC running on:" << _name << std::endl;

		while (_children.size() > 0) {
			GameObject* child = _children[0];
			remove(child);
			delete child;
		}

		//do not forget to delete behaviour, material, mesh, collider manually if required!
	}

	void GameObject::setName(const std::string& pName)
	{
		_name = pName;
	}

	std::string GameObject::getName() const
	{
		return _name;
	}

	void GameObject::setTransform(const glm::mat4& pTransform)
	{
		_transform = pTransform;
	}

	const glm::mat4& GameObject::getTransform() const
	{
		return _transform;
	}

	void GameObject::setLocalPosition(glm::vec3 pPosition)
	{
		_transform[3] = glm::vec4(pPosition, 1);
	}

	glm::vec3 GameObject::getLocalPosition() const
	{
		return glm::vec3(_transform[3]);
	}

	void GameObject::setMaterial(AbstractMaterial* pMaterial)
	{
		_material = pMaterial;
	}

	AbstractMaterial* GameObject::getMaterial() const
	{
		return _material;
	}

	void GameObject::setMesh(Mesh* pMesh)
	{
		_mesh = pMesh;
	}

	Mesh* GameObject::getMesh() const
	{
		return _mesh;
	}
	
	/// <summary>
	/// compatiblity with older code, just calls addBehaviour()
	/// </summary>
	void GameObject::setBehaviour(AbstractBehaviour* pBehaviour)
	{
		GameObject::addBehaviour(pBehaviour);
	}

	/// <summary>
	/// Returns the first behaviour the GameObject has.
	/// Use getBehaviours() for the full list 
	/// </summary>
	AbstractBehaviour* GameObject::getBehaviour() const
	{
		return _behaviours.front();
	}

	void GameObject::setParent(GameObject* pParent) {
		//remove from previous parent
		if (_parent != nullptr) {
			_parent->_innerRemove(this);
		}

		//set new parent
		if (pParent != nullptr) {
			pParent->_innerAdd(this);
		}

		//if we have been detached from our parent, make sure
		//the world reference for us and all our children is set to null
		//if we have been attached to a parent, make sure
		//the world reference for us and all our children is set to our parent world reference
		//(this could still be null if the parent or parent's parent is not attached to the world)
		if (_parent == nullptr) {
			_setWorldRecursively(nullptr);
		}
		else {
			//might still not be available if our parent is not part of the world
			_setWorldRecursively(_parent->_world);
		}
	}

	void GameObject::_innerRemove(GameObject* pChild) {
		for (auto i = _children.begin(); i != _children.end(); ++i) {
			if (*i == pChild) {
				_children.erase(i);
				pChild->_parent = nullptr;
				return;
			}
		}
	}

	void GameObject::_innerAdd(GameObject* pChild)
	{
		_children.push_back(pChild);
		pChild->_parent = this;
	}

	void GameObject::add(GameObject* pChild) {
		pChild->setParent(this);
	}

	void GameObject::remove(GameObject* pChild) {
		pChild->setParent(nullptr);
	}

	GameObject* GameObject::getParent() const {
		return _parent;
	}

	////////////

	//costly operation, use with care
	glm::vec3 GameObject::getWorldPosition() const
	{
		return glm::vec3(getWorldTransform()[3]);
	}

	//costly operation, use with care
	glm::mat4 GameObject::getWorldTransform() const
	{
		if (_parent == nullptr) return _transform;
		else return _parent->getWorldTransform() * _transform;
	}

	////////////

	void GameObject::translate(glm::vec3 pTranslation)
	{
		setTransform(glm::translate(_transform, pTranslation));
	}

	void GameObject::scale(glm::vec3 pScale)
	{
		setTransform(glm::scale(_transform, pScale));
	}

	void GameObject::rotate(float pAngle, glm::vec3 pAxis)
	{
		//_transform = glm::mat4();
		setTransform(glm::rotate(_transform, pAngle, pAxis));
	}

	void GameObject::update(float pStep)
	{
		//make sure behaviour is updated after worldtransform is set
		for (int i = _behaviours.size() - 1; i >= 0; --i) {
			_behaviours[i]->update(pStep);
		}

		for (int i = _children.size() - 1; i >= 0; --i) {
			_children[i]->update(pStep);
		}
	}

	void GameObject::_setWorldRecursively(World* pWorld) {
		_world = pWorld;

		for (int i = _children.size() - 1; i >= 0; --i) {
			_children[i]->_setWorldRecursively(pWorld);
		}
	}

	int GameObject::getChildCount() const {
		return _children.size();
	}

	GameObject* GameObject::getChildAt(int pIndex) const {
		return _children[pIndex];
	}

	//Added:

	/// <summary>
	/// Adds a behaviour to the GameObject, which should be a new behaviour specific for this gameobject.
	/// If it isn't, it will be removed from the old owner and set to this gameobject.
	/// </summary>
	void GameObject::addBehaviour(MGE::AbstractBehaviour* pBehaviour)
	{
		if (pBehaviour == nullptr) return;
		if (pBehaviour->getOwner() != nullptr)
			pBehaviour->getOwner()->removeBehaviour(pBehaviour);

		_behaviours.push_back(pBehaviour);
		_behaviours.back()->setOwner(this);
	}

	void GameObject::removeBehaviour(MGE::AbstractBehaviour* pBehaviour)
	{
		for (auto i = _behaviours.begin(); i != _behaviours.end(); ++i) {
			if (*i == pBehaviour) {
				_behaviours.erase(i);
				pBehaviour->setOwner(nullptr);
				return;
			}
		}
	}

	std::vector<MGE::AbstractBehaviour*>* GameObject::getBehaviours() {
		return &_behaviours;
	}

	/*
	void GameObject::setLocalPosition(glm::vec3 pPosition) {
		glm::mat4 temp = glm::mat4(1);
		glm::rotate(temp, _rotation.w, glm::vec3(_rotation));
		_position = pPosition;
		temp[3] = glm::vec4(pPosition, 1);
		setTransform(temp);
	}*/

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

	void GameObject::setLocalRotation(float pAngle, glm::vec3 pAxis) {
		glm::mat4 temp = glm::mat4(1);
		glm::rotate(temp, pAngle, glm::vec3(pAxis));
		_rotation = glm::vec4(pAxis, pAngle);
		temp[3] = glm::vec4(_position, 1);
		setTransform(temp);
	}

	glm::vec4 GameObject::getLocalRotation() {
		return _rotation;
	}

	/*
	void GameObject::rotate(float pAngle, glm::vec3 pAxis)
	{
		setLocalRotation(pAngle + _rotation.w, glm::normalize(glm::vec3(_rotation) * pAxis));
		//_rotation * glm::vec4(pAxis, pAngle);



		//MGE::GameObject::rotate(pAngle, pAxis);

		//glm::inv

		//setTransform(glm::rotate(_transform, pAngle, pAxis));
	}

	void GameObject::rotate(glm::mat4 pRotation) {
		//setTransform(_transform += pRotation);
		//setTransform(_transform);
	}*/

	//
}
