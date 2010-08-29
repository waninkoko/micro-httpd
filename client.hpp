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

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string>

#include "header.hpp"
#include "http.hpp"
#include "socket.hpp"

using namespace std;


/*!
	Client class.
	\author Miguel Boton Campo.
*/
class CClient {
	CSocket *Socket;			//!< Client socket object.

private:
	/*!
		Send a HTTP header to the client.
		\param header the header object.
		\returns true if success, otherwise false.
	*/
	bool SendHeader(CHeader &Header);

public:
	/*!
		Client object constructor.
		\param fd the client socket descriptor.
	*/
	CClient(CSocket *Socket);

	/*!
		Client object destructor.
	*/
	~CClient(void);

	/*!
		Disconnect the client.
	*/
	void Disconnect(void);

	/*!
		Read data from the client.
		\param buffer the data buffer pointer.
		\param len the data buffer length.
		\returns the number of bytes read.
	*/
	ssize_t Read(void *buffer, size_t len);

	/*!
		Write data to the client.
		\param buffer the data buffer pointer.
		\param len the data buffer length.
		\returns the number of bytes written.
	*/
	ssize_t Write(const void *buffer, size_t len);

	/*!
		Read data from the client.
		The loop finishes when the buffer is filled.
		\param buffer the data buffer pointer.
		\param len the data buffer length.
		\returns the number of bytes read.
	*/
	ssize_t ReadLoop(void *buffer, size_t len);

	/*!
		Send data to the client.
		\param buffer the data buffer pointer.
		\param len the data buffer length.
		\returns true if success, otherwise false.
	*/
	bool Send(const void *buffer, size_t len, int reply = REPLY_OK);

	/*!
		Send file to the client.
		\param filepath the file to send.
		\returns true if success, otherwise false.
	*/
	bool SendFile(string filepath);
	bool SendFile(const char *filepath);

	/*!
		Receive request from the client.
		\param header the header object.
		\returns true if success, otherwise false.
	*/
	bool RecvRequest(CHeader &Header);

	/*!
		Handle a request error.
		\param reply the request reply number.
	*/
	bool HandleError(int reply);
};

#endif	/* _CLIENT_H_ */
