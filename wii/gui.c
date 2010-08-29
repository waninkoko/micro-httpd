#include <stdio.h>
#include <ogcsys.h>

#include "video.h"

/* Constants */
#define CONSOLE_XCOORD		20
#define CONSOLE_YCOORD		20
#define CONSOLE_WIDTH		600
#define CONSOLE_HEIGHT		440


void Gui_InitConsole(void)
{
	/* Initialize console */
	Con_Init(CONSOLE_XCOORD, CONSOLE_YCOORD, CONSOLE_WIDTH, CONSOLE_HEIGHT);
}
