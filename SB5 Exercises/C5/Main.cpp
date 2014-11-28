#include "CaptureToTGA.h"

int main(int argc, char* argv[])
{
	CaptureToTGAApp app(argc, argv, 800, 600, "Sun Earth Moon");
	app.Run();
	return 0;
}