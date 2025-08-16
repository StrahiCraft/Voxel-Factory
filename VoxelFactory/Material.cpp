#include "Material.h"

Material::Material(const std::string& name)
	: diffuseMap(0), normalMap(0), name(name)
{
	loadUvFunc();

	ambient[0] = ambient[1] = ambient[2] = 1.0f; ambient[3] = 1.0f;
	diffuse[0] = diffuse[1] = diffuse[2] = 1.0f; diffuse[3] = 1.0f;
}

void Material::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	ambient[0] = r; ambient[1] = g; ambient[2] = b; ambient[3] = a;
}

void Material::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	diffuse[0] = r; diffuse[1] = g; diffuse[2] = b; diffuse[3] = a;
}

void Material::handleTransparency() const {
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Material::apply() const {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

	glActiveTextureARB(GL_TEXTURE0);
	if (normalMap) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, normalMap);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_DOT3_RGB);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_PRIMARY_COLOR);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
	}
	else {
		glDisable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PRIMARY_COLOR);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
	}

	glActiveTextureARB(GL_TEXTURE1);
	if (diffuseMap) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_TEXTURE);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_PREVIOUS);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
	}
	else {
		glDisable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);
		glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS);
		glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
	}

	glActiveTextureARB(GL_TEXTURE0);
}

void Material::cleanup() const {

	for (int u = 0; u < 2; ++u) {
		glActiveTextureARB(GL_TEXTURE0 + u);
		glDisable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDisable(GL_ALPHA_TEST);
	glActiveTextureARB(GL_TEXTURE0);
}

void Material::loadUvFunc() {
	glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	if (!glActiveTextureARB) {
		glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTexture");
	}
	if (!glActiveTextureARB) {
		std::cerr << "Fatal Error: glActiveTextureARB not found!\n";
		exit(EXIT_FAILURE);
	}

	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	if (!glMultiTexCoord2fARB) {
		glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2f");
	}
	if (!glMultiTexCoord2fARB) {
		std::cerr << "Fatal Error: glMultiTexCoord2fARB not found!\n";
		exit(EXIT_FAILURE);
	}
}
