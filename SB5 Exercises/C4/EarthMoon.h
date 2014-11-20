#include "OpenGLFramework.h"

class EarthMoonApp : public OpenGLFramework
{
public:
	GLShaderManager shaderManager;
	GLGeometryTransform transformPipeline;
	GLMatrixStack modelViewMatrix;
	GLMatrixStack projectionMatrix;
	GLFrame cameraFrame;
	GLFrustum viewFrustum;

	GLTriangleBatch     sunBatch;
	GLTriangleBatch		earthBatch;
	GLTriangleBatch     moonBatch;

	EarthMoonApp(int argc, char* argv[], int w, int h, const char *title);

	void OnChangeSize(int w, int h);

	void SetupRC();

	void OnRenderScene();
};