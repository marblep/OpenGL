#include "Skybox.h"
#include "SphereReflect.h"

int main(int argc, char* argv[])
{
	//SkyboxApp app(argc, argv, 800, 600, "Skybox");
	SphereReflect app(argc, argv, 800, 600, "Sphere Reflect");
	app.Run();
	return 0;
}