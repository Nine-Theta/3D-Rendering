#include "RenderingProject_Engine/Core/Model.hpp"


namespace RP {
	namespace RPEngine {

		Model::Model(MGE::Mesh* pMesh, MGE::AbstractMaterial* pMaterial, glm::vec3 pScale)
			: _mesh(pMesh), _material(pMaterial), _scale(pScale)

		{

		}

		void Model::setMaterial(MGE::AbstractMaterial* pMaterial)
		{
			_material = pMaterial;
		}

		void Model::setMesh(MGE::Mesh* pMesh)
		{
			_mesh = pMesh;
		}

		MGE::AbstractMaterial* Model::getMaterial() const
		{
			return _material;
		}

		MGE::Mesh* Model::getMesh() const
		{
			return _mesh;
		}

		void Model::setScale(glm::vec3 pScale)
		{
			_scale = pScale;
		}

		glm::vec3 Model::getScale() {
			return _scale;
		}

		Model::~Model() {

		}
	}
}