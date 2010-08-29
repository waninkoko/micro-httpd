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

#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include <ogcsys.h>


/*!
	Socket object class.
	\author Miguel Boton Campo
*/
class CSocket {
	s32 sockFd;	//!< Socket descriptor.

public:
	/*!
		Socket object constructor.
	*/
	CSocket(void);

	/*!
		Socket object constructor.
		\param fd the socket descriptor.
	*/
	CSocket(int fd);

	/*!
		Socket object destructor.
	*/
	~CSocket(void);

	/*!
		Create a socket.
		\returns true if success, false otherwise.
	*/
	bool Create(void);

	/*!
		Destroy the socket.
	*/
	void Destroy(void);

	/*!
		Bind the socket to a port.
		\param port the port to bind the socket.
		\returns true if success, otherwise false.
	*/
	bool Bind(unsigned short port);

	/*!
		Listen for incoming connections.
		\param max maximum number of simultaneously connections.
		\returns true if success, otherwise false.
	*/
	bool Listen(unsigned int max);

	/*!
		Accept incoming connection.
	*/
	CSocket *Accept(void);

	/*!
		Send data through the socket.
		\param buffer the buffer pointer.
		\param len the buffer length.
		\returns the number of bytes sent.
	*/
	ssize_t Send(const void *buffer, size_t len);

	/*!
		Receive data through the socket.
		\param buffer the buffer pointer.
		\param len the buffer length.
		\returns the number of bytes received.
	*/
	ssize_t Receive(void *buffer, size_t len);
};

#endif	/* _NETWORK_HPP_ */
