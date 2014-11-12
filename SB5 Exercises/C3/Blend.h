#include "OpenGLFramework.h"

class BlendApp : public OpenGLFramework
{
public:
	GLBatch	squareBatch;
	GLBatch greenBatch;
	GLBatch redBatch;
	GLBatch blueBatch;
	GLBatch blackBatch;
	GLShaderManager	shaderManager;

	BlendApp(int argc, char* argv[], int w, int h, const char *title);
	
	void OnKeys(int key, int x, int y);
	void SetupRC();
	void OnRenderScene();

};