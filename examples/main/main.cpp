
/*
 Copyright (c) 2014, The eve Project
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of the {organization} nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/messaging/Includes.h"
#endif

#ifndef __EVE_THREADING_INCLUDES_H__
#include "eve/threading/Includes.h"
#endif

int main(int argc, char **argv)
{
	// Hide console window in release mode.
#if defined(NDEBUG)
	: ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif	

	eve::messaging::Server::create_instance();
	EVE_LOG_INFO("eve Version: %s", EVE_VERSIONNAME);
	eve::messaging::Server::release_instance();


	// Pointer example //

	// Create thread pointer.
	eve::threading::ThreadDummy * thr = EVE_CREATE_PTR(eve::threading::ThreadDummy);
	// Start thread.
	thr->start();
	// Sleep using microseconds.
	eve::threading::sleep_micro(1000ULL * 1000ULL);
	// Release pointer.
	EVE_RELEASE_PTR(thr);


	//-------------------------------------------


	// Scoped pointer example //

	// Create scoped thread pointer.
	eve::memory::Scoped<eve::threading::ThreadDummy> scThr;
	// Start thread.
	scThr->start();

	// Sleep using milliseconds.
	eve::threading::sleep_milli(1000);

	return 0;
}
