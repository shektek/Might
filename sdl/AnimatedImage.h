#ifndef ANIMATEDIMAGE_H
#define ANIMATEDIMAGE_H

#include <vector>
#include <map>
#include <SDL2/SDL_image.h>

//for each image in the image set, iterate through whatever frames pertain to it, then continue to the next image
class AnimatedImage
{
	private:
		int	_currentSurfaceIndex;
		int	_currentFrameSubIndex;
		//this looks retarded and sort of is, it may be that a small class was a better option
		std::vector<std::pair<SDL_Surface*, std::vector<SDL_Rect>>> _imageFrames;

	public:
		AnimatedImage();
		AnimatedImage(const AnimatedImage &other);
		~AnimatedImage();

		//Get a frame rectangle and the surface it relates to
		void	GetCurrentFrame(SDL_Surface *&srf, SDL_Rect *frm);
		void	GetFirstFrame(SDL_Surface *&srf, SDL_Rect *frm);
		void	GetLastFrame(SDL_Surface *&srf, SDL_Rect *frm);

		//Iterate forward or backwawrd through the surface/frame collections
		void 	Continue();
		void	Rewind();
		//Check which frame we're at
		bool	IsFirst();
		bool	IsLast();
		void	GetCurrentIndex(int &srfInd, int &frmInd);

		//Add another image surface
		void	AddSurface(SDL_Surface *srf);
		//Add a frame to the last image surface
		void	AddFrame(SDL_Rect frm);
		//Add a frame for the given surface
		void	AddFrame(SDL_Surface *srf, SDL_Rect frm);
};

#endif
