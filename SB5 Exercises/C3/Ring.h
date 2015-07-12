#include "OpenGLFramework.h"

class RingApp : public OpenGLFramework
{
public:
	GLShaderManager		shaderManager;
	GLMatrixStack		modelViewMatrix;
	GLMatrixStack		projectionMatrix;
	GLFrame				cameraFrame;
	GLFrame             objectFrame;
	GLFrustum			viewFrustum;

	GLBatch             triangleStripBatch;

	GLGeometryTransform	transformPipeline;

	

	RingApp(int argc, char* argv[], int w, int h, const char *title);

	void SetupRC();
	void OnRenderScene();
	void OnChangeSize(int w, int h);
	void OnKeys(int key, int x, int y);

private:
	void DrawWireFrameBatch(GLBatch *pBatch);
};