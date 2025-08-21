#include "Game.h"
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

	Input::update();

	Game::update();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Camera::applyCameraMatrix();

	doLighting();
	
	Game::render();

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
	AudioManager::addSound("ChangeMachine", "Audio/SFX/ChangeMachine.wav");

	AudioManager::playSong("Zeigarnik Effect");
}

void initVariables() {
	Prefabs::initPrefabs();
	initAudio();

	Game::addScene("Factory");
	// TODO set to main menu instead
	Game::setCurrentScene("Factory");

	GameObject* player = new GameObject("Player");
	player->addComponent<Player>();
	player->addComponent<CameraController>();
	GameObject* placingMachine = new GameObject(Prefabs::getPrefab("PlacingMachine"));

	player->getComponent<Player>()->setupMachines(placingMachine);
	player->getComponent<Transform>()->_position = glm::vec3(16, 2, 16);

	Game::addObject("Factory", player);
	Game::addObject("Factory", placingMachine);

	GameObject* ground = new GameObject("Ground");
	ground->addComponent<MeshRenderer>("Models/Ground/Ground.obj");
	ground->getComponent<Transform>()->_position = glm::vec3(15.5, 0, 15.5);
	ground->getComponent<Transform>()->_scale = glm::vec3(1 / 1.6f);
	Game::addObject("Factory", ground);

	UIObject* machinePlacementText = new UIObject("Machine placement text", ScreenAlignment::BOTTOM_LEFT);
	machinePlacementText->addComponent<TextRenderer>("Conveyor\nPrice=");
	machinePlacementText->getComponent<Transform>()->_position = glm::vec3(0, 50, 0);
	machinePlacementText->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));

	player->getComponent<Player>()->setupMachinePlacementText(machinePlacementText->getComponent<TextRenderer>());

	Game::addUIObject("Factory", machinePlacementText);

	UIObject* moneyCounter = new UIObject("MoneyCounter", ScreenAlignment::TOP_LEFT);
	moneyCounter->addComponent<TextRenderer>("100$");
	moneyCounter->getComponent<Transform>()->_position = glm::vec3(0, -50, 0);
	moneyCounter->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));

	CashManager::setupMoneyCounter(moneyCounter->getComponent<TextRenderer>());

	Game::addUIObject("Factory", moneyCounter);

	UIObject* buildHint = new UIObject("BuildHint", ScreenAlignment::BOTTOM_RIGHT);
	buildHint->addComponent<TextRenderer>("[B]toggle build");
	buildHint->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	buildHint->getComponent<Transform>()->_position = glm::vec3(-490, 20, 0);
	buildHint->getComponent<TextRenderer>()->setTextColor(glm::vec3(0, 1, 0));

	Game::addUIObject("Factory", buildHint);

	UIObject* rotationHint = new UIObject("RotationHint", ScreenAlignment::BOTTOM_RIGHT);
	rotationHint->addComponent<TextRenderer>("[R]rotate");
	rotationHint->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	rotationHint->getComponent<Transform>()->_position = glm::vec3(-490, 60, 0);
	rotationHint->getComponent<TextRenderer>()->setTextColor(glm::vec3(243.0 / 255.0, 247.0 / 255.0, 2.0 / 255.0));
	rotationHint->setActive(false);

	Game::addUIObject("Factory", rotationHint);

	UIObject* destroyHint = new UIObject("DestroyHint", ScreenAlignment::BOTTOM_RIGHT);
	destroyHint->addComponent<TextRenderer>("[R_mouse]destroy");
	destroyHint->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	destroyHint->getComponent<Transform>()->_position = glm::vec3(-490, 100, 0);
	destroyHint->getComponent<TextRenderer>()->setTextColor(glm::vec3(1, 0, 0));
	destroyHint->setActive(false);

	Game::addUIObject("Factory", destroyHint);

	UIObject* placeHint = new UIObject("PlaceHint", ScreenAlignment::BOTTOM_RIGHT);
	placeHint->addComponent<TextRenderer>("[L_mouse]place");
	placeHint->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	placeHint->getComponent<Transform>()->_position = glm::vec3(-490, 100, 0);
	placeHint->getComponent<TextRenderer>()->setTextColor(glm::vec3(0, 1, 0));
	placeHint->setActive(false);

	Game::addUIObject("Factory", placeHint);

	UIObject* scrollHint = new UIObject("ScrollHint", ScreenAlignment::BOTTOM);
	scrollHint->addComponent<TextRenderer>("<[Z]|[C]>");
	scrollHint->getComponent<Transform>()->rotate(180, glm::vec3(0, 1, 0));
	scrollHint->getComponent<Transform>()->_position = glm::vec3(-160, 20, 0);
	scrollHint->setActive(false);

	Game::addUIObject("Factory", scrollHint);

	player->getComponent<Player>()->setupHints(buildHint, rotationHint, placeHint, destroyHint, scrollHint);
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

void initGame() {
	glClearColor(windowColor.r, windowColor.g, windowColor.b, windowColor.a);
	glEnable(GL_DEPTH_TEST);

	Window::updateWindow();

	doLighting();
	initVariables();
}

int main(int argv, char** argc) {

	initGlut(argv, argc);

	initGame();

	glutDisplayFunc(gameLoop);
	glutReshapeFunc(Window::reshape);
	Input::setCallbackFunctions();

	glutMainLoop();

	return 0;
}