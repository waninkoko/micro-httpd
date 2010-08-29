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

#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#include <sstream>
#include <string>

using namespace std;


/*!
	HTTP header parser class.
	\author Miguel Boton Campo
*/
class CHeader {
	stringstream header;	//!< Header string.

public:
	/*!
		Header object constructor.
	*/
	CHeader(void);

	/*!
		Header object constructor.
		\param header the http header string.
	*/
	CHeader(string header);

	/*!
		Clear header string.
	*/
	void Clear(void);

	/*!
		Generate the HTTP header.
		\returns the generated HTTP header string.
	*/
	string Generate(void);

	/*!
		Parse the request type.
		\param type the string buffer to store the type string.
		\returns true if success, otherwise false.
	*/
	bool GetType(string &type);

	/*!
		Parse the request path.
		\param path the string buffer to store the path string.
		\returns true if success, otherwise false.
	*/
	bool GetPath(string &path);

	/*!
		Set the header string.
		\param header the header string.
	*/
	void Set(string header);
	void Set(const char *header);

	/*!
		Add the HTTP reply.
		\param reply the reply number.
	*/
	void AddReply(int reply);

	/*!
		Add the content length string.
		\param len the content length.
	*/
	void AddLength(size_t len);

	/*!
		Add the date.
	*/
	void AddDate(void);

	/*!
		Add the server name string.
	*/
	void AddServer(void);

	/*!
		Add the ending char sequence.
	*/
	void AddEnd(void);
};

#endif	/* _HEADER_HPP_ */
