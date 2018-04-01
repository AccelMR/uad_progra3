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
	CApp(window_width, window_height)
{
	Log << "CAppProyecto3" << endl;
	myWorld = new CWorld(getOpenGLRenderer());
}


CAppProyectoP3::~CAppProyectoP3()
{
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

			myWorld->Initialize();

			// Create our menu (add all menu items)
			/*
			if (!initializeMenu())
			{
				return;
			}
			*/

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

		if (myWorld != NULL && myWorld->isInitialized())
		{
			// Get a matrix that has both the object rotation and translation
			// MathHelper::Matrix4 modelMatrix = MathHelper::ModelMatrix((float)totalDegreesRotatedRadians, m_objectPosition);

			myWorld->render(getCamera()->getPosition());

			/**/
		}
	}

}

bool CAppProyectoP3::initializeMenu()
{
	return false;
}
