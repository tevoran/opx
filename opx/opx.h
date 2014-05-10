#ifndef OPX_H
#define OPX_H

//numbers
#define pi 3.1415

//structs
//struct vector_float
  struct opx_vector_float
  {
    float x;
    float y;
    float z;
  };

//struct planet
  struct planet
  {
    float x;
    float y;
    float z;
    float r; //radius
  };

double opx_cos(double number);
double opx_sin(double number);
void opx_init(int resx, int resy, int colordepth);
void opx_render(struct opx_vector_float player,float anglexy,float anglexz, int resx, int resy);

#endif
