#include "OpenGLFramework.h"

class TriangleApp : public OpenGLFramework
{
public:
	GLBatch triangleBatch;
	GLShaderManager shaderManager;

	TriangleApp(int argc, char* argv[], int w, int h, const char *title);

	void SetupRC();
	void OnRenderScene();
};