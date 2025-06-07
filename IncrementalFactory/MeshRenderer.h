#pragma once
#include "Component.h"
#include "Mesh.h"

class MeshRenderer : public Component {
private:
    std::vector<Mesh> _meshes;
public:
    MeshRenderer(const std::string& path);

    void render();
};