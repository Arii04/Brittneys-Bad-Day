#include "stdafx.h"
#include "MyGame.h"

CMyGame game;
CGameApp app;

int main(int argc, char* argv[])
{
	//app.DebugMemoryLeaks();
	app.OpenWindow(800, 600, "World scroller");
	//app.OpenFullScreen(800, 600, 24);
	//app.OpenConsole();
	app.SetClearColor(CColor::LightGray());
	app.Run(&game);
	return(0);
}
