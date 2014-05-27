#ifndef OPX_H
#define OPX_H

#include <CL/cl.h> //included for data type cl_int

//quality
#define icos 7 //defines the quality of cosine
                //must be <12 due to technical reasons
#define isin 7 //defines the quality of sine
#define isqrt 7 //defines the quality of squareroot
#define max_stars 1000000 //defines the max number of stars
#define render_bubble_radius 550000 //defines the radius of a bubble where stars are raytraced

//numbers
#define pi 3.141592654

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
    float m; //mass
    float xs; //speed x
    float ys; //speed y
    float zs; //speed z
    float color_r;
    float color_g;
    float color_b;
    int *star; //shows the adress in memory of the parent star
    int *next; //an index to the next planet in the solar system
               //if 0x0 then this planet is the last planet of the system
  };

//math functions
long opx_random(long seed);
float opx_cos(float number);
float opx_sin(float number);
float opx_sqrt(float number);
long long opx_factorial(int number);
float opx_exponentiation(float number,int power);

//engine functions
void opx_add_star(float x,float y,float z,float radius,float r,float g,float b,int number);
void opx_init(int resx, int resy, int colordepth);
void opx_init_opencl();
void opx_render(struct opx_vector_float player,float anglexy,float anglexz, int resx, int resy);
void opx_update_bubble(struct opx_vector_float player);

//gfx functions
void opx_pixel(int x,int y,float r,float g,float b);
void opx_cls();

//intersections
float opx_intersect_vector_planet(struct opx_vector_float start,struct opx_vector_float vector,struct planet planet);
float opx_intersect_vector_star(struct opx_vector_float start,struct opx_vector_float vector,void *stars_collection);

//opx opencl functions
void opx_cl_error(cl_int ret,const char *error_msg); //for error messages
float opx_vector_add(float in1,float in2,float out,int count);
#endif
