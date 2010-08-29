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

#include <cstdio>
#include <network.h>
#include <sys/types.h>

#include "log.hpp"
#include "socket.hpp"


CSocket::CSocket(void)
{
	/* Reset descriptor */
	sockFd = -1;
}

CSocket::CSocket(int fd)
{
	/* Set descriptor */
	sockFd = fd;
}

CSocket::~CSocket(void)
{
	/* Destroy socket */
	Destroy();
}

bool CSocket::Create(void)
{
	/* Destroy socket */
	Destroy();

	/* Create socket */
	sockFd = net_socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd < 0)
		return false;

	return true;
}

void CSocket::Destroy(void)
{
	/* Shutdown socket */
	if (sockFd >= 0)
		net_shutdown(sockFd, 2);

	/* Reset descriptor */
	sockFd = -1;
}

bool CSocket::Bind(unsigned short port)
{
	struct sockaddr_in sockAddr;

	int res;

	/* Socket address */
	sockAddr.sin_family      = AF_INET;
	sockAddr.sin_port        = htons(port);
	sockAddr.sin_addr.s_addr = INADDR_ANY;

	/* Bind address to socket */
	res = net_bind(sockFd, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
	if (res == -1)
		return false;

	return true;
}

bool CSocket::Listen(unsigned int max)
{
	int res;

	/* Listen for connections */
	res = net_listen(sockFd, max);
	if (res == -1)
		return false;

	return true;
}

CSocket *CSocket::Accept(void)
{
	struct sockaddr_in sockAddr;
	socklen_t sockLen;

	int fd;

	/* Socket address length */
	sockLen = sizeof(sockAddr);

	/* Accept incoming connection */
	fd = net_accept(sockFd, (struct sockaddr *)&sockAddr, &sockLen);	
	if (fd == -1)
		return NULL;

	/* Create socket */
	return (new CSocket(fd));
}

ssize_t CSocket::Send(const void *buffer, size_t len)
{
	/* Send buffer */
	return net_send(sockFd, buffer, len, 0);
}

ssize_t CSocket::Receive(void *buffer, size_t len)
{
	/* Receive buffer */
	return net_recv(sockFd, buffer, len, 0);
}
