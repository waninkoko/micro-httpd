/*
 * micro-httpd - A very lightweight HTTP server.
 *
 * Copyright (c) 2010, Miguel Boton <mboton at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Miguel nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <cstdlib>

#include "file.hpp"
#include "http.hpp"
#include "log.hpp"
#include "server.hpp"

#include "wii/fat.h"
#include "wii/gui.h"
#include "wii/network.h"
#include "wii/sys.h"
#include "wii/video.h"

using namespace std;

/* Global variables */
static CServer *Server = NULL;


void Quit(int dummy)
{
	CLog::Print("Terminating...");

	if (Server) {
		/* Stop server */
		Server->Stop();

		/* Delete server */
		delete Server;
	}

	/* Exit */
	exit(0);
}

int main(int argc, char **argv)
{
	unsigned short port;
	int res;

	/* Initialize system */
	Sys_Init();

	/* Set video mode */
	Video_SetMode();

	/* Initialize console */
	Gui_InitConsole();

	CLog::Print("Mounting SD card...");

	/* Initialize libfat */
	res = Fat_MountSD();
	if (res < 0) {
		CLog::PrintErr("ERROR: Could not mount the SD card!");
		goto out;
	}

	CLog::Print("Initializing network...");

	/* Initialize network */
	res = Network_Init();
	if (res < 0) {
		CLog::PrintErr("ERROR: Could not initialize the network!");
		goto out;
	}

	CLog::Print("IP address: %s\n", Network_GetIP());

	/* Initialize HTTP class */
	CHTTP::Init();

	/* Default port */
	port = 82;

	/* Set basepath */
	CFile::SetPath("sd:");

	/* Create server */
	Server = new CServer(port);
	if (!Server) {
		CLog::PrintErr("ERROR: Server could NOT be created!");
		goto out;
	}

	/* Start server */
	res = Server->Start();
	if (!res) {
		CLog::PrintErr("ERROR: Server could NOT be started!");
		goto out;
	}

	/* Keep waiting for connections */
	while (Server->Accept());

out:
	/* Quit */
	Quit(0);

	return 0;
}
