#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const std::string& path) {
    setMesh(path);
}

MeshRenderer::MeshRenderer(std::vector<Mesh> meshes) {
    _meshes = meshes;
}

MeshRenderer::MeshRenderer(std::vector<Mesh> meshes, bool rendererMeshes, bool selected, glm::vec3 wireframeColor) {
    _meshes = meshes;
    _renderMeshes = rendererMeshes;
    _selected = selected;
    _wireframeColor = wireframeColor;
}

MeshRenderer::MeshRenderer() {

}

std::vector<Mesh> MeshRenderer::getMeshes() {
    return _meshes;
}

void MeshRenderer::setMesh(std::string path) {
    _meshes = Mesh::loadMeshes(path);
}

void MeshRenderer::setMesh(std::vector<Mesh> meshes) {
    _meshes = std::vector<Mesh>(meshes);
}

void MeshRenderer::render() {
    for (const Mesh& mesh : _meshes) {
        if (_renderMeshes) {
            mesh.material.apply();
            mesh.material.handleTransparency();

            if (!mesh.material.diffuseMap) {
                glDisable(GL_LIGHTING);
                glColor4fv(mesh.material.diffuse);
            }

            glBegin(GL_TRIANGLES);
            for (const auto& vertex : mesh.vertices) {
                glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);
                Material::glMultiTexCoord2fARB(GL_TEXTURE0, vertex.texcoord.x, vertex.texcoord.y);
                Material::glMultiTexCoord2fARB(GL_TEXTURE1, vertex.texcoord.x, vertex.texcoord.y);
                glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
            }

            glEnd();
            mesh.material.cleanup();
        }

        if (_selected) {
            renderWireframe(mesh);
        }
    }
}

void MeshRenderer::setMeshRendering(bool value) {
    _renderMeshes = value;
}

void MeshRenderer::renderWireframe(const Mesh& mesh) {
    glDisable(GL_LIGHTING);
    glColor3f(_wireframeColor.r, _wireframeColor.g, _wireframeColor.b);
    for (int i = 0; i < mesh.vertices.size(); i += 3) {
        glBegin(GL_LINE_LOOP);

        renderVertex(mesh.vertices[i]);
        renderVertex(mesh.vertices[i + 1]);
        renderVertex(mesh.vertices[i + 2]);

        glEnd();
    }
    glColor3f(1, 1, 1);
    glEnable(GL_LIGHTING);

    mesh.material.cleanup();
}

void MeshRenderer::renderVertex(Vertex vertex) {
    glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);

    glVertex3f(vertex.position.x + vertex.normal.x * _wireframeOffset,
        vertex.position.y + vertex.normal.y * _wireframeOffset,
        vertex.position.z + vertex.normal.z * _wireframeOffset);
}

void MeshRenderer::setSelected(bool selected) {
    _selected = selected;
}

void MeshRenderer::setSelectionColor(glm::vec3 color) {
    _wireframeColor = color;
}

bool MeshRenderer::getSelected() {
    return _selected;
}

Component* MeshRenderer::copy() {
    return new MeshRenderer(_meshes, _renderMeshes, _selected, _wireframeColor);
}