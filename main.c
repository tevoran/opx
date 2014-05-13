#include <stdlib.h>
#include <SDL/SDL.h>
#include "include/definitions.h"
#include "opx/opx.h"

void main()
{
  //Setting up OPX
  opx_init(resolution_x,resolution_y,32,0);

  //creating player
  struct opx_vector_float player;
    player.x=0;
    player.y=0.630;
    player.z=-0.002;
    float anglexz=pi/2;
    float anglexy=0;
    int i=0;
    long rand_=144253115;
   while(i<100)
      {
	i++;
	rand_=opx_random(rand_);
        printf("%ld\n",rand_);
        //opx_render(player,anglexy,anglexz,resolution_x,resolution_y,0);
	//player.y=player.y-0.002;
	//break;
      }

}
