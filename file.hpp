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

#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <fstream>
#include <string>

using namespace std;


/*!
	File class.
	\author Miguel Boton Campo
*/
class CFile {
	static string basepath;		//!< File basepath.

	fstream file;			//!< File object.

public:
	/*!
		Get the basepath.
		\returns the current basepath.
	*/
	static string GetPath(void);

	/*!
		Set the basepath.
		\param dirpath the directory to use as base.
	*/
	static void SetPath(string dirpath);
	static void SetPath(const char *dirpath);

	/*!
		Open a file.
		\param filepath the file path.
		\returns true if success, otherwise false.	
	*/
	bool Open(string filepath);
	bool Open(const char *filepath);

	/*!
		Close the file.
	*/
	void Close(void);

	/*!
		Get the file size.
		\returns the file size.
	*/
	size_t Size(void);

	/*!
		Read data from the file.
		\param buffer the buffer to store the data.
		\param len the number of bytes to read.
		\returns true if success, otherwise false.
	*/
	bool Read(void *buffer, size_t len);

	/*!
		Write data to the file.
		\param buffer the buffer to write.
		\param len the buffer length.
		\returns true if success, otherwise false.
	*/
	bool Write(void *buffer, size_t len);

	/*!
		Get buffer with the file contents.
		\returns the buffer pointer.
	*/
	char *Get(void);
};

#endif	/* _FILE_HPP_ */
