#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const std::string& path) {
    _meshes = Mesh::loadMeshes(path);
}

void MeshRenderer::render() {
    for (const auto& mesh : _meshes) {

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
}