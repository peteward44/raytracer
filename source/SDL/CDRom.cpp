
#include "CDRom.h"

using namespace SDL;


CDTrack::CDTrack(SDL_CD* cd, SDL_CDtrack* track)
 : cd(cd), track(track)
{
}


void CDTrack::Play()
{
	Play(0, 0);
}


void CDTrack::Play(int startFrame, int numFrames)
{
	if (SDL_CDPlayTracks(cd, track->id, startFrame, 1, numFrames) == -1)
		throw CDRomException("Could not play track");
}


void CDTrack::PlaySeconds(float offset, float length)
{
	if (SDL_CDPlayTracks(cd, track->id, (int)(offset / (float)CD_FPS), 1, (int)(length / (float)CD_FPS)) == -1)
		throw CDRomException("Could not play track");
}


//////////////////


CDRom::CDRom(SDL_CD* cd)
 : cd(cd)
{
	for (int i=0; i<cd->numtracks; ++i)
	{
		tracks.push_back( CDTrack(cd, &cd->track[i]) );
	}
}


CDRom::~CDRom()
{
	SDL_CDClose(cd);
}


CDRomPtr CDRom::Open(int drive)
{
	SDL_CD* cd = SDL_CDOpen(drive);
	if (cd == 0)
		throw CDRomException("CD drive busy or unavailable");
	return CDRomPtr( new CDRom(cd) );
}


std::string CDRom::GetName(int drive)
{
	return std::string( SDL_CDName(drive) );
}


void CDRom::Eject()
{
	if (SDL_CDEject(cd) == -1)
		throw CDRomException("Could not eject cdrom");
}


void CDRom::Play(int start, int length)
{
	if (SDL_CDPlay(cd, start, length) == -1)
		throw CDRomException("Could not play CD");
}


void CDRom::Stop()
{
	if (SDL_CDStop(cd) == -1)
		throw CDRomException("Could not stop CD");
}


void CDRom::Pause()
{
	if (SDL_CDPause(cd) == -1)
		throw CDRomException("Could not pause CD");
}


void CDRom::Resume()
{
	if (SDL_CDResume(cd) == -1)
		throw CDRomException("Could not resume CD");
}

