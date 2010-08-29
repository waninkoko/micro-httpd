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

#include "thread.hpp"


CMutex::CMutex(void)
{
	/* Initialize the mutex */
	pthread_mutex_init(&mutex, NULL);
}

CMutex::~CMutex(void)
{
	/* Destroy the mutex */
	pthread_mutex_destroy(&mutex);
}

bool CMutex::Lock(void)
{
	int res;

	/* Lock the mutex */
	res = pthread_mutex_lock(&mutex);
	if (res)
		return false;

	return true;
}

bool CMutex::Unlock(void)
{
	int res;

	/* Unlock the mutex */
	res = pthread_mutex_unlock(&mutex);
	if (res)
		return false;

	return true;
}


CThread::~CThread(void)
{
	/* Destroy thread */
	Destroy();
}

bool CThread::Create(void *(*routine)(void *), void *arg)
{
	int res;

	/* Create thread */
	res = pthread_create(&thread, NULL, routine, arg);
	if (res)
		return false;

	return true;
}

bool CThread::Destroy(void)
{
	int res;

	/* Destroy thread */
	res = pthread_cancel(thread);
	if (res)
		return false;

	return true;
}

bool CThread::Join(void)
{
	int res;

	/* Join thread */
	res = pthread_join(thread, NULL);
	if (res)
		return false;

	return true;
}

void CThread::Exit(void *ret)
{
	/* Terminate thread */
	pthread_exit(ret);
}

