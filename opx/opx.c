#include "opx.h"
#include <SDL/SDL.h>

//SDL variables
SDL_Surface *screen;
SDL_Rect pixel;
  
//OPX variables
int planets=1;

  //vision ray
  struct opx_vector_float vision;

struct planet sphere;
struct star sun;

void opx_init(int resx, int resy, int colordepth, int seed)
{
  //Set screen
  screen=SDL_SetVideoMode(resx,resy,colordepth, SDL_HWSURFACE|SDL_DOUBLEBUF);
    printf("OPX: screen video mode set\n");

}

//should be resx/resy=1
//all angles are in radian
void opx_render(struct opx_vector_float player,float anglexy,float anglexz,int resx,int resy,int screenshot)
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

  //content
  sun.x=0;
  sun.y=0;
  sun.z=15000;
  sun.r=200;
  sun.color_r=255;
  sun.color_g=205;
  sun.color_b=20;

  sphere.x=0;
  sphere.y=0;
  sphere.z=0;
  sphere.r=0.63;
  sphere.color_r=50;
  sphere.color_g=50;
  sphere.color_b=200;

  //runtime variables
  int x=0; //pixels x
  int y=0; //pixels y
  int y_update=1; //check variable if y was updated
  int i=0; //object counter
  int r,g,b; //last colors
  float l=0; //actual object
  float l_min=0; //nearest object
  float anglexz_now,anglexy_now; //latest angles of the vision ray
  float anglexy_cos; //save value to save CPU time

  while(1)
    {
      //setting vision ray
      //updating y of vision ray
      if(y_update==1)
	{
	  anglexy_now=anglexy+pi/4-((pi/2)*(float)((float)y/(float)resy));
	  anglexy_cos=opx_cos(anglexy_now);
	  vision.y=opx_sin(anglexy_now);
	  y_update=0;
	}

      //updating x of vision ray
      anglexz_now=anglexz+pi/4-((pi/2)*(float)((float)x/(float)resx));
        vision.x=anglexy_cos*opx_cos(anglexz_now);
	vision.z=anglexy_cos*opx_sin(anglexz_now);

      //checking for intersection
      l_min=opx_intersect_vector_star(player,vision,sun);
      if(0<l_min)
      	{
	  r=sun.color_r;
	  g=sun.color_g;
	  b=sun.color_b;
	}
      else
	{
	  r=0;
	  g=0;
	  b=0;
	}
      i=0;
      for(i;i<planets;i++)
	{
	  l=opx_intersect_vector_planet(player,vision,sphere);
	  if((l_min==0 && l>0) || (l<l_min && l>0))
	    {
	      l=l_min;
	      r=sphere.color_r;
	      g=sphere.color_g;
	      b=sphere.color_b;
	    }
	  
	}
      opx_pixel(x,y,r,g,b);
      //continue with next pixel
	  x++;
	  if(x==resx)
	    {
	      x=0;
	      y++;
	      y_update=1; //changes update value so that y value of the vision gets updated
	    }
	  if(y==resy)
	    {
	      y=0;
	      SDL_Flip(screen);
	      if(screenshot==1)
		{
		  SDL_SaveBMP(screen,"screenshots/screen13-5-14.bmp");
		  }
	      //CLS
	      SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
	      break;
	    }
    }
}


void opx_pixel(int x,int y,int r,int g,int b)
{
  pixel.x=x;
  pixel.y=y;
  pixel.w=1;
  pixel.h=1;
  SDL_FillRect(screen,&pixel,SDL_MapRGB(screen->format,r,g,b));
}
