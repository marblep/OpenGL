
#include "Cube.h"

GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat side = 2.0f;
GLfloat vCube[36][3] = {
	 //0,1,2
	-side, -side, side,
	side, -side, side,
	side, side, side,
	//0,2,3
	-side, -side, side,
	side, side, side,
	-side, side, side,
	//1,4,2
	side, -side, side,
	side, -side, -side,
	side, side, side,
	//2,4,5
	side, side, side,
	side, -side, -side,
	side, side, -side,
	//4,7,5
	side, -side, -side,
	-side, -side, -side,
	side, side, -side,
	//7,6,5
	-side, -side, -side,
	-side, side, -side,
	side, side, -side,
	//0,3,7
	-side, -side, side,
	-side, side, side,
	-side, -side, -side,
	//7,3,6
	-side, -side, -side,
	-side, side, side,
	-side, side, -side,
	//2,5,3
	side, side, side,
	side, side, -side,
	-side, side, side,
	//3,5,6
	-side, side, side,
	side, side, -side,
	-side, side, -side,
	//1,0,4
	side, -side, side,
	-side, -side, side,
	side, -side, -side,
	//0,7,4
	-side, -side, side,
	-side, -side, -side,
	side, -side, -side,
};

	CubeApp::CubeApp(int argc, char* argv[], int w, int h, const char *title) : OpenGLFramework(argc, argv, w, h, title){}

	void CubeApp::OnKeys(int key, int x, int y)
	{
		if(key == GLUT_KEY_UP)
			objectFrame.RotateWorld(m3dDegToRad(-5.0f), 1.0f, 0.0f, 0.0f);
		if(key == GLUT_KEY_DOWN)
			objectFrame.RotateWorld(m3dDegToRad(5.0f), 1.0f, 0.0f, 0.0f);
		if(key == GLUT_KEY_LEFT)
			objectFrame.RotateWorld(m3dDegToRad(-5.0f), 0.0f, 1.0f, 0.0f);
		if(key == GLUT_KEY_RIGHT)
			objectFrame.RotateWorld(m3dDegToRad(5.0f), 0.0f, 1.0f, 0.0f);

		glutPostRedisplay();
	}

	void CubeApp::OnChangeSize(int w, int h)
	{
		glViewport(0,0,w,h);
		viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 500.0f);
		projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
		modelViewMatrix.LoadIdentity();
	}

	void CubeApp::SetupRC()
	{
		glClearColor(0.7f,0.7f,0.7f,1.0f);
		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		shaderManager.InitializeStockShaders();

		transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);

		cameraFrame.MoveForward(-15.0f);

		triangleBatch.Begin(GL_TRIANGLES, 36);
		triangleBatch.CopyVertexData3f(vCube);
		triangleBatch.End();
	}

	void CubeApp::OnRenderScene()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		modelViewMatrix.PushMatrix();
			M3DMatrix44f mCamera;
			cameraFrame.GetCameraMatrix(mCamera);
			modelViewMatrix.MultMatrix(mCamera);

			M3DMatrix44f mObject;
			objectFrame.GetMatrix(mObject);
			modelViewMatrix.MultMatrix(mObject);
		
			DrawWireFramedBatch(&triangleBatch);

		modelViewMatrix.PopMatrix();

		glutSwapBuffers();
	}

	void CubeApp::DrawWireFramedBatch(GLBatch* pBatch)
	{
		shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vGreen);
		pBatch->Draw();

		glPolygonOffset(-1.0f, -1.0f);
		glEnable(GL_POLYGON_OFFSET_LINE);

		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.5f);

		shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);
		pBatch->Draw();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_POLYGON_OFFSET_LINE);
		glLineWidth(1.0f);
		glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);

	}