#include "Skybox.h"

SkyboxApp::SkyboxApp(int argc, char* argv[], int w, int h, const char *title) : OpenGLFramework(argc, argv, w, h, title){}

void SkyboxApp::SetupRC()
{
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	LoadCubeMap();

	//viewFrame.MoveForward(-4.0);

	gltMakeCube(cubeBatch, 20.0f);

	skyBoxShader = gltLoadShaderPairWithAttributes("SkyBox.vp", "SkyBox.fp", 1, GLT_ATTRIBUTE_VERTEX, "vVertex");
	locMVPSkyBox = glGetUniformLocation(skyBoxShader, "mvpMatrix");
}



void SkyboxApp::OnRenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	M3DMatrix44f mCameraRotOnly;
	viewFrame.GetCameraMatrix(mCameraRotOnly, true);

	modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(mCameraRotOnly);
		glUseProgram(skyBoxShader);
		glUniformMatrix4fv(locMVPSkyBox, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
		cubeBatch.Draw();
	modelViewMatrix.PopMatrix();

	glutSwapBuffers();
}

void SkyboxApp::LoadCubeMap()
{
	GLuint cubeTexture;
	const char *szCubeFaces[6] = { "textures\\pos_x.tga", "textures\\neg_x.tga", 
									"textures\\pos_y.tga", "textures\\neg_y.tga", 
									"textures\\pos_z.tga", "textures\\neg_z.tga" };

	GLenum  cube[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
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
	for(int i = 0; i < 6; i++)
	{
		pBytes = gltReadTGABits(szCubeFaces[i], &iWidth, &iHeight, &iComponents, &eFormat);
		glTexImage2D(cube[i], 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
		free(pBytes);
	}
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

void SkyboxApp::OnChangeSize(int w, int h)
{
	if(h == 0)
        h = 1;
    
    glViewport(0, 0, w, h);
    
    viewFrustum.SetPerspective(35.0f, float(w)/float(h), 1.0f, 1000.0f);
    
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void SkyboxApp::OnKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)
		viewFrame.RotateLocalX(0.1f);

    if(key == GLUT_KEY_DOWN)
        viewFrame.RotateLocalX(-0.1f);

    if(key == GLUT_KEY_LEFT)
        viewFrame.RotateLocalY(0.1);
      
    if(key == GLUT_KEY_RIGHT)
        viewFrame.RotateLocalY(-0.1);
                        
    glutPostRedisplay();
}