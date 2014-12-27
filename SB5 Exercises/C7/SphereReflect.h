#include "OpenGLFramework.h"

class SphereReflect : public OpenGLFramework
{
public:

	SphereReflect(int argc, char* argv[], int w, int h, const char *title);

	void OnChangeSize(int w, int h);
	void OnRenderScene();
	void OnKeys(int key, int x, int y);
	void SetupRC();

private:
	GLFrame viewFrame;
	GLFrustum viewFrustum;
	GLMatrixStack modelViewMatrix;
	GLMatrixStack projectionMatrix;
	GLGeometryTransform transformPipeline;
	GLTriangleBatch     sphereBatch;
	GLint               reflectionShader;
	GLuint              cubeTexture;
	GLint               locMVPReflect, locMVReflect, locNormalReflect, locInvertedCamera, locCubeSampler;

	void LoadCubeMap();
};