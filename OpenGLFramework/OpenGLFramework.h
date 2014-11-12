#ifndef OPENGLFRAMEWORK_H
#define OPENGLFRAMEWORK_H


#include <GLTools.h>
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>
#include <math.h>
#define FREEGLUT_STATIC
#include <GL/glut.h>

#include <stdlib.h>

class OpenGLFramework
{
public:
	static OpenGLFramework* m_app;

	OpenGLFramework(int argc, char* argv[], int w, int h, const char *title);
	void Run();
	virtual void OnChangeSize(int w, int h);
	virtual void OnRenderScene();
	virtual void OnKeys(int key, int x, int y);

private:
	void InitWindow(int w, int h, const char *title);
	virtual bool InitOpenGLState();
	virtual void SetupRC();
	
};

void ChangeSize(int w, int h);

void RenderScene();

void Keys(int key, int x, int y);

#endif