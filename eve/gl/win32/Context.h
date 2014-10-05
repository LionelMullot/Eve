
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

#pragma once
#ifndef __EVE_OPENGL_CONTEXT_H__
#define __EVE_OPENGL_CONTEXT_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_MEMORY_INCLUDES_H__
#include "eve/mem/Includes.h"
#endif

#ifndef __EVE_MESSAGING_INCLUDES_H__
#include "eve/mess/Includes.h"
#endif

#ifndef __EVE_OPENGL_PIXEL_FORMAT_H__
#include "eve/gl/win32/PixelFormat.h"
#endif



namespace eve { namespace thr { class SpinLock; } }


namespace eve
{
	namespace gl
	{
		/** 
		* \class eve::gl::Context
		*
		* \brief OpenGL master context.
		* Create and manage rendering context (GLRC) based on available pixel format.
		*
		* \note extends mem::Pointer
		*/
		class Context final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			static eve::gl::Context *		m_p_instance;			//<! Class unique instance.
			static eve::thr::SpinLock *		m_p_fence;				//!< Context activation fence.
			
			HGLRC							m_hGLRC;				//!< OpenGL rendering context handle.
			HDC								m_hDC;					//!< Draw context (linked to window) handle.

			eve::gl::PixelFormat			m_pixelFormat;			//!< Pixel format.
			PIXELFORMATDESCRIPTOR			m_pixelFormatDecriptor;	//!< Pixel format descriptor.
			int32_t							m_pixelFormatId;		//!< Pixel format ID.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Context);
			EVE_PROTECT_DESTRUCTOR(Context);


		public:
			/** \brief Create unique instance. */
			static eve::gl::Context * create_instance(void);
			/** \brief Release unique instance */
			static void release_instance(void);


		private:
			/** \brief Class constructor. */
			Context(void);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/**
			* \brief Release and delete class members. (pure virtual)
			* Stop this object's thread execution (if any) immediately.
			*/
			virtual void release(void) override;


		private:
			/** \brief Init GLEW and test required OpenGL version. */
			void initOpenGL(void);


			/** 
			* \brief Choose available pixel format, as close to desired options as possible depending on hardware
			* \param p_pPfd pixel format descriptor as PIXELFORMATDESCRIPTOR pointer.
			* \return Chosen pixel format ID as int32_t.
			*/
			int32_t choosePixelFormat(void);


			/** \brief DC attached pixel format may change selected options, grab and stock updated values. */
			void updateFormatVersion(void);


			///////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get OpenGL rendering context handle. */
			static const HGLRC get_handle(void);


			/** \brief Get pixel format. */
			static const eve::gl::PixelFormat & get_pixel_format(void);
			/** \brief Get pixel format descriptor. */
			static const PIXELFORMATDESCRIPTOR & get_pixel_format_descriptor(void);
			/** \brief Get pixel format ID. */
			static const int32_t get_pixel_format_ID(void);


			/** \brief Get unique instance. */
			static eve::gl::Context * get_instance(void);
			/** \brief Get fence (SpinLock). */
			static eve::thr::SpinLock * get_fence(void);

		}; // class Context

	} // namespace gl

} // namespace eve


/** \def EveContextGL: Convenience macro to access OpenGL context instance. */
#define EveContextGL	eve::gl::Context::get_instance()


//=================================================================================================
inline eve::gl::Context *	eve::gl::Context::get_instance(void)	{ EVE_ASSERT(m_p_instance);		return m_p_instance;	}
inline eve::thr::SpinLock * eve::gl::Context::get_fence(void)		{ EVE_ASSERT(m_p_fence);		return m_p_fence;		}

//=================================================================================================
inline const HGLRC			eve::gl::Context::get_handle(void)		{ EVE_ASSERT(m_p_instance);		return m_p_instance->m_hGLRC; }

//=================================================================================================
inline const eve::gl::PixelFormat &		eve::gl::Context::get_pixel_format(void)			{ EVE_ASSERT(m_p_instance);  return m_p_instance->m_pixelFormat;			}
inline const PIXELFORMATDESCRIPTOR &	eve::gl::Context::get_pixel_format_descriptor(void)	{ EVE_ASSERT(m_p_instance);  return m_p_instance->m_pixelFormatDecriptor;	}
inline const int32_t					eve::gl::Context::get_pixel_format_ID(void)			{ EVE_ASSERT(m_p_instance);  return m_p_instance->m_pixelFormatId;			}



namespace eve
{
	namespace gl
	{
		/**
		* \class eve::gl::SubContext
		*
		* \brief OpenGL window binded context linked to master context (aka eve::gl::Context).
		*
		* \note extends mem::Pointer
		*/
		class SubContext final
			: public eve::mem::Pointer
		{

			friend class eve::mem::Pointer;

			//////////////////////////////////////
			//				DATA				//
			//////////////////////////////////////

		private:
			static eve::gl::SubContext *		m_p_context_current;		//<! Current OpenGL context.

		private:
			HDC									m_hDC;						//!< Draw context (linked to window) handle.
			HWND								m_hWnd;						//!< Window handle.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(SubContext);
			EVE_PROTECT_CONSTRUCTOR_DESTRUCTOR(SubContext);

		public:
			/**
			* \brief Create and return new pointer.
			* \param p_hWnd linked window handle.
			*/
			static eve::gl::SubContext * create_ptr(HWND p_hWnd);


		private:
			/** 
			* \brief Class constructor.
			* \param p_hWnd linked window handle.
			*/
			SubContext(HWND p_hWnd);


		private:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/**
			* \brief Release and delete class members. (pure virtual)
			* Stop this object's thread execution (if any) immediately.
			*/
			virtual void release(void) override;


		private:
			/** \brief Stock current context. */
			static void set_current_context(eve::gl::SubContext * p_pContext);
			/** \brief Get current context. */
			static const eve::gl::SubContext * get_current_context(void);


		public:
			/** 
			* \brief Make context current (aka active). 
			* \note Only 1 context can be current at a time.
			*/
			bool makeCurrent(void);
			/** \brief Release context activation. */
			bool doneCurrent(void);
			/** \brief Terminate OpenGL operations and swap buffers if multiple buffers are in use.	*/
			void swapBuffers(void);

		}; // class SubContext

	} // namespace gl

} // namespace eve

//=================================================================================================
inline const eve::gl::SubContext * eve::gl::SubContext::get_current_context(void) { return m_p_context_current; }

#endif // __EVE_OPENGL_CONTEXT_H__
