#pragma once
#include "Renderer.h"

class MeshRenderer : public Renderer {
private:
    std::vector<Mesh> _meshes;
public:
    MeshRenderer(const std::string& path);

    void render();
};