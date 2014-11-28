#include "CaptureToTGA.h"
#include <StopWatch.h>

GLint gltWriteTGA(const char *szFileName)
{
    FILE *pFile;                // File pointer
    struct TGA_Header tgaHeader;        // TGA file header
    unsigned long lImageSize;   // Size in bytes of image
	GLbyte *pBits = NULL;
    GLint iViewport[4];         // Viewport in pixels
    GLint lastBuffer;          // Storage for the current read buffer setting

    // Get the viewport dimensions
    glGetIntegerv(GL_VIEWPORT, iViewport);

    // How big is the image going to be (targas are tightly packed)
    lImageSize = iViewport[2] * 3 * iViewport[3];
    // Allocate block. If this doesn't work, go home
	pBits = (GLbyte*)malloc(lImageSize);
    if(pBits == NULL)
        return 0;
    // Read bits from color buffer
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);

    // Get the current read buffer setting and save it. Switch to
    // the front buffer and do the read operation. Finally, restore
    // the read buffer state
    glGetIntegerv(GL_READ_BUFFER, &lastBuffer);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, iViewport[2], iViewport[3], GL_BGR_EXT, GL_UNSIGNED_BYTE, pBits);
    glReadBuffer(lastBuffer);

    // Initialize the Targa header
    tgaHeader.identsize = 0;
    tgaHeader.colorMapType = 0;
    tgaHeader.imageType = 2;
    tgaHeader.colorMapStart = 0;
    tgaHeader.colorMapLength = 0;
    tgaHeader.colorMapBits = 0;
    tgaHeader.xstart = 0;
    tgaHeader.ystart = 0;
    tgaHeader.width = iViewport[2];
    tgaHeader.height = iViewport[3];
    tgaHeader.bits = 24;
    tgaHeader.descriptor = 0;

    // Attempt to open the file
    pFile = fopen(szFileName, "wb");
    if(pFile == NULL)
        {
			fprintf(stdout, "Open file error!");
        return 0;
        }

    // Write the header  
    fwrite(&tgaHeader, sizeof(tgaHeader), 1, pFile);

    // Write the image data
    fwrite(pBits, lImageSize, 1, pFile);

    fclose(pFile);

    // Success!
	fprintf(stdout, "Successful !");
    return 1;
}

void ProcessMenu(int value)
{
	switch(value)
    {
    case 0:
		gltWriteTGA("CaptureScreen.tga");
        break;
	}
}

bool CaptureToTGAApp::InitOpenGLState()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return false;
	}

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(Keys);

	glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("Capture Screen",0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

	return true;
}



CaptureToTGAApp::CaptureToTGAApp(int argc, char* argv[], int w, int h, const char *title) : OpenGLFramework(argc, argv, w, h, title){}

void CaptureToTGAApp::SetupRC()
{
	shaderManager.InitializeStockShaders();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	gltMakeSphere(sunBatch, 1.0f, 26, 13);
	gltMakeSphere(earthBatch, 0.3f, 26, 13);
	gltMakeSphere(moonBatch, 0.1f, 26, 13);
}

void CaptureToTGAApp::OnChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	
    // Create the projection matrix, and load it on the projection matrix stack
	viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 100.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
    // Set the transformation pipeline to use the two matrix stacks 
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
    
}

void CaptureToTGAApp::OnRenderScene()
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
	modelViewMatrix.Rotate(15.0f, 0.0f, 0.0f, 1.0f);

	shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), 
		transformPipeline.GetProjectionMatrix(), vLightEyePos, vSunColor);
	sunBatch.Draw();

	modelViewMatrix.PushMatrix();
		modelViewMatrix.Rotate(rot_earth, 0.0f,0.1f,0.0f);
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

