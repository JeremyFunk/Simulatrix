#include "simixpch.h"
#include "PrimitivePlane.h"

namespace Simulatrix {
    ResourceModel PrimitivePlane::GetPrimitiveData() {
        ResourceModel d;
        ResourceMesh m;
        m.vertices.push_back(ResourceVertex(glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
        m.vertices.push_back(ResourceVertex(glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
        m.vertices.push_back(ResourceVertex(glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
        m.vertices.push_back(ResourceVertex(glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));

        m.indices.push_back(0);
        m.indices.push_back(1);
        m.indices.push_back(2);
        m.indices.push_back(2);
        m.indices.push_back(3);
        m.indices.push_back(0);
        d.Meshes.push_back(m);
        return d;
    }
}