#include "GameObject.h"
#include "MeshRenderer.h"
#include "SphereRenderer.h"
#include "CameraController.h"

PFNGLACTIVETEXTUREARBPROC Material::glActiveTextureARB = nullptr;
PFNGLMULTITEXCOORD2FARBPROC Material::glMultiTexCoord2fARB = nullptr;

glm::vec2 windowSize = { 1280, 720 };
glm::vec2 windowPosition = { 50, 50 };
glm::vec4 windowColor = { 0.2f, 0.4f, 0.65f, 1.0f };

const char* windowTitle = "Incremental Factory";

std::vector<std::unique_ptr<GameObject>> _objects;

void doLighting();

void fpsPrinter(int time) {
	std::cout << "\x1B[2J\x1B[H";
	std::cout << "FPS: " << (1.0 / Time::getDeltaTime()) << std::endl;

	glutTimerFunc(time, fpsPrinter, time);
}

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
	std::unique_ptr<GameObject> mesh = std::make_unique<GameObject>("Mesh");
	mesh->addComponent<MeshRenderer>("Models/skull/skull_downloadable.obj");

	std::unique_ptr<GameObject> camera = std::make_unique<GameObject>("Camera");
	camera->addComponent<CameraController>();

	_objects.push_back(std::move(mesh));
	_objects.push_back(std::move(camera));

	std::unique_ptr<GameObject> ground = std::make_unique<GameObject>("Ground");
	ground->addComponent<MeshRenderer>("Models/Ground/Ground.obj");
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

	glutTimerFunc(500, fpsPrinter, 500);

	glutMainLoop();

	return 0;
}