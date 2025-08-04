#pragma once
#include "Mesh.h"
#include "BoundingBox.h"

class GameObject;

class MeshRenderer : public Component {
private:
    std::vector<Mesh> _meshes;

    bool _selected = true;
    float _wireframeOffset = 0.05f;
    glm::vec3 _wireframeColor = glm::vec3(235.0f / 255.0f, 143.0f / 255.0f, 52.0f / 255.0f);

public:
    MeshRenderer(const std::string& path);

    void render();
    void renderWireframe(const Mesh& mesh);
    void setSelected(bool selected);
    bool getSelected();
    std::vector<BoundingBox> generateMeshBoundingBox();

private:
    /// <summary>
    /// Used for rendering the wireframe, call this function 3 times for 3
    /// vertices that make up a triangle to render a triangle outline.
    /// </summary>
    /// <param name="vertex">
    /// Vertex of a mesh
    /// </param>
    void renderVertex(Vertex vertex);

};