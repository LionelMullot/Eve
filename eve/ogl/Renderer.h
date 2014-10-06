
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
#ifndef __EVE_OPENGL_RENDER_H__
#define __EVE_OPENGL_RENDER_H__

#ifndef __EVE_CORE_RENDERER_H__
#include "eve/core/Renderer.h"
#endif


namespace eve { namespace ogl { class Object; } }
namespace eve { namespace ogl { class SubContext; } }

namespace eve { namespace thr { class SpinLock;  } }

namespace eve
{
	namespace ogl
	{
		/**
		* \class eve::sys::Renderer
		*
		* \brief OpenGL render engine.
		*
		* \note extends eve::core::Renderer
		*/
		class Renderer
			: public eve::core::Renderer
		{

			friend class eve::mem::Pointer;
			friend class eve::ogl::Object;

			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

		protected:
			eve::ogl::SubContext *						m_pContext;				//!< OpenGL context.
				
			std::deque<eve::ogl::Object *> *            m_pQueueInit;			//<! OpenGL objects initialization queue.
			std::deque<eve::ogl::Object *> *            m_pQueueUpdate;			//<! OpenGL objects update queue.
			std::deque<eve::ogl::Object *> *            m_pQueueRelease;		//<! OpenGL objects release queue.
			eve::thr::SpinLock *						m_pQueueFence;			//!< Init/Update/Release queues fence.


			//////////////////////////////////////
			//				METHOD				//
			//////////////////////////////////////

			EVE_DISABLE_COPY(Renderer);
			EVE_PROTECT_DESTRUCTOR(Renderer);

		protected:
			/** \class constructor. */
			Renderer(void);

			
		protected:
			/** \brief Alloc and init class members. (pure virtual) */
			virtual void init(void) override;
			/** \brief Release and delete class members. (pure virtual) */
			virtual void release(void) override;


		public:
			/** \brief Register renderer to window handle. (pure virtual) */
			virtual void registerToHandle(void * p_handle) override;


		protected:
			/** \brief Put target object in initialization queue. */
			void putInQueueInit(eve::ogl::Object * p_pObject);
			/** \brief Put target object in update queue. */
			void putInQueueUpdate(eve::ogl::Object * p_pObject);
			/** \brief Put target object in release queue. */
			void putInQueueRelease(eve::ogl::Object * p_pObject);

			/** \brief Iterates queues and call associated OpenGL commands. */
			void processQueues(void);
			/** \brief Clear queues. */
			void clearQueues(void);


		public:
			/** \brief Before display callback. (pure virtual) */
			virtual void cb_beforeDisplay(void) override;
			/** \brief After display callback. (pure virtual) */
			virtual void cb_afterDisplay(void) override;

			/** \brief Draw on screen callback. (pure virtual) */
			virtual void cb_display(void) override;

		}; // class Renderer

	} // namespace core

} // namespace eve

#endif // __EVE_OPENGL_RENDER_H__