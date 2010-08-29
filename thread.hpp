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

#ifndef _THREAD_HPP_
#define _THREAD_HPP_

#include <ogcsys.h>


/*!
	Mutex abstraction class.
	\author Miguel Boton Campo
*/
class CMutex {
	mutex_t mutex;	//!< Mutex object.

public:
	/*!
		Mutex object constructor.
	*/
	CMutex(void);

	/*!
		Mutex object destructor.
	*/
	~CMutex(void);

	/*!
		Lock the mutex.
		\returns true if success, otherwise false.
	*/
	bool Lock(void);

	/*!
		Unlock the mutex.
		\returns true if success, otherwise false.
	*/
	bool Unlock(void);
};


/*!
	Thread abstraction class.
	\author Miguel Boton Campo
*/
class CThread {
	lwp_t thread;	//!< Thread object.

public:
	/*!
		Thread object destructor.
	*/
	~CThread(void);

	/*!
		Create a thread.
		\param routine the routine to be executed in the thread.
		\param arg the argument to be passed to the routine.
		\returns true if success, otherwise false.
	*/
	bool Create(void *(*routine)(void *), void *arg);

	/*!
		Destroy the thread.
		\returns true if success, otherwise false.
	*/
	bool Destroy(void);

	/*!
		Join the thread.
		\returns true if success, otherwise false.
	*/
	bool Join(void);

	/*!
		Terminate the thread
		(to be called from the thread routine).
		\param ret the return value pointer.
	*/
	static void Exit(void *ret);
};

#endif	/* _THREAD_HPP_ */
