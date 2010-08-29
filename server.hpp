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

#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <vector>

#include "socket.hpp"
#include "thread.hpp"

using namespace std;


/*!
	Server class.
	\author Miguel Boton Campo
*/
class CServer {
	CSocket Socket;			//!< Socket object.

	vector <CThread *> threads;	//!< Thread array.
	unsigned short port;		//!< Server port number.

private:
	/*!
		Client connection handler.
		\param client the client object pointer.
	*/
	static void *Handler(void *client);

	/*!
		Create a client thread.
		\param Socket the client socket object.
		\returns true if sucess, otherwise false.
	*/
	bool CreateThread(CSocket *Socket);

public:
	/*!
		Server object constructor.
		\param port the port to bind to the server (80 default).
	*/
	CServer(unsigned short port = 80);

	/*!
		Server object destructor.
	*/
	~CServer(void);

	/*!
		Start the server.
		\returns true if success, otherwise false.
	*/
	bool Start(void);

	/*!
		Stop the server.
	*/
	void Stop(void);

	/*!
		Accept an incoming connection.
		\returns true if success, otherwise false.
	*/
	bool Accept(void);
};

#endif	/* _HTTP_HPP */
