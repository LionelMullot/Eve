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
#ifndef __EVE_OPENGL_PARTICULE_PARTICULE_MANAGER_H__
#define __EVE_OPENGL_PARTICULE_PARTICULE_MANAGER_H__

#ifndef __EVE_CORE_INCLUDES_H__
#include "eve/core/Includes.h"
#endif

#ifndef __EVE_OPENGL_CORE_EXTERNAL_H__
#include "eve/ogl/core/External.h"
#endif

#ifndef __EVE_OPENGL_CORE_OBJECT_H__
#include "eve/ogl/core/Object.h"
#endif

#ifndef __EVE_MATH_CORE_TVECTOR_H__
#include "eve/math/core/TVector.h"
#endif

namespace eve
{
	namespace ogl
	{

		struct Particle
		{
			eve::math::TVec4<float>	m_currPosition;
			eve::math::TVec4<float>	m_prevPosition;
		};

		class ParticleManager
			: public eve::ogl::Object
		{
		private:
			std::map<std::string, GLuint> 		m_bufferData;
			int m_numParticles, m_iniRadius;
			Particle* m_particles;

			void setParticles(struct Particle* particles, int numParticles, int iniRadius);

		public:


			/** \brief Class constructor. */
			ParticleManager(void);
			/** \brief Class destructor. */
			virtual ~ParticleManager(void);

			/** \brief Copy constructor. */
			ParticleManager(const ParticleManager & p_other);
			/** \brief Assignment operator. */
			const ParticleManager & operator = (const ParticleManager & p_other);

			ParticleManager(ParticleManager&& other);

			ParticleManager& operator=(ParticleManager&& other);

		protected:
			/**
			* \brief Get attributes from eve::ogl::Format. (pure virtual)
			* Object attributes MUST be retrieved before init() call.
			*/
			virtual void setAttributes(eve::ogl::Format * p_format);

		public:
			/** \brief Alloc and init non OpenGL class members. (pure virtual) */
			virtual void init(void){};
			/** \brief Release and delete non OpenGL class members. (pure virtual) */
			virtual void release(void);


		protected:
			/** \brief Init OpenGL components. */
			virtual void oglInit(void);
			/** \brief Update OpenGL components. (only FBO size can be updated here) */
			virtual void oglUpdate(void){};
			/** \brief Deallocate and release OpenGL components. */
			virtual void oglRelease(void);



		public:

			void loadParticleBuffer(int numParticles, int iniRadius, eve::ogl::Renderer * p_pRenderer);

			void loadUintUniform(GLuint shaderProgramID, std::string name, GLuint value);
			void loadFloatUniform(GLuint shaderProgramID, std::string name, GLfloat value);
			void loadVec4Uniform(GLuint shaderProgramID, std::string name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
			void loadMatrix4Uniform(GLuint shaderProgramID, std::string name, const GLfloat* value);

			///////////////////////////////////////////////////////////////////////////////////////////////
			//		GET / SET
			///////////////////////////////////////////////////////////////////////////////////////////////

		public:
			/** \brief Get OpenGL shader unique id. (pure virtual) */
			virtual const GLuint getId(void) const override;

		};

	} // namespace ogl

} // namespace eve

#endif