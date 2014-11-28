#include "OpenGLFramework.h"

#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )

PACK
(
struct TGA_Header
{
    GLbyte  identsize;
    GLbyte  colorMapType;
    GLbyte  imageType;
    // Color map specifications
	GLshort colorMapStart;//???
    GLshort colorMapLength;//???
    GLbyte colorMapBits;

    //image specification
    GLshort xstart;
    GLshort ystart;
    GLshort width;
    GLshort height;
    GLbyte  bits;
    GLbyte descriptor;
}
);

class CaptureToTGAApp : public OpenGLFramework
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

	CaptureToTGAApp(int argc, char* argv[], int w, int h, const char *title);

	void OnChangeSize(int w, int h);

	void SetupRC();

	void OnRenderScene();

	bool InitOpenGLState();
};