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

#include <ctime>

#include "header.hpp"
#include "http.hpp"
#include "main.hpp"

/* Constants */
#define CRLF	"\r\n"


CHeader::CHeader(void)
{
	/* Clear header */
	Clear();
}

CHeader::CHeader(string header)
{
	/* Set the header string */
	Set(header);
}

void CHeader::Clear(void)
{
	/* Clear header string */
	header.str("");
}

string CHeader::Generate(void)
{
	/* Return header string */
	return header.str();
}

bool CHeader::GetType(string &type)
{
	string str = Generate();

	size_t npos;

	/* Find the first space */
	npos = str.find_first_of(" ");

	/* Not found */
	if (npos == string::npos)
		return false;

	/* Extract the request type */
	type = str.substr(0, npos);

	return true;
}

bool CHeader::GetPath(string &path)
{
	string str = Generate();

	size_t pos, npos;

	/* Find the first space */
	pos = str.find_first_of(" ");

	/* Not found */
	if (pos == string::npos)
		return false;

	/* Find the second space */
	npos = str.find_first_of(" ", ++pos);

	/* Not found */
	if (npos == string::npos)
		return false;

	/* Extract the request path */
	path = str.substr(pos, npos - pos);

	return true;
}

void CHeader::Set(string header)
{
	/* Set the header string */
	this->header << header;
}

void CHeader::Set(const char *header)
{
	string s(header);

	/* Set the header string */
	Set(s);
}

void CHeader::AddReply(int reply)
{
	/* Add the HTTP reply string */
	header << "HTTP/1.1 " << reply << " " << CHTTP::GetDescription(reply) << CRLF;
}

void CHeader::AddLength(size_t len)
{
	/* Add the content length */
	header << "Content-length: " << len << CRLF;
}

void CHeader::AddDate(void)
{
	time_t     rawtime;
	struct tm *timeinfo;

	char date[128];

	/* Get time */
	time(&rawtime);

	/* Timezone conversion */
	timeinfo = localtime(&rawtime);

	/* Generate the date string */
	strftime(date, sizeof(date), "%a, %d %b %Y %X %Z", timeinfo);

	/* Add the date */
	header << "Date: " << date << CRLF;
}

void CHeader::AddServer(void)
{
	/* Add the server name */
	header << "Server: " << APP_NAME << "/" << APP_VERSION << CRLF;
}

void CHeader::AddEnd(void)
{
	header << CRLF;
}
