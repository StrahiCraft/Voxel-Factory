#include "GameObject.h"
#include "MeshRenderer.h"
#include "CubeRenderer.h"
#include "CameraController.h"
#include "Player.h"

PFNGLACTIVETEXTUREARBPROC Material::glActiveTextureARB = nullptr;
PFNGLMULTITEXCOORD2FARBPROC Material::glMultiTexCoord2fARB = nullptr;

glm::vec2 windowSize = { 1280, 720 };
glm::vec2 windowPosition = { 50, 50 };
glm::vec4 windowColor = { 0.2f, 0.4f, 0.65f, 1.0f };

const char* windowTitle = "Incremental Factory";

std::vector<std::unique_ptr<GameObject>> _objects;

void doLighting();

void update() {
	if (Input::getKeyDown(' ')) {
		Input::_isCursorLocked = !Input::_isCursorLocked;
	}

	Input::update();

	for (auto& object : _objects)
		object->update();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Camera::applyCameraMatrix();

	doLighting();
	for (auto& object : _objects) {
		object->render();
	}
	glDisable(GL_LIGHTING);

	glutSwapBuffers();
}

void gameLoop() {
	Time::updateTime();

	update();
	render();

	glutPostRedisplay();
}

void initGlut(int argv, char** argc) {
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowSize.x, windowSize.y);
	glutInitWindowPosition(windowPosition.x, windowPosition.y);
	glPointSize(1);
	glLineWidth(1);
	glutCreateWindow(windowTitle);
}

void initVariables() {
	Prefabs::initPrefabs();

	std::unique_ptr<GameObject> player = std::make_unique<GameObject>("Player", std::vector<GameObject*> {
		new GameObject(Prefabs::getPrefab("PlacingMachine"))
	});
	player->addComponent<Player>();
	player->addComponent<CameraController>();
	player->getComponent<Player>()->setPlacingMachine();

	_objects.push_back(std::move(player));

	std::unique_ptr<GameObject> ground = std::make_unique<GameObject>("Ground");
	ground->addComponent<MeshRenderer>("Models/Ground/Ground.obj");
	ground->getComponent<Transform>()->position = glm::vec3(15.5, 0, 15.5);
	ground->getComponent<Transform>()->scale = glm::vec3(1 / 1.6f);
	_objects.push_back(std::move(ground));
}

void doLighting() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[4] = { 0.0f, 1.0f, 1.0f, 0.0f };
	GLfloat diffuse_pos[4] = { 1, 1, 1, 1 };
	GLfloat ambient_pos[4] = { 0.35f, 0.35f, 0.35f, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_pos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse_pos);
}

void updateWindow() {
	glutReshapeWindow(windowSize.x, windowSize.y);
	glViewport(0, 0, windowSize.x, windowSize.y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, float(windowSize.x) / float(windowSize.y), 0.1f, 300.0f);
	glMatrixMode(GL_MODELVIEW);
}

void initGame() {
	glClearColor(windowColor.r, windowColor.g, windowColor.b, windowColor.a);
	glEnable(GL_DEPTH_TEST);

	updateWindow();

	doLighting();
	initVariables();
}

void onResize(int newWidth, int newHeight) {
	windowSize.x = newWidth;
	windowSize.y = newHeight;

	updateWindow();
}

int main(int argv, char** argc) {

	initGlut(argv, argc);

	initGame();

	glutDisplayFunc(gameLoop);
	glutReshapeFunc(onResize);
	Input::setCallbackFunctions();

	glutMainLoop();

	return 0;
}