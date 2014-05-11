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

//should be resx/resy=1
//all angles are in radian
void opx_render(struct opx_vector_float player,float anglexy,float anglexz,int resx,int resy)
{
  //making angles<2pi
  while(anglexz>=2*pi)
    {
      anglexz=anglexz-2*pi;
    }
  while(anglexy>=2*pi)
    {
      anglexy=anglexy-2*pi;
    }

  sphere.x=0;
  sphere.y=0;
  sphere.z=10;
  sphere.r=1;
  pixel.x=0;
  pixel.y=0;
  pixel.w=1;
  pixel.h=1;
  //runtime variables
  int x=0;
  int y=0;
  float a,b,c,d;//variables for the abc formula
  float x1;//the result of the abc formula

  //intersection variables
  c=(player.x-sphere.x)*(player.x-sphere.x)+(player.y-sphere.y)*(player.y-sphere.y)+(player.z-sphere.z)*(player.z-sphere.z)-(sphere.r*sphere.r);
  while(1)
    {
      //setting vision ray
      vision.x=opx_cos(anglexz+pi/4-((pi/2)*(float)((float)x/(float)resx)));
      vision.y=opx_sin(anglexy+pi/4-((pi/2)*(float)((float)y/(float)resy)));
      vision.z=opx_sin(anglexz+pi/4-((pi/2)*(float)((float)x/(float)resx)));

      //checking for intersection
      a=1+vision.y*vision.y;//vision.x*vision.x+vision.y*vision.y+vision.z*vision.z;
      b=2*((player.x-sphere.x)*vision.x+(player.y-sphere.y)*vision.y+(player.z-sphere.z)*vision.z);
      d=b*b-4*a*c; //discriminant

      if(d>=0)
	{
	  x1=(-b-opx_sqrt(d))/(2*a);
	  if(x1>0)
	    {
	      //draw pixel
	      pixel.x=x;
	      pixel.y=y;
	      SDL_FillRect(screen,&pixel,SDL_MapRGB(screen->format,0,200,30));
	    }
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
	      //SDL_SaveBMP(screen,"screenshots/screen11-5-14.bmp");
	      //CLS
	      SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
	      break;
	    }
    }
}
