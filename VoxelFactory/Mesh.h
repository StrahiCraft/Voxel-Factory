#pragma once
#include "Material.h"
#include "Texture.h"
#include "Vertex.h"

#include <glut.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <filesystem>

class Mesh {
public:
    std::vector<Vertex> vertices;
    Material material;

    static void loadMtl(const std::string& path, std::map<std::string, Material>& materials);
    static std::vector<Mesh> loadMeshes(const std::string& path);
};