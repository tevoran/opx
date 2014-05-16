#include "opx.h"
#include <SDL/SDL.h>
#include <SDL_opengl.h>

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
