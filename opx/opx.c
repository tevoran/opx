#include "opx.h"
#include <stdlib.h>
#include <float.h>
#include <SDL/SDL.h>
#include <SDL_opengl.h>

//SDL variables
SDL_Surface *screen;
  
//OPX variables
void *stars_collection; //should be just read
void *render_bubble; //should be just read
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
    printf("OPX: init SDL...");
  SDL_Init(SDL_INIT_VIDEO);
    printf("done\n");

  //activating OpenGL
    printf("OPX: activating OpenGL doublebuffer...");
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    printf("done\n");

  //activating OpenCL
    printf("OPX: init OpenCL...");
  opx_init_opencl();
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

  //Creating render bubble
    printf("OPX: creating render bubble...");
  render_bubble=malloc(max_stars*sizeof(int));
  *(int*)render_bubble=max_stars+1;//mark the end of the bubble
    printf("done\n");
}

//should be resx/resy=1
//all angles are in radian
void opx_render(struct opx_vector_float player,float anglexy,float anglexz,int resx,int resy)
{
  //content
  sphere.x=0;
  sphere.y=0;
  sphere.z=0;
  sphere.r=0.63;
  sphere.color_r=200;
  sphere.color_g=200;
  sphere.color_b=250;

  //runtime variables
  int star_data_length=8*sizeof(long);
  int x=0; //pixels x
  int y=0; //pixels y
  int y_update=1; //check variable if y was updated
  int i=0; //object counter
  int i_stars=0; //star counter
  int bubble_star_number=0;
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
	//if in render bubble -> raytracing
	//else project one dot at its place
	r=0;
	g=0;
	b=0;
	l_min=FLT_MAX;
        for(i_stars=0;i_stars<max_stars;i_stars++)
	  {
	    bubble_star_number=*(int*)(render_bubble+i_stars*sizeof(int));
	    if(max_stars<=bubble_star_number)//if there is no next star then end the loop
	      {
		break;
	      }
	    l=opx_intersect_vector_star(player,vision,stars_collection+(bubble_star_number*star_data_length));
	    if(l<l_min && 0<l)//if the current star is nearer then get the color of it
	      {
		r=*(float*)(stars_collection+(bubble_star_number*star_data_length)+(5*sizeof(long)));
		g=*(float*)(stars_collection+(bubble_star_number*star_data_length)+(6*sizeof(long)));
		b=*(float*)(stars_collection+(bubble_star_number*star_data_length)+(7*sizeof(long)));
		opx_pixel(x,y,r,g,b);
		l_min=l;
	      }
	  }
	/*l=opx_intersect_vector_planet(player,vision,sphere);
	  if(l<l_min && 0<l)
	    {
	      l=l_min;
	      r=(float)sphere.color_r/256;
	      g=(float)sphere.color_g/256;
	      b=(float)sphere.color_b/256;
	      opx_pixel(x,y,r,g,b);
	      }*/
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
	      opx_cls();
	      break;
	    }
    }
}

//a spherical render bubble
//each star inside is raytraced others are just directly projected
void opx_update_bubble(struct opx_vector_float player)
{
  int i;
  int count_bubble=0;
  int star_data_length=8*sizeof(long);
  //spherical equation is used
  float r=(float)render_bubble_radius*(float)render_bubble_radius;
  float x;
  float y;
  float z;
  //pointer to render_bubble structure
  void *ptr;
  ptr=render_bubble;
  for(i=0;i<max_stars;i++)
    {
      if(1!=*(long*)(stars_collection+(i*star_data_length)))//if there is no next star then end the loop
       {
	 break;
       }
      x=(*(float*)(stars_collection+(i*star_data_length)+(1*sizeof(long))))-player.x;
      x=x*x;
      y=(*(float*)(stars_collection+(i*star_data_length)+(2*sizeof(long))))-player.y;
      y=y*y;
      z=(*(float*)(stars_collection+(i*star_data_length)+(3*sizeof(long))))-player.z;
      z=z*z;
      if((x+y+z)<r)
	{
	  count_bubble=count_bubble+1;
	  *(int*)ptr=i;
	  ptr=ptr+sizeof(int);
	}
    }
  printf("stars in bubble: %i of %i\n",count_bubble,i);
  *(int*)ptr=max_stars+1;
}
