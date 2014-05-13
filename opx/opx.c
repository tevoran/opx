#include "opx.h"
#include <SDL/SDL.h>

//SDL variables
SDL_Surface *screen;
SDL_Rect pixel;
  
//OPX variables
int objects=2;

  //vision ray
  struct opx_vector_float vision;

struct planet sphere;
struct star sun;

void opx_init(int resx, int resy, int colordepth)
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
  sun.z=100;
  sun.r=10;
  sun.color_r=230;
  sun.color_g=130;
  sun.color_b=20;

  sphere.x=0;
  sphere.y=0;
  sphere.z=10;
  sphere.r=1;
  sphere.color_r=30;
  sphere.color_g=30;
  sphere.color_b=30;

  pixel.x=0;
  pixel.y=0;
  pixel.w=1;
  pixel.h=1;

  //runtime variables
  int x=0; //pixels x
  int y=0; //pixels y
  int i=0; //object counter
  float l_min=0; //nearest object
  float anglexz_now,anglexy_now;

  while(1)
    {
      //setting vision ray
      anglexz_now=anglexz+pi/4-((pi/2)*(float)((float)x/(float)resx));
      anglexy_now=anglexy+pi/4-((pi/2)*(float)((float)y/(float)resy));

      vision.x=opx_cos(anglexy_now)*opx_cos(anglexz_now);
      vision.z=opx_cos(anglexy_now)*opx_sin(anglexz_now);
      vision.y=opx_sin(anglexy_now);

      //checking for intersection
      l_min=opx_intersect_vector_star(player,vision,sun);
      if(0<l_min)
	{
	  //draw pixel
	  pixel.x=x;
	  pixel.y=y;
	  SDL_FillRect(screen,&pixel,SDL_MapRGB(screen->format,sun.color_r,sun.color_g,sun.color_b));
	}
      if(0<opx_intersect_vector_planet(player,vision,sphere))
	{
	  //draw pixel
	  pixel.x=x;
	  pixel.y=y;
	  SDL_FillRect(screen,&pixel,SDL_MapRGB(screen->format,sphere.color_r,sphere.color_g,sphere.color_b));
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

//this function checks if there is an intersection between a vector and a planet
//it returns l times the length of "vector" if there is an intersection
//if there is no intersection the 0 is returned
float opx_intersect_vector_planet(struct opx_vector_float start,struct opx_vector_float vector,struct planet planet)
{
  //the abc-formula is used
  float a,b,c,d,l=0;
  struct opx_vector_float dx; 
    dx.x=start.x-planet.x;
    dx.y=start.y-planet.y;
    dx.z=start.z-planet.z;

  a=vector.x*vector.x+vector.y*vector.y+vector.z*vector.z;
  b=2*(dx.x*vector.x+dx.y*vector.y+dx.z*vector.z);
  c=dx.x*dx.x+dx.y*dx.y+dx.z*dx.z-planet.r*planet.r;

  //discriminant
  d=b*b-4*a*c;

  if(d>0)
    {
      l=(-b-opx_sqrt(d))/(2*a);
    }
  return l;
}


//this function checks if there is an intersection between a vector and a planet
//it returns l times the length of "vector" if there is an intersection
//if there is no intersection the 0 is returned
float opx_intersect_vector_star(struct opx_vector_float start,struct opx_vector_float vector,struct star star_)
{
  //the abc-formula is used
  float a,b,c,d,l=0;
  struct opx_vector_float dx; 
    dx.x=start.x-star_.x;
    dx.y=start.y-star_.y;
    dx.z=start.z-star_.z;

  a=vector.x*vector.x+vector.y*vector.y+vector.z*vector.z;
  b=2*(dx.x*vector.x+dx.y*vector.y+dx.z*vector.z);
  c=dx.x*dx.x+dx.y*dx.y+dx.z*dx.z-star_.r*star_.r;

  //discriminant
  d=b*b-4*a*c;

  if(d>0)
    {
      l=(-b-opx_sqrt(d))/(2*a);
    }
  return l;
}
