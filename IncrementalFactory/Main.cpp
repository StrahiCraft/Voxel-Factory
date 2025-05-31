#include "GameObject.h"
#include "MeshRenderer.h"

PFNGLACTIVETEXTUREARBPROC Material::glActiveTextureARB = nullptr;
PFNGLMULTITEXCOORD2FARBPROC Material::glMultiTexCoord2fARB = nullptr;

// ==================================================================
//						  WINDOW SETTINGS
// ==================================================================

glm::vec2 windowSize = { 500, 500 };
glm::vec2 windowPosition = { 50, 50 };
glm::vec4 windowColor = { 0.2f, 0.4f, 0.65f, 1.0f };

const char* windowTitle = "Incremental Factory";

// ==================================================================
//				TIME STUFF, CHANGE TO TIME CLASS
// ==================================================================

float _deltaTime = 0;
float _previousTime = 0;

int _frameTime = 16; // in milliseconds

// ==================================================================

glm::vec3 _cameraPos = { -3.0f, 1.0f, -3.0f };
glm::vec3 _cameraTarget = { 0.0f, 0.0f, 0.0f };
glm::vec3 _cameraUp = { 0.0f, 1.0f, 0.0f };


std::vector<std::unique_ptr<GameObject>> _objects;

void update(float deltaTime) {
	for (auto& object : _objects)
		object->update(deltaTime);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		_cameraPos.x, _cameraPos.y, _cameraPos.z,
		_cameraTarget.x, _cameraTarget.y, _cameraTarget.z,
		_cameraUp.x, _cameraUp.y, _cameraUp.z
	);

	for (auto& object : _objects) {
		object->render();
	}

	glutSwapBuffers();
}

void gameLoop() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	_deltaTime = (float)((currentTime - _previousTime) / 1000);
	_previousTime = currentTime;

	update(_deltaTime);
	render();
}

void initGlut(int argv, char** argc) {
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowSize.x, windowSize.y);
	glutInitWindowPosition(windowPosition.x, windowPosition.y);
	glutCreateWindow(windowTitle);
}

void initVariables() {
	std::unique_ptr<GameObject> mesh = std::make_unique<GameObject>("Mesh");
	//mesh->addComponent<MeshRenderer>("Models/skull/skull_downloadable.obj");
	mesh->addComponent<Renderer>();

	_objects.push_back(std::move(mesh));
}

void initLight() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuse_pos[4] = { 1, 1, 1, 1 };
	GLfloat ambient_pos[4] = { 0.2f, 0.2f, 0.2f, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_pos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse_pos);
}

void initGame() {
	glClearColor(windowColor.r, windowColor.g, windowColor.b, windowColor.a);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, float(windowSize.x) / float(windowSize.y), 0.1f, 300.0f);
	glMatrixMode(GL_MODELVIEW);

	initLight();
	initVariables();
}

void timer(int val) {
	glutPostRedisplay();
	glutTimerFunc(_frameTime, timer, 0);
}

int main(int argv, char** argc) {

	initGlut(argv, argc);

	initGame();

	glutDisplayFunc(gameLoop);
	glutTimerFunc(_frameTime, timer, 0);

	glutMainLoop();

	return 0;
}