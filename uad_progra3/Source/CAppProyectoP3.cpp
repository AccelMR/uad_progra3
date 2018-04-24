#include "../Include/CAppProyectoP3.h"
#include "../Include/Globals.h"
#include "../Include/CAppParcial2.h"
#include "../Include/C3DModel.h"
#include "../Include/LoadTGA.h"
#include "../Include/CWideStringHelper.h"



CAppProyectoP3::CAppProyectoP3()
{
	Log << "CAppProyecto3" << endl;
	myWorld = new CWorld(getOpenGLRenderer());
}

CAppProyectoP3::CAppProyectoP3(int window_width, int window_height) :
	CApp(window_width, window_height),
	m_currentDeltaTime{ 0.0 },
	m_objectRotation{ 0.0 },
	m_objectPosition{ 0.0f, 0.0f, 0.0f },
	m_rotationSpeed{ DEFAULT_ROTATION_SPEED }
{
	Log << "CAppProyecto3" << endl;
	myWorld = new CWorld(getOpenGLRenderer());
}


CAppProyectoP3::~CAppProyectoP3()
{
	CloseHandle(thread1);
	CloseHandle(thread2);
	CloseHandle(thread3);
}

void CAppProyectoP3::onMouseMove(float deltaX, float deltaY)
{
	// Camera
	CCamera* cam = getCamera();
	if (cam != nullptr) {
		cam->move(-deltaX * DEFAULT_CAMERA_MOVE_SPEED,
			deltaY * DEFAULT_CAMERA_MOVE_SPEED);
	}
}

void CAppProyectoP3::onF3(int mods)
{
	// Check BITWISE AND to detect shift/alt/ctrl
	if (mods & KEY_MOD_SHIFT)
	{
		moveCamera(-1.0f);
	}
	else
	{
		moveCamera(1.0f);
	}
}

void CAppProyectoP3::moveCamera(float direction)
{
	if (getOpenGLRenderer() != NULL)
	{
		getOpenGLRenderer()->moveCamera(direction);
	}
}

void CAppProyectoP3::update(double deltaTime)
{
	double degreesToRotate = 0.0;

	if (deltaTime <= 0.0f)
	{
		return;
	}

	// Save current delta time
	m_currentDeltaTime = deltaTime;

	// Calculate degrees to rotate
	// ----------------------------------------------------------------------------------------------------------------------------------------
	// degrees = rotation speed * delta time 
	// deltaTime is expressed in milliseconds, but our rotation speed is expressed in seconds (convert delta time from milliseconds to seconds)
	degreesToRotate = m_rotationSpeed * (deltaTime / 1000.0);
	// accumulate rotation degrees
	m_objectRotation += degreesToRotate;

	// Reset rotation if needed
	while (m_objectRotation > 360.0)
	{
		m_objectRotation -= 360.0;
	}
	if (m_objectRotation < 0.0)
	{
		m_objectRotation = 0.0;
	}
}

DWORD CAppProyectoP3::InitilizeWorld(PVOID pvParam)
{
	cout << "Thread 1: Inicializando Grid" << endl;
	
	CAppProyectoP3* myProj = (CAppProyectoP3*)pvParam;
	myProj->myWorld->Initialize();

	cout << "Thread 1: Fin" << endl;

	SetEvent(myProj->getEvent());
	SetEvent(myProj->getEvent2());
	return 0;
}

DWORD CAppProyectoP3::CreateDefaultWorld(PVOID pvParam)
{
	CAppProyectoP3* myProj = (CAppProyectoP3*)pvParam;
	WaitForSingleObject(myProj->getEvent(), INFINITE);
	cout << "Thread 2: Inicializando Grid" << endl;
	myProj->myWorld->InitializeQuadTree();
	cout << "Thread 2: Grid Fin" << endl;
	return 0;
}

DWORD CAppProyectoP3::InitilizeQuadTree(PVOID pvParam)
{
	CAppProyectoP3* myProj = (CAppProyectoP3*)pvParam;
	WaitForSingleObject(myProj->getEvent2(), INFINITE);
	cout << "Thread 3: Inicializando Grid" << endl;
	myProj->myWorld->DefaultWorld();
	cout << "Thread 3: Grid Fin" << endl;
	return 0;
}
void CAppProyectoP3::run()
{

	// Check if CGameWindow object and window library been initialized
	if (canRun())
	{
		// Create the Window 
		if (getGameWindow()->create(CAPPPARCIAL3_WINDOW_TITLE))
		{
			// Set initial clear screen color
			getOpenGLRenderer()->setClearScreenColor(0.15f, 0.75f, 0.75f);
			// Initialize window width/height in the renderer
			getOpenGLRenderer()->setWindowWidth(getGameWindow()->getWidth());
			getOpenGLRenderer()->setWindowHeight(getGameWindow()->getHeight());
			// Initialize a test cube
			getOpenGLRenderer()->initializeTestObjects();

			hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
			thread1 = CreateThread(
				nullptr,
				0,
				(LPTHREAD_START_ROUTINE)InitilizeWorld,
				this,
				0,
				&threadID_1);

			thread2 = CreateThread(
				nullptr,
				0,
				(LPTHREAD_START_ROUTINE)CreateDefaultWorld,
				this,
				0,
				&threadID_2);

			thread3 = CreateThread(
				nullptr,
				0,
				(LPTHREAD_START_ROUTINE)InitilizeQuadTree,
				this,
				0,
				&threadID_3);

			// Enter main loop
			Log << "Entering Main loop" << endl;
			getGameWindow()->mainLoop(this);
		}
	}
}

void CAppProyectoP3::render()
{
	CGameMenu *menu = getMenu();

	// If menu is active, render menu
	if (menu != NULL && menu->isInitialized() && menu->isActive())
	{
		menu->render(getOpenGLRenderer());
	}
	else // Otherwise, render active object if loaded (or test cube if no object is loaded)
	{
		// White 
		float color[3] = { 0.95f, 0.95f, 0.95f };

		GetExitCodeThread(thread2, &check);
		GetExitCodeThread(thread3, &check2);

		if (myWorld != NULL && myWorld->isInitialized() && check != STILL_ACTIVE && check2 != STILL_ACTIVE)
		{
			// Get a matrix that has both the object rotation and translation
			//MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);

			myWorld->render(getCamera()->getPosition());

			/**/
		}
		else {
			// convert total degrees rotated to radians;
			double totalDegreesRotatedRadians = m_objectRotation * 3.1459 / 180.0;

			// Get a matrix that has both the object rotation and translation
			MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);

			// No model loaded, show test cube
			getOpenGLRenderer()->renderTestObject(&modelMatrix);
		}
	}

}

bool CAppProyectoP3::initializeMenu()
{
	return false;
}
