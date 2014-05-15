#include "opx.h"


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
float opx_intersect_vector_star(struct opx_vector_float start,struct opx_vector_float vector,void *stars_collection)
{
  //the abc-formula is used
  float a,b,c,d,l=0,radius;
  struct opx_vector_float star_;
    star_.x=*(float*)(stars_collection+sizeof(long));
    star_.y=*(float*)(stars_collection+2*sizeof(long));
    star_.z=*(float*)(stars_collection+3*sizeof(long));
    radius=*(float*)(stars_collection+4*sizeof(long));

  struct opx_vector_float dx; 
    dx.x=start.x-star_.x;
    dx.y=start.y-star_.y;
    dx.z=start.z-star_.z;

  a=vector.x*vector.x+vector.y*vector.y+vector.z*vector.z;
  b=2*(dx.x*vector.x+dx.y*vector.y+dx.z*vector.z);
  c=dx.x*dx.x+dx.y*dx.y+dx.z*dx.z-radius*radius;

  //discriminant
  d=b*b-4*a*c;

  if(d>0)
    {
      l=(-b-opx_sqrt(d))/(2*a);
    }
  return l;
}
