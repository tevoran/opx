#include <stdlib.h>
#include <SDL/SDL.h>
#include "include/definitions.h"
#include "opx/opx.h"

void main()
{
  //Setting up OPX
  init_opx();
	//Setting up SDL
		printf("Setting up SDL...");
	SDL_Surface *screen;
	screen=SDL_SetVideoMode(resx,resy,32, SDL_HWSURFACE|SDL_DOUBLEBUF);
	
	//pixel rect
	 SDL_Rect pixel;
 		pixel.x = 0;
		pixel.y = 0;
 		pixel.h = 1;
 		pixel.w = 1;

	//struct vektor
	struct vektor
	{
		float x;
		float y;
		float z;
	};
	//Betrachter
	struct vektor p;
		p.x=0;
		p.y=0;
		p.z=0;
	//Kugel 1
	struct vektor kugel;
		kugel.x=0;
		kugel.y=0;
		kugel.z=4;
		//radius
		int r=1;
	//Schnittpunkt
	struct vektor s;
		s.x=0;
		s.y=0;
		s.z=0;

	//Sichtvektor
	struct vektor see;
	        see.y=1;

	//Rendering
		int x=0;
		int y=0;
		float lambda=0;
		float a=0;
		//cls
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		while(1)
		{
		//rendern
		see.x=4*x/resx-2;
		see.y=3*y/resy-1.5;

			//Schnittpunkt bestimmen mit Sehstrahl bestimmen
			lambda=(see.x*(kugel.x-p.x)+see.y*(kugel.y-p.y)+see.z*(kugel.z-p.z))/(see.x*see.x+see.y*see.y+see.z*see.z);
			s.x=p.x+lambda*see.x;
			s.y=p.y+lambda*see.y;
			s.z=p.z+lambda*see.z;
			//entfernung zur kugel a*a
			a=(s.x-kugel.x)*(s.x-kugel.x)+(s.y-kugel.y)*(s.y-kugel.y)+(s.z-kugel.z)*(s.z-kugel.z);
			printf("a:%f\n",a);
			//zeichnen
			if(a<(r*r))
			{
				pixel.x=x;
				pixel.y=y;
				SDL_FillRect(screen, &pixel, SDL_MapRGB(screen->format, 10, 70, 150));
			}
			//sehstrahl festlegen
			x++;
			if(x==resx)
			{
				x=0;
				y++;
				if(y==resy)
				{
					y=0;
				SDL_Flip(screen);
				SDL_FillRect(screen, &pixel, SDL_MapRGB(screen->format, 10, 70, 150));
				}
			}
		}
}
