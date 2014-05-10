#include <stdlib.h>
#include <SDL/SDL.h>
#include "include/definitions.h"
#include "opx/opx.h"

void main()
{
  //Setting up OPX
  opx_init(resolution_x,resolution_y,32);

  //creating player
  struct opx_vector_float player;
    player.x=0;
    player.y=0;
    player.z=3;
    float anglexz=pi/2+0.5;
    float anglexy=-0.4;

   while(1)
      {
       	opx_render(player,anglexy,anglexz,resolution_x,resolution_y);
      }

}
