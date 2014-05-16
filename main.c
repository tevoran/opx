#include <stdlib.h>
#include <SDL/SDL.h>
#include "include/definitions.h"
#include "opx/opx.h"

void main()
{
  //Setting up SDL
  SDL_Event event;
  Uint8 *keyboard;
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,1);

  //Setting up OPX
  long seed=434453777;
  opx_init(resolution_x,resolution_y,32);

  //creating content
    //creating stars
    int n=opx_random(seed)%10;
    long new_seed=opx_random(seed);
    float x,y,z,radius;
    float r,g,b;
    for(n;n>=0;n--)
      {
	x=opx_random(new_seed)%30000-15000;
	  new_seed=opx_random(new_seed);
	y=opx_random(new_seed)%5000;
	  new_seed=opx_random(new_seed);
	z=opx_random(new_seed)%30000-15000;
	  new_seed=opx_random(new_seed);
	radius=opx_random(new_seed)%150;
	  new_seed=opx_random(new_seed);
	r=(float)((float)(opx_random(new_seed)%250)/256);
	  new_seed=opx_random(new_seed);
	g=(float)((float)(opx_random(new_seed)%150)/256);
	  new_seed=opx_random(new_seed);
	b=(float)((float)(opx_random(new_seed)%100)/256);
	  new_seed=opx_random(new_seed);
	opx_add_star(x,y,z,radius,r,g,b,n);
      }
  

  //creating player
  struct opx_vector_float player;
    player.x=0;
    player.y=0.6301;
    player.z=0;
    float anglexz=pi/2;
    float anglexy=0.4;

    int ltimer=SDL_GetTicks();
    int timer=0;


    //Mainloop
    while(1)
      {
	timer=SDL_GetTicks();
          printf("Time per frame: %i ms\n",timer-ltimer);
	  float FPS=(float)(float)1000/(float)(timer-ltimer);
	  printf("FPS: %f\n",FPS);
	ltimer=timer;
        opx_render(player,anglexy,anglexz,resolution_x,resolution_y);
        anglexz=anglexz+0.05;

	//end OPX after pressing ESC
	SDL_PollEvent(&event);
	keyboard=SDL_GetKeyState(NULL);
        if(keyboard[SDLK_ESCAPE])
	  {
	    atexit(SDL_Quit);
	    break;
	  }
      }

}
