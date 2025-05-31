#pragma once
#include "Material.h"
#include "Texture.h"

#include <glut.h>

#include <glm.hpp>

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <filesystem>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    Material material;

    static void loadMtl(const std::string& path, std::map<std::string, Material>& materials);
    static std::vector<Mesh> loadMeshes(const std::string& path);
};