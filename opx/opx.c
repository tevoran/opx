#include "opx.h"
#include <stdlib.h>
#include <float.h>
#include <SDL/SDL.h>

//SDL variables
SDL_Surface *screen;
SDL_Rect pixel;
  
//OPX variables
void *stars_collection;
int planets=1;

//vision ray
struct opx_vector_float vision;

struct planet sphere;

void opx_add_star(float x,float y,float z,float radius,int r,int g,int b,int number)
{
  void *ptr;
  ptr=(stars_collection+(number*8*sizeof(long)));
  *(long*)ptr=1;
    ptr=ptr+sizeof(long);
  *(float*)ptr=x;
    ptr=ptr+sizeof(long);
  *(float*)ptr=y;
    ptr=ptr+sizeof(long);
  *(float*)ptr=z;
    ptr=ptr+sizeof(long);
  *(float*)ptr=radius;
    ptr=ptr+sizeof(long);
  *(int*)ptr=r;
    ptr=ptr+sizeof(long);
  *(int*)ptr=g;
    ptr=ptr+sizeof(long);
  *(int*)ptr=b;
}

void opx_init(int resx, int resy, int colordepth, long seed)
{
  //Set screen
  screen=SDL_SetVideoMode(resx,resy,colordepth, SDL_HWSURFACE|SDL_DOUBLEBUF);
    printf("OPX: screen video mode set\n");

  //creating memory space for the stars
  stars_collection=malloc(8*sizeof(long)*max_stars);

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
  int i_stars=0; //star counter
  int r,g,b; //last colors
  float l=0; //actual object
  float l_min; //nearest object
  float anglexz_now,anglexy_now; //latest angles of the vision ray
  float anglexy_cos; //save value to save CPU time

  while(1)
    {
      //setting vision ray
      //updating y of vision ray
      if(y_update==1)
	{
	  anglexy_now=(anglexy+(pi/4))-((pi/2)*(float)((float)y/(float)resy));
	  anglexy_cos=opx_cos(anglexy_now);
	  vision.y=opx_sin(anglexy_now);
	  y_update=0;
	}

      //updating x of vision ray
      anglexz_now=(anglexz+(pi/4))-((pi/2)*(float)((float)x/(float)resx));
        vision.x=anglexy_cos*opx_cos(anglexz_now);
	vision.z=anglexy_cos*opx_sin(anglexz_now);

      //checking for intersection
	//checking for stars
	r=0;
	g=0;
	b=0;
	l_min=FLT_MAX;
        for(i_stars=0;i_stars<max_stars;i_stars++)
	  {
	    if(1!=*(long*)(stars_collection+i_stars*(8*sizeof(long))))
	      {
		break;
	      }
	    l=opx_intersect_vector_star(player,vision,(stars_collection+i_stars*(8*sizeof(long))));
	    if(l<l_min && 0<l)
	      {
		r=*(int*)(stars_collection+i_stars*(8*sizeof(long))+5*sizeof(long));
		g=*(int*)(stars_collection+i_stars*(8*sizeof(long))+6*sizeof(long));
		b=*(int*)(stars_collection+i_stars*(8*sizeof(long))+7*sizeof(long));
		opx_pixel(x,y,r,g,b);
		l_min=l;
	      }
	  }
	  l=opx_intersect_vector_planet(player,vision,sphere);
	  if(l<l_min && 0<l)
	    {
	      l=l_min;
	      r=sphere.color_r;
	      g=sphere.color_g;
	      b=sphere.color_b;
	      opx_pixel(x,y,r,g,b);
	    }
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
		  SDL_SaveBMP(screen,"screenshots/screenshot.bmp");
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
