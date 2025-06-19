#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const std::string& path) {
    _meshes = Mesh::loadMeshes(path);
    generateMeshBoundingBox();
}

void MeshRenderer::render() {
    for (const Mesh& mesh : _meshes) {

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

        if (_selected) {
            renderWireframe(mesh);
        }
    }
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
    glEnable(GL_LIGHTING);

    mesh.material.cleanup();
}

void MeshRenderer::renderVertex(Vertex vertex) {
    glNormal3f(vertex.normal.x, vertex.normal.y, vertex.normal.z);

    glVertex3f(vertex.position.x + vertex.normal.x * _wireframeOffset,
        vertex.position.y + vertex.normal.y * _wireframeOffset,
        vertex.position.z + vertex.normal.z * _wireframeOffset);
}

void MeshRenderer::generateMeshBoundingBox() {
    for (const Mesh& mesh : _meshes) {
        BoundingBox meshBoundingBox;
        for (const auto& vertex : mesh.vertices) {
            if (vertex.position.x > meshBoundingBox.maxPosition.x) {
                meshBoundingBox.maxPosition.x = vertex.position.x;
            }
            if (vertex.position.y > meshBoundingBox.maxPosition.y) {
                meshBoundingBox.maxPosition.y = vertex.position.y;
            }
            if (vertex.position.z > meshBoundingBox.maxPosition.z) {
                meshBoundingBox.maxPosition.z = vertex.position.z;
            }

            if (vertex.position.x < meshBoundingBox.minPosition.x) {
                meshBoundingBox.minPosition.x = vertex.position.x;
            }
            if (vertex.position.y < meshBoundingBox.minPosition.y) {
                meshBoundingBox.minPosition.y = vertex.position.y;
            }
            if (vertex.position.z < meshBoundingBox.minPosition.z) {
                meshBoundingBox.minPosition.z = vertex.position.z;
            }
        }
        _boundingBoxes.push_back(meshBoundingBox);
    }
}

void MeshRenderer::setSelected(bool selected) {
    _selected = selected;
}

bool MeshRenderer::getSelected() {
    return _selected;
}
