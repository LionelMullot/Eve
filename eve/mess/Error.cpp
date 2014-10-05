
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

// Main header
#include "eve/mess/Error.h"


#if defined(EVE_OS_WIN)

	//=================================================================================================
	std::wstring eve::mess::get_error_msg(DWORD p_err)
	{
		std::wstring returnString;

		wchar_t buffer[2048];
		try
		{
			DWORD len = 0;
			LPWSTR msg = nullptr;

			len = ::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								   NULL,
								   p_err,
								   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
								   (LPWSTR)&msg, 0, NULL);
			if (len > 0)
			{
				_snwprintf(buffer, 2048 * sizeof(wchar_t), EVE_TXT("error (%d): %s."), p_err, msg);
			}
			else
			{
				_snwprintf(buffer, 2048 * sizeof(wchar_t), EVE_TXT("error code: %d."), p_err);
			}

			returnString = std::wstring(buffer);

			if (msg) ::LocalFree(msg);

		}
		catch (...)
		{
			returnString = EVE_TXT("Can't get Win32 error message");
		}
		return returnString;
	}

	//=================================================================================================
	std::wstring eve::mess::get_error_msg(void)
	{
		return eve::mess::get_error_msg(::GetLastError());
	}

#endif // defined(EVE_OS_WIN)
