#include "EarthMoon.h"
#include <StopWatch.h>

EarthMoonApp::EarthMoonApp(int argc, char* argv[], int w, int h, const char *title) : OpenGLFramework(argc, argv, w, h, title){}

void EarthMoonApp::SetupRC()
{
	shaderManager.InitializeStockShaders();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	gltMakeSphere(sunBatch, 1.0f, 26, 13);
	gltMakeSphere(earthBatch, 0.3f, 26, 13);
	gltMakeSphere(moonBatch, 0.1f, 26, 13);
}

void EarthMoonApp::OnChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	
    // Create the projection matrix, and load it on the projection matrix stack
	viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 100.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
    // Set the transformation pipeline to use the two matrix stacks 
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
    
}

void EarthMoonApp::OnRenderScene()
{
	static GLfloat vSunColor[] = { 1.0f, 0.42f, 0.0f, 0.035f};
    static GLfloat vEarthColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    static GLfloat vMoonColor[] = { 0.66f, 0.66f, 0.66f, 1.0f };

	static CStopWatch	rotTimer;
	float rot_earth = rotTimer.GetElapsedSeconds() * 60.0f * 1.5f;
	float rot_moon = rotTimer.GetElapsedSeconds() * 60.0f * 2.5f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelViewMatrix.PushMatrix();

	M3DMatrix44f mCamera;
	cameraFrame.GetCameraMatrix(mCamera);
	modelViewMatrix.PushMatrix(mCamera);

	// Transform the light position into eye coordinates
    M3DVector4f vLightPos = { 0.0f, 10.0f, 5.0f, 1.0f };
    M3DVector4f vLightEyePos;
    m3dTransformVector4(vLightEyePos, vLightPos, mCamera);

	modelViewMatrix.Translate(0.0f, 0.0f, -8.5f);

	shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), 
		transformPipeline.GetProjectionMatrix(), vLightEyePos, vSunColor);
	sunBatch.Draw();

	modelViewMatrix.PushMatrix();
		modelViewMatrix.Rotate(rot_earth, -0.12f,0.85f,0.0f);
		modelViewMatrix.Translate(2.3f,0.0f,0.0f);
		shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), 
			transformPipeline.GetProjectionMatrix(), vLightEyePos, vEarthColor);
		earthBatch.Draw();

		modelViewMatrix.PushMatrix();
			modelViewMatrix.Rotate(rot_moon, 0.0f,1.0f,0.0f);
			modelViewMatrix.Translate(0.5f,0.0f,0.0f);
			shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), 
				transformPipeline.GetProjectionMatrix(), vLightEyePos, vMoonColor);
			moonBatch.Draw();
		modelViewMatrix.PopMatrix();

	modelViewMatrix.PopMatrix();

	modelViewMatrix.PopMatrix();
	modelViewMatrix.PopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}