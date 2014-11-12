#include "OpenGLFramework.h"

extern GLfloat vGreen[];
extern GLfloat vBlack[];

extern GLfloat side;
extern GLfloat vCube[36][3];

class CubeApp : public OpenGLFramework
{
public:
	GLShaderManager shaderManager;
	GLGeometryTransform transformPipeline;
	GLMatrixStack modelViewMatrix;
	GLMatrixStack projectionMatrix;
	GLFrame cameraFrame;
	GLFrame objectFrame;
	GLBatch triangleBatch;
	GLFrustum viewFrustum;

	CubeApp(int argc, char* argv[], int w, int h, const char *title);

	void OnKeys(int key, int x, int y);

	void OnChangeSize(int w, int h);

	void SetupRC();

	void OnRenderScene();

	void DrawWireFramedBatch(GLBatch* pBatch);
};