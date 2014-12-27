#include "SphereReflect.h"

SphereReflect::SphereReflect(int argc, char* argv[], int w, int h, const char *title) : OpenGLFramework(argc, argv, w, h, title){}

void SphereReflect::SetupRC()
{
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	LoadCubeMap();

	viewFrame.MoveForward(-4.0);

	gltMakeSphere(sphereBatch, 1.0f, 52, 26);

	reflectionShader = gltLoadShaderPairWithAttributes("Reflection.vp", "Reflection.fp", 2,
		GLT_ATTRIBUTE_VERTEX, "vVertex",
		GLT_ATTRIBUTE_NORMAL, "vNormal");

	locMVPReflect = glGetUniformLocation(reflectionShader, "mvpMatrix");
	locMVReflect = glGetUniformLocation(reflectionShader, "mvMatrix");
	locNormalReflect = glGetUniformLocation(reflectionShader, "normalMatrix");
	locInvertedCamera = glGetUniformLocation(reflectionShader, "mInverseCamera");
	locCubeSampler = glGetUniformLocation(reflectionShader, "cubeMap");
}



void SphereReflect::OnRenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	M3DMatrix44f mCamera;
	M3DMatrix44f mCameraRotOnly;
	M3DMatrix44f mInverseCamera;

	viewFrame.GetCameraMatrix(mCamera, false);
	viewFrame.GetCameraMatrix(mCameraRotOnly, true);
	m3dInvertMatrix44(mInverseCamera, mCameraRotOnly);

	modelViewMatrix.PushMatrix();
	// Draw the sphere
	modelViewMatrix.MultMatrix(mCamera);
	glUseProgram(reflectionShader);
	glUniformMatrix4fv(locMVPReflect, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
	glUniformMatrix4fv(locMVReflect, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
	glUniformMatrix3fv(locNormalReflect, 1, GL_FALSE, transformPipeline.GetNormalMatrix());
	glUniformMatrix4fv(locInvertedCamera, 1, GL_FALSE, mInverseCamera);
	glUniform1i(locCubeSampler, 0);

	glEnable(GL_CULL_FACE);
	sphereBatch.Draw();
	glDisable(GL_CULL_FACE);
	modelViewMatrix.PopMatrix();

	glutSwapBuffers();
}

void SphereReflect::LoadCubeMap()
{
	GLuint cubeTexture;
	const char *szCubeFaces[6] = { "textures\\pos_x.tga", "textures\\neg_x.tga",
		"textures\\pos_y.tga", "textures\\neg_y.tga",
		"textures\\pos_z.tga", "textures\\neg_z.tga" };

	GLenum  cube[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glGenTextures(1, &cubeTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLbyte *pBytes;
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
	for (int i = 0; i < 6; i++)
	{
		pBytes = gltReadTGABits(szCubeFaces[i], &iWidth, &iHeight, &iComponents, &eFormat);
		glTexImage2D(cube[i], 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
		free(pBytes);
	}
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

void SphereReflect::OnChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	viewFrustum.SetPerspective(35.0f, float(w) / float(h), 1.0f, 1000.0f);

	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void SphereReflect::OnKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		viewFrame.RotateLocalX(0.1f);

	if (key == GLUT_KEY_DOWN)
		viewFrame.RotateLocalX(-0.1f);

	if (key == GLUT_KEY_LEFT)
		viewFrame.RotateLocalY(0.1);

	if (key == GLUT_KEY_RIGHT)
		viewFrame.RotateLocalY(-0.1);

	glutPostRedisplay();
}