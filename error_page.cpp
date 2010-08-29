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

#include "error_page.hpp"
#include "http.hpp"
#include "main.hpp"

using namespace std;


string CErrorPage::Get(int reply)
{
	string page;

	/* Check reply code */
	switch (reply) {
	case REPLY_NOENT:	/* 404 */
		page = E404();
		break;
	case REPLY_INTERR:	/* 500 */
		page = E500();
		break;
	case REPLY_NOTIMP:	/* 501 */
		page = E501();
		break;
	default:
		page = Generate(reply);
	}

	return page;
}

string CErrorPage::Generate(int reply)
{
	stringstream ss;
	string       desc;

	/* Get the description */
	desc = CHTTP::GetDescription(reply);

	/* No description */
	if (desc.empty())
		desc = "Unknown";

	/* HTML code */
	ss << "<html>" << endl;
	ss << "<head><title>Error " << reply << " - " << desc << "</title></head>" << endl;
	ss << "<body><h1>Error "    << reply << " - " << desc << "</h1>" << endl;
	ss << "<hr>" << APP_NAME << "/" << APP_VERSION << "</hr></body>" << endl;
	ss << "</html>";

	/* Return string */
	return ss.str();
}

string CErrorPage::E404(void)
{
	stringstream ss;
	string       desc;

	/* Get the description */
	desc = CHTTP::GetDescription(404);

	/* HTML code */
	ss << "<html>" << endl;
	ss << "<head><title>Error 404 - " << desc << "</title></head>" << endl;
	ss << "<body><h1>Error 404 - " << desc << "</h1>" << endl;
	ss << "<h3>The requested page does not exist.</h3>" << endl;
	ss << "<hr>" << APP_NAME << "/" << APP_VERSION << "</hr></body>" << endl;
	ss << "</html>";

	/* Return string */
	return ss.str();
}

string CErrorPage::E500(void)
{
	stringstream ss;
	string       desc;

	/* Get the description */
	desc = CHTTP::GetDescription(500);

	/* HTML code */
	ss << "<html>" << endl;
	ss << "<head><title>Error 500 - " << desc << "</title></head>" << endl;
	ss << "<body><h1>Error 500 - " << desc << "</h1>" << endl;
	ss << "<hr>" << APP_NAME << "/" << APP_VERSION << "</hr></body>" << endl;
	ss << "</html>";

	/* Return string */
	return ss.str();
}

string CErrorPage::E501(void)
{
	stringstream ss;
	string       desc;

	/* Get the description */
	desc = CHTTP::GetDescription(501);

	/* HTML code */
	ss << "<html>" << endl;
	ss << "<head><title>Error 501 - " << desc << "</title></head>" << endl;
	ss << "<body><h1>Error 501 - " << desc << "</h1>" << endl;
	ss << "<hr>" << APP_NAME << "/" << APP_VERSION << "</hr></body>" << endl;
	ss << "</html>";

	/* Return string */
	return ss.str();
}
