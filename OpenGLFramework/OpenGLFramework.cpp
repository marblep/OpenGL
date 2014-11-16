#include "OpenGLFramework.h"

OpenGLFramework* OpenGLFramework::m_app = NULL;

void OpenGLFramework::Run()
{
	if(InitOpenGLState() == false)
		exit(EXIT_FAILURE);

	SetupRC();
	glutMainLoop();
}

OpenGLFramework::OpenGLFramework(int argc, char* argv[], int w, int h, const char *title)
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	
	m_app = this;

	InitWindow(w,h,title);

	
}

bool OpenGLFramework::InitOpenGLState()
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

	return true;
}

void OpenGLFramework::InitWindow(int w, int h, const char *title)
{
	glutInitWindowSize(w, h);
	glutCreateWindow(title);
}

void OpenGLFramework::SetupRC()
{

}

void OpenGLFramework::OnChangeSize(int w, int h)
{
	glViewport(0,0,w,h);
}

void OpenGLFramework::OnRenderScene()
{

}

void OpenGLFramework::OnKeys(int key, int x, int y)
{

}

void ChangeSize(int w, int h)
{
	OpenGLFramework::m_app->OnChangeSize(w,h);
}

void RenderScene()
{
	OpenGLFramework::m_app->OnRenderScene();
}

void Keys(int key, int x, int y)
{
	OpenGLFramework::m_app->OnKeys(key,x,y);
}
