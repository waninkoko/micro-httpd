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
#include <errno.h>

#include "client.hpp"
#include "header.hpp"
#include "log.hpp"
#include "server.hpp"
#include "utils.hpp"

using namespace std;


CServer::CServer(unsigned short port)
{
	/* Set port number */
	this->port = port;
}

CServer::~CServer(void)
{
	/* Stop server */
	Stop();
}

void *CServer::Handler(void *client)
{
	CClient *Client = static_cast<CClient *>(client);
	bool     res;

	/* Thread loop */
	while (1) {
		CHeader Header;
		string  path, type;

		/* Receive request */
		res = Client->RecvRequest(Header);
		if (!res)
			break;

		/* Get request type/path */
		Header.GetType(type);
		Header.GetPath(path);

		/* Show request info */
		CLog::Print("Request type: %s\n"
			    "Request path: %s", type.c_str(), path.c_str());

		/* Check request type */
		if (!type.compare("GET")) {
			/* Check path */
			if (!path.compare("/"))
				path = "/index.html";

			/* Send file */
			res = Client->SendFile(path);
		} else {
			/* Bad request */
			res = Client->HandleError(REPLY_BADREQ);
		}

		/* Disconnect if error */
		if (!res)
			break;
	}

	CLog::Print("Disconnecting...");

	/* Disconnect client */
	Client->Disconnect();

	/* Delete client */
	delete Client;

	return NULL;
}

bool CServer::Start(void)
{
	bool res;

	/* Create socket */
	res = Socket.Create();
	if (!res) {
		CLog::PrintErr("ERROR: Socket creation failed!");
		return false;
	}

	/* Bind address */
	res = Socket.Bind(port);
	if (!res) {
		CLog::PrintErr("ERROR: Bind address failed!");
		return false;
	}

	/* Listen for connections */
	res = Socket.Listen(10);
	if (!res) {
		CLog::PrintErr("ERROR: Listen failed!");
		return false;
	}

	return true;
}

void CServer::Stop(void)
{
	vector<CThread *>::iterator it;

	/* Destroy socket */
	Socket.Destroy();

	/* Destroy threads */
	foreach (threads, it) {
		CThread *Thread = *it;

		CLog::Print("Destroying thread...");

		/* Destroy thread */
		Thread->Destroy();

		/* Join thread */
		Thread->Join();

		/* Delete thread */
		delete Thread;
	}

	/* Clear threads array */
	threads.clear();
}

bool CServer::CreateThread(CSocket *Socket)
{
	CClient *Client;
	CThread *Thread;

	bool res;

	/* Create client object */
	Client = new CClient(Socket);
	if (!Client)
		return false;

	/* Create thread object */
	Thread = new CThread();
	if (!Thread)
		return false;

	/* Create thread */
	res = Thread->Create(Handler, Client);
	if (!res)
		return false;

	/* Push thread into the array */
	threads.push_back(Thread);

	return true;
}

bool CServer::Accept(void)
{
	CSocket *Client;

	CLog::Print("Waiting for incoming connection...");

	/* Accept incoming connection */
	Client = Socket.Accept();
	if (!Client) {
		CLog::PrintErr("ERROR: Accept connection failed!");
		return false;
	}

	/* Show connection info */
	//cout << "Connection received!" << endl;
	//cout << "   IP Address: " << inet_ntoa(sockAddr.sin_addr) << endl;
	//cout << "   Port: " << htons(sockAddr.sin_port) << endl;
	//cout << endl;

	/* Create thread */
	return CreateThread(Client);
}

