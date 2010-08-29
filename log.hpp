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

#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <cstdio>
#include <cstdarg>

#include "thread.hpp"


/*
	Server log class.
	\author Miguel Boton Campo
*/
class CLog {
	static CMutex Mutex;	//!< Mutex object.

private:
	/*!
		Print a formatted message to a stream.
		\param stream the target stream.
		\param fmt the message format.
		\param args the list of arguments.
	*/
	static void PrintStream(FILE *stream, const char *fmt, va_list args);

public:
	/*!
		Print a formatted message.
		\param fmt the message format.
	*/
	static void Print(const char *fmt, ...);

	/*!
		Print a formatted error message.
		\param fmt the message format.
	*/
	static void PrintErr(const char *fmt, ...);

};

#endif	/* _LOG_HPP_ */
