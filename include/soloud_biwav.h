/*
SoLoud audio engine
Copyright (c) 2013-2014 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

// BiDirectionalWav by Fincodr

#ifndef SOLOUD_BIWAV_H
#define SOLOUD_BIWAV_H

#include "soloud.h"
#include "soloud_biwav.h"

struct stb_vorbis;

namespace SoLoud
{
	class BiWav;
	class DataReader;

	class BiWavInstance : public AudioSourceInstance
	{
		BiWav *mParent;
		unsigned int mOffset;
	public:
		BiWavInstance(BiWav *aParent);
		virtual void getAudio(float *aBuffer, unsigned int aSamples);
		virtual void seek(double aSeconds, float *mScratch, unsigned int mScratchSize);
		virtual result rewind();
		virtual bool hasEnded();
		virtual result setReversed(bool aReversed);
	};

	class BiWav : public AudioSource
	{
		result loadwav(DataReader *aReader);
		result loadogg(stb_vorbis *aVorbis);
		result testAndLoadFile(DataReader *aReader);
	public:
		float *mData;
		unsigned int mSampleCount;

		BiWav();
		virtual ~BiWav();
		result load(const char *aFilename);
		result loadMem(unsigned char *aMem, unsigned int aLength);
		virtual AudioSourceInstance *createInstance();
		time getLength();
	};
};

#endif
