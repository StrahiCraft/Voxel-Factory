#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include <iostream>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <glext.h>

typedef void (APIENTRY* PFNGLACTIVETEXTUREARBPROC)(GLenum texture);
typedef void (APIENTRY* PFNGLMULTITEXCOORD2FARBPROC)(GLenum target, GLfloat s, GLfloat t);

class Material {
public:
	std::string name;

	GLfloat ambient[4];
	GLfloat diffuse[4];

	GLuint diffuseMap;
	GLuint normalMap;

	static PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
	static PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;

	Material(const std::string& name = "Material");

	void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

	void handleTransparency() const;

	void apply() const;

	void cleanup() const;

private:
	void loadUvFunc();
};