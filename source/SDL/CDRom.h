
#ifndef CDROM_H
#define CDROM_H

#include "SDLpp.h"
#include <vector>


namespace SDL
{
	class CDRom;
	typedef boost::shared_ptr<CDRom> CDRomPtr;


	class CDTrack
	{
		friend class CDRom;
	private:
		SDL_CD* cd;
		SDL_CDtrack* track;
		
		CDTrack(SDL_CD* cd, SDL_CDtrack* track);
		
	public:
	
		inline int GetId() const
		{ return track->id; }
	
		inline bool IsData() const
		{ return track->type == SDL_DATA_TRACK; }
		
		inline bool IsAudio() const
		{ return track->type == SDL_AUDIO_TRACK; }
		
		inline int GetLength() const
		{ return track->length; }
		
		inline int GetOffset() const
		{ return track->offset; }
		
		inline float GetLengthInSeconds() const
		{ return (float)track->length / (float)CD_FPS; }
		
		
		void Play();
		void Play(int startFrame, int numFrames);
		void PlaySeconds(float offset, float length);
	};


	class CDRom
	{
	private:
		SDL_CD* cd;
		static int numDrives;
		std::vector< CDTrack > tracks;
		
		CDRom();
		CDRom(const CDRom& cdrom);
		CDRom& operator = (const CDRom& cdrom);
		
		CDRom(SDL_CD* cd);

	public:
		~CDRom();
	
		static CDRomPtr Open(int drive);
		static std::string GetName(int drive);
		
		inline static int GetNumDrives()
		{ return numDrives; }
		
		inline std::string GetName() const
		{ return std::string( SDL_CDName(cd->id) ); }
		
		void Eject();
		
		void Play(int start, int length);
		void Stop();
		void Pause();
		void Resume();
		
		
		inline bool IsEmpty() const
		{ return SDL_CDStatus(cd) == CD_TRAYEMPTY; }
		
		inline bool IsStopped() const
		{ return SDL_CDStatus(cd) == CD_STOPPED; }
		
		inline bool IsPaused() const
		{ return SDL_CDStatus(cd) == CD_PAUSED; }
		
		inline bool IsPlaying() const
		{ return SDL_CDStatus(cd) == CD_PLAYING; }
		
		
		inline int GetNumTracks() const
		{ return cd->numtracks; }
		
		inline int GetCurrentTrack() const
		{ return cd->cur_track; }
		
		inline int GetCurrentFrame() const
		{ return cd->cur_frame; }
		
		
		inline CDTrack& GetTrack(int id)
		{
			assert(id >= 0 && id < cd->numtracks);
			return tracks[id];
		}
	};
}


#endif

