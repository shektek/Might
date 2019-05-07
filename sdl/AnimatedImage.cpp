#include "AnimatedImage.h"

AnimatedImage::AnimatedImage()
{
	_currentSurfaceIndex = 0;
	_currentFrameSubIndex = 0;
}

AnimatedImage::AnimatedImage(const AnimatedImage &other)
{
	_currentSurfaceIndex = other._currentSurfaceIndex;
	_currentFrameSubIndex = other._currentFrameSubIndex;
	_imageFrames = other._imageFrames;
}

AnimatedImage::~AnimatedImage()
{
	_currentSurfaceIndex = -1;
	_currentFrameSubIndex = -1;
	_imageFrames.clear();
}

void AnimatedImage::GetCurrentFrame(SDL_Surface *&srf, SDL_Rect *frm)
{
	if(_imageFrames.size() > 0)
	{
		//there is always a surface, but not always a frame
		srf = _imageFrames[_currentSurfaceIndex].first;

		if(_imageFrames[_currentSurfaceIndex].second.size() > 0
		    && (int)_imageFrames[_currentSurfaceIndex].second.size() > _currentFrameSubIndex
		    && _currentFrameSubIndex >= 0)
			frm = &_imageFrames[_currentSurfaceIndex].second[_currentFrameSubIndex];
		else
			frm = nullptr;
	}
	else
	{
		srf = nullptr;
		frm = nullptr;
	}
}

void AnimatedImage::GetFirstFrame(SDL_Surface *&srf, SDL_Rect *frm)
{
	if(_imageFrames.size() > 0)
	{
		srf = _imageFrames.front().first;

		if(_imageFrames.front().second.size() > 0)
			frm = &_imageFrames.front().second.front();
		else
			frm = nullptr;
	}
	else
	{
		srf = nullptr;
		frm = nullptr;
	}
}

void AnimatedImage::GetLastFrame(SDL_Surface *&srf, SDL_Rect *frm)
{
	if(_imageFrames.size() > 0)
	{
		srf = _imageFrames.back().first;
		if(_imageFrames.back().second.size() > 0)
			frm = &_imageFrames.back().second.back();
		else
			frm = nullptr;
	}
	else
	{
		srf = nullptr;
		frm = nullptr;
	}
}

void AnimatedImage::Continue()
{
	//iterate the subframe if possible, otherwise iterate the surface and reset the frame index
	if(_currentFrameSubIndex+1 < (int)_imageFrames[_currentSurfaceIndex].second.size())
	{
		_currentFrameSubIndex++;
	}
	else if(_currentFrameSubIndex+1 >= (int)_imageFrames[_currentSurfaceIndex].second.size())
	{
		_currentFrameSubIndex = 0;
		_currentSurfaceIndex++;
	}

	//if the current surface is beyond bounds, reset all counts to the beginning
	if(_currentSurfaceIndex == (int)_imageFrames.size())
	{
		_currentFrameSubIndex = 0;
		_currentSurfaceIndex = 0;
	}
}

void AnimatedImage::Rewind()
{
	if(_currentFrameSubIndex-1 > 0)
	{
		_currentFrameSubIndex--;
	}
	else if(_currentFrameSubIndex - 1 <= 0)
	{
		_currentSurfaceIndex--;
		_currentFrameSubIndex = -1;
	}

	if(_currentFrameSubIndex == -1 && _currentSurfaceIndex >= 0)
	{
		_currentFrameSubIndex = _imageFrames[_currentSurfaceIndex].second.size()-1;
		if(_currentFrameSubIndex < 0)
			_currentFrameSubIndex = 0;
	}
	else if(_currentSurfaceIndex < 0)
	{
		_currentSurfaceIndex = _imageFrames.size()-1;

		_currentFrameSubIndex = _imageFrames[_currentSurfaceIndex].second.size()-1;
		if(_currentFrameSubIndex < 0)
			_currentFrameSubIndex = 0;
	}
}

bool AnimatedImage::IsFirst()
{
	return (_currentSurfaceIndex == 0 && _currentFrameSubIndex == 0);
}

bool AnimatedImage::IsLast()
{
	return (_currentSurfaceIndex == (int)_imageFrames.size()-1
		&& _currentFrameSubIndex == (int)_imageFrames.back().second.size()-1);
}

void AnimatedImage::GetCurrentIndex(int &srfInd, int &frmInd)
{
	srfInd = _currentSurfaceIndex;
	frmInd = _currentFrameSubIndex;
}

void AnimatedImage::AddSurface(SDL_Surface *srf)
{
	_imageFrames.push_back(std::pair<SDL_Surface*,std::vector<SDL_Rect>>(srf, std::vector<SDL_Rect>()));
}

void AnimatedImage::AddFrame(SDL_Rect frm)
{
	if(_imageFrames.size() > 0)
		_imageFrames.back().second.push_back(frm);
}

void AnimatedImage::AddFrame(SDL_Surface *srf, SDL_Rect frm)
{
	bool surfaceFound = false;

	for(int i = 0; i < (int)_imageFrames.size(); i++)
	{
		if(_imageFrames[i].first == srf)
		{
			surfaceFound = true;
			_imageFrames[i].second.push_back(frm);
			break;
		}
	}

	if(!surfaceFound)
	{
		AddSurface(srf);
		AddFrame(frm);
	}
}
