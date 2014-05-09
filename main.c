#include <stdlib.h>
#include <SDL/SDL.h>
#include "include/definitions.h"
#include "opx/opx.h"

void main()
{
  //Setting up OPX
  opx_init(resx,resy,32);

  //creating player
  struct opx_vector_float player;
    player.x=0;
    player.y=0;
    player.z=0;

    int i=9;
    for(i;i>0;i--)
      {
       	opx_render(player,resx,resy,32);
	player.z++;
	SDL_Delay(500);
      }

}
