#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <SOIL2.h>
#include <glut.h>

inline bool fileExist(const std::string& path);

GLuint loadTexture(const std::string& path);
