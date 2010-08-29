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

#include <sstream>

#include "file.hpp"


string CFile::basepath = ".";


string CFile::GetPath(void)
{
	/* Return the basepath */
	return basepath;
}

void CFile::SetPath(string dirpath)
{
	/* Set the basepath */
	basepath = dirpath;
}

void CFile::SetPath(const char *dirpath)
{
	string s(dirpath);

	/* Set the basepath */
	SetPath(s);
}

bool CFile::Open(string filepath)
{
	const char *s = filepath.c_str();

	/* Open file */
	return Open(s);
}

bool CFile::Open(const char *filepath)
{
	stringstream spath;
	const char  *fpath;

	/* Close file */
	Close();

	/* Generate path */
	spath << basepath << filepath;

	/* Path string */
	fpath = spath.str().c_str();

	/* Open file */
	file.open(fpath);

	/* Check if opened */
	return file.is_open();
}

void CFile::Close(void)
{
	/* Close file */
	file.close();
}

size_t CFile::Size(void)
{
	size_t pos, size;

	/* Save position */
	pos = file.tellg();

	/* Move to the end */
	file.seekg(0, ios::end);

	/* Get position */
	size = file.tellg();

	/* Restore position */
	file.seekg(pos, ios::beg);

	return size;
}

bool CFile::Read(void *buffer, size_t len)
{
	char *ptr = static_cast<char *>(buffer);

	/* Read data */
	file.read(ptr, len);

	return true;
}

bool CFile::Write(void *buffer, size_t len)
{
	char *ptr = static_cast<char *>(buffer);

	/* Write data */
	file.write(ptr, len);

	return true;
}

char *CFile::Get(void)
{
	char *buffer;

	size_t len;
	bool   res;

	/* Get file size */
	len = Size();	

	/* Allocate buffer */
	buffer = new char[len];
	if (!buffer)
		return NULL;

	/* Read file */
	res = Read(buffer, len);

	/* Read error */
	if (!res) {
		/* Free buffer */
		delete buffer;

		/* NULL pointer */
		buffer = NULL;
	}

	return buffer;
}
