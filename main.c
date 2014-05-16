#include <stdlib.h>
#include <SDL/SDL.h>
#include "include/definitions.h"
#include "opx/opx.h"

void main()
{
  //Setting up OPX
  long seed=823123574;
  opx_init(resolution_x,resolution_y,32,0);

  //creating content
  opx_add_star(0,0,15000,700,255,255,255,0);
  opx_add_star(5000,1500,15000,130,0,150,0,1);

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
        opx_render(player,anglexy,anglexz,resolution_x,resolution_y,1);
	//player.z=player.z+0.001;
	printf("z: %f\n",player.z);
	//break;
      }

}
