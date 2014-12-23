#include "OpenGLFramework.h"

class SkyboxApp : public OpenGLFramework
{
public:

	SkyboxApp(int argc, char* argv[], int w, int h, const char *title);

	void OnChangeSize(int w, int h);
	void OnRenderScene();
	void OnKeys(int key, int x, int y);

	bool InitOpenGLState();
	void SetupRC();
};