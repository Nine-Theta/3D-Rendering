#ifndef MODEL_HPP
#define MODEL_HPP

#include "mge/core/Mesh.hpp"

namespace MGE {
    class AbstractMaterial;
}

namespace RP {
    namespace RPEngine {

        class Model
        {
        public:
            Model(MGE::Mesh* pMesh, MGE::AbstractMaterial* pMaterial, glm::vec3 pScale = glm::vec3(1.0f, 1.0f, 1.0f));
            virtual ~Model();



            //mesh and material should be shared as much as possible
            void setMaterial(MGE::AbstractMaterial* pMaterial);
            void setMesh(MGE::Mesh* pMesh);

            MGE::AbstractMaterial* getMaterial() const;
            MGE::Mesh* getMesh() const;

            void setScale(glm::vec3 pScale);
            glm::vec3 getScale();

        protected:
            MGE::Mesh* _mesh;
            MGE::AbstractMaterial* _material;
            glm::vec3 _scale;


        private:
            Model(const Model&);
            Model& operator= (const Model&);
        };
    }
}

#endif // !MODEL_HPP
