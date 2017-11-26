#include "CConsle.h"
#include "define.h"

void CConsole::Render()
{
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glRecti(0, WINDOWS_HEIGHT / 2, WINDOWS_WIDTH - 100, WINDOWS_HEIGHT);

}