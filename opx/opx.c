#include "opx.h"
#include <SDL/SDL.h>

//SDL variables
SDL_Surface *screen;
SDL_Rect pixel;
  
//OPX variables
struct planet sphere;

  //vision ray
  struct opx_vector_float vision;

  //vision ray
  struct opx_vector_float vision;


void opx_init(int resx, int resy, int colordepth)
{
  //Set screen
  screen=SDL_SetVideoMode(resx,resy,colordepth, SDL_HWSURFACE|SDL_DOUBLEBUF);
    printf("OPX: screen video mode set\n");
}

//resx/resy=4/3
void opx_render(struct opx_vector_float player,int resx, int resy)
{
  sphere.x=0;
  sphere.y=0;
  sphere.z=10;
  sphere.r=1;
  vision.z=1;
  pixel.x=0;
  pixel.y=0;
  pixel.w=1;
  pixel.h=1;
  //runtime variables
  int x=0;
  int y=0;
  float a,b,c;
  while(1)
    {
      //setting vision ray
      vision.x=4*((float)x/(float)resx)-2;
      vision.y=3*((float)y/(float)resy)-1.5;

      //checking for intersection
      a=vision.x*vision.x+vision.y*vision.y+vision.z*vision.z;
      b=2*((player.x-sphere.x)*vision.x+(player.y-sphere.y)*vision.y+(player.z-sphere.z)*vision.z);
      c=(player.x-sphere.x)*(player.x-sphere.x)+(player.y-sphere.y)*(player.y-sphere.y)+(player.z-sphere.z)*(player.z-sphere.z)-(sphere.r*sphere.r);

      if(b*b-4*a*c>=0)
	{
	  //draw pixel
	  pixel.x=x;
	  pixel.y=y;
	  SDL_FillRect(screen,&pixel,SDL_MapRGB(screen->format,160,50,10));
	}
	  //continue with next pixel
	  x++;
	  if(x==resx)
	    {
	      x=0;
	      y++;
	    }
	  if(y==resy)
	    {
	      y=0;
	      SDL_Flip(screen);
	      SDL_SaveBMP(screen,"screenshots/screen9-5-14.bmp");
	      break;
	    }
    }
}
