#include "Triangle.h"

TriangleApp::TriangleApp(int argc, char* argv[], int w, int h, const char *title) : OpenGLFramework(argc, argv, w, h, title){}

void TriangleApp::SetupRC()
{
	glClearColor(0.0f,0.0f,1.0f,1.0f);
	shaderManager.InitializeStockShaders();
	
	GLfloat vVerts[] = {-0.5f, 0.0f, 0.0f,
						0.5f, 0.0f, 0.0f,
						0.0f, 0.5f, 0.0f};
	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();
}
void TriangleApp::OnRenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	triangleBatch.Draw();

	glutSwapBuffers();
}