#ifndef OPX_H
#define OPX_H

//quality
#define icos 10 //defines the quality of cosine
                //must be <12 due to technical reasons
#define isin 10 //defines the quality of sine
#define isqrt 10 //defines the quality of squareroot

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
  };

//math functions
double opx_cos(double number);
double opx_sin(double number);
double opx_sqrt(double number);
long long opx_factorial(int number);
double opx_exponentiation(double number,int power);

//engine functions
void opx_init(int resx, int resy, int colordepth);
void opx_render(struct opx_vector_float player,float anglexy,float anglexz, int resx, int resy);

#endif
