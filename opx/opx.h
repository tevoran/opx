#ifndef OPX_H
#define OPX_H

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

void opx_init();
void opx_render();

#endif
