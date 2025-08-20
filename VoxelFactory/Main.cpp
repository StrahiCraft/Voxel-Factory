#include "World.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "Player.h"
#include "TextRenderer.h"

PFNGLACTIVETEXTUREARBPROC Material::glActiveTextureARB = nullptr;
PFNGLMULTITEXCOORD2FARBPROC Material::glMultiTexCoord2fARB = nullptr;

glm::vec2 windowSize = { 1280, 720 };
glm::vec2 windowPosition = { 50, 50 };
glm::vec4 windowColor = { 0.2f, 0.4f, 0.65f, 1.0f };

const char* windowTitle = "Voxel Factory";

void doLighting();

void update() {
	if (Input::getKeyDown(' ')) {
		Input::_isCursorLocked = !Input::_isCursorLocked;
	}

	if (Input::getKeyDown(']')) {
		World::printWorld();
	}

	Input::update();

	World::update();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Camera::applyCameraMatrix();

	doLighting();
	
	World::render();

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

void initAudio() {
	AudioManager::init();

	AudioManager::addSong("Zeigarnik Effect", "Audio/Music/Zeigarnik Effect.mp3");

	AudioManager::addSound("Place", "Audio/SFX/Place.mp3");
	AudioManager::addSound("Destroy", "Audio/SFX/Destroy.mp3");
	AudioManager::addSound("Rotate", "Audio/SFX/Rotate.wav");
	AudioManager::addSound("InvalidPlacement", "Audio/SFX/InvalidPlacement.mp3");

	AudioManager::playSong("Zeigarnik Effect");
}

void initVariables() {
	Prefabs::initPrefabs();
	initAudio();

	GameObject* player = new GameObject("Player");
	player->addComponent<Player>();
	player->addComponent<CameraController>();
	GameObject* placingMachine = new GameObject(Prefabs::getPrefab("PlacingMachine"));

	player->getComponent<Player>()->setupMachines(placingMachine);
	player->getComponent<Transform>()->_position = glm::vec3(16, 2, 16);

	World::addObject(player);
	World::addObject(placingMachine);

	GameObject* ground = new GameObject("Ground");
	ground->addComponent<MeshRenderer>("Models/Ground/Ground.obj");
	ground->getComponent<Transform>()->_position = glm::vec3(15.5, 0, 15.5);
	ground->getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	World::addObject(ground);

	GameObject* machinePlacementText = new GameObject("Machine placement text");
	machinePlacementText->addComponent<TextRenderer>("Conveyor\nPrice=");
	machinePlacementText->getComponent<Transform>()->_position = glm::vec3(0, 50, 0);
	machinePlacementText->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));

	player->getComponent<Player>()->setupMachinePlacementText(machinePlacementText->getComponent<TextRenderer>());

	World::addUIObject(machinePlacementText);

	GameObject* moneyCounter = new GameObject("MoneyCounter");
	moneyCounter->addComponent<TextRenderer>("100$");
	moneyCounter->getComponent<Transform>()->_position = glm::vec3(0, 660, 0);
	moneyCounter->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));

	CashManager::setupMoneyCounter(moneyCounter->getComponent<TextRenderer>());

	World::addUIObject(moneyCounter);
}

void doLighting() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[4] = { 0.0f, 1.0f, 1.0f, 0.0f };
	GLfloat diffuse_pos[4] = { 1, 1, 1, 1 };
	GLfloat ambient_pos[4] = { 0.25f, 0.25f, 0.25f, 1 };
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