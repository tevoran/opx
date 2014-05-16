#include <stdlib.h>
#include <SDL/SDL.h>
#include "include/definitions.h"
#include "opx/opx.h"

void main()
{
  //Setting up OPX
  long seed=123456789;
  opx_init(resolution_x,resolution_y,32,0);

  //creating content
    //creating stars
    int n=opx_random(seed)%20;
    long new_seed=opx_random(seed);
    float x,y,z,radius;
    int r,g,b;
    for(n;n>=0;n--)
      {
	x=opx_random(new_seed)%200-100;
	  new_seed=opx_random(new_seed);
	y=opx_random(new_seed)%250-125;
	  new_seed=opx_random(new_seed);
	z=opx_random(new_seed)%3000;
	  new_seed=opx_random(new_seed);
	radius=opx_random(new_seed)%250;
	  new_seed=opx_random(new_seed);
	r=opx_random(new_seed)%256;
	  new_seed=opx_random(new_seed);
	g=opx_random(new_seed)%256;
	  new_seed=opx_random(new_seed);
	b=opx_random(new_seed)%256;
	  new_seed=opx_random(new_seed);
	opx_add_star(x,y,z,radius,r,g,b,n);
      }
  

  //creating player
  struct opx_vector_float player;
    player.x=0;
    player.y=1;
    player.z=-1;
    float anglexz=pi/2;
    float anglexy=0;

    int ltimer=SDL_GetTicks();
    int timer=0;

   while(1)
      {
	timer=SDL_GetTicks();
          printf("Time per frame: %i ms\n",timer-ltimer);
	  float FPS=(float)(float)1000/(float)(timer-ltimer);
	  printf("FPS: %f\n",FPS);
	ltimer=timer;
        opx_render(player,anglexy,anglexz,resolution_x,resolution_y,0);
	//player.z=player.z+0.001;
	printf("z: %f\n",player.z);
	//break;
      }

}
