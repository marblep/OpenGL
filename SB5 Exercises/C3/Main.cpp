#include "Cube.h"
#include "Triangle.h"
#include "Blend.h"

int main(int argc, char* argv[])
{
	BlendApp app(argc, argv, 800, 600, "BlendApp");
	app.Run();
	return 0;
}