#include "opx.h"
#include <stdlib.h>
#include <float.h>
#include <SDL/SDL.h>
#include <SDL_opengl.h>

//SDL variables
SDL_Surface *screen;
SDL_Rect pixel;
  
//OPX variables
void *stars_collection;
int planets=1;

//vision ray
struct opx_vector_float vision;

struct planet sphere;

void opx_add_star(float x,float y,float z,float radius,float r,float g,float b,int number)
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
  *(float*)ptr=r;
    ptr=ptr+sizeof(long);
  *(float*)ptr=g;
    ptr=ptr+sizeof(long);
  *(float*)ptr=b;
}

void opx_init(int resx, int resy, int colordepth)
{
  //activating SDL
    printf("OPX: Init SDL...");
  SDL_Init(SDL_INIT_VIDEO);
    printf("done\n");

  //activating OpenGL
    printf("OPX: activating OpenGL doublebuffer...");
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    printf("done\n");

  //set screen mode
    printf("OPX: setting screen video mode...");
  screen=SDL_SetVideoMode(resx,resy,colordepth, SDL_OPENGL);
    printf("done\n");

  //creating memory space for the stars
  stars_collection=malloc(8*sizeof(long)*max_stars);

  //OpenGL projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,resx,resy,0,-1,10);
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
  sphere.color_r=200;
  sphere.color_g=200;
  sphere.color_b=250;

  //runtime variables
  int x=0; //pixels x
  int y=0; //pixels y
  int y_update=1; //check variable if y was updated
  int i=0; //object counter
  int i_stars=0; //star counter
  float r,g,b; //last colors
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
		r=*(float*)(stars_collection+i_stars*(8*sizeof(long))+5*sizeof(long));
		g=*(float*)(stars_collection+i_stars*(8*sizeof(long))+6*sizeof(long));
		b=*(float*)(stars_collection+i_stars*(8*sizeof(long))+7*sizeof(long));
		opx_pixel(x,y,r,g,b);
		l_min=l;
	      }
	  }
	  l=opx_intersect_vector_planet(player,vision,sphere);
	  if(l<l_min && 0<l)
	    {
	      l=l_min;
	      r=(float)sphere.color_r/256;
	      g=(float)sphere.color_g/256;
	      b=(float)sphere.color_b/256;
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
	      SDL_GL_SwapBuffers();
	      if(screenshot==1)
		{
		  SDL_SaveBMP(screen,"screenshots/screenshot.bmp");
		}
	      //CLS
	      opx_cls();
	      break;
	    }
    }
}


void opx_pixel(int x,int y,float r,float g,float b)
{
  glBegin(GL_TRIANGLE_STRIP);
    glColor3f(r,g,b);
    glVertex3f(x-1,y-1,0);
    glVertex3f(x+1,y-1,0);
    glVertex3f(x+1,y+1,0);
    glVertex3f(x-1,y+1,0);
  glEnd();
}

void opx_cls()
{
  glClearColor(0,0,0,0);//clear the screen with black
  glClear(GL_COLOR_BUFFER_BIT);
}
