#include "opx.h"

float opx_cos(float number)
{
  int sign=1;
  while(number>pi)
    {
      number=number-pi;
      sign=sign*(-1);
      }
  int i=1;
  float y=1;
  for(i;i<icos;i++)
    {
      y=y*(1-(4*number*number)/((2*i-1)*(2*i-1)*pi*pi));
    }
  y=y*(float)sign;
  return y;
}


//calculating sine by using productsums
float opx_sin(float number)
{
  int sign=1;
  while(number>pi)
    {
      number=number-pi;
      sign=sign*(-1);
      }
  int i=1;
  float x=number;
  float y=1;
  if(number==0)
    {
      return x;
    }
  else
    {
      for(i;i<=isin;i++)
	{
	  y=y*(1-(number*number)/(i*i*pi*pi));
	}
      x=x*y*(float)sign;
    }
  return x;
}

long long opx_factorial(int number)
{
  long long x;
  if(number==0)
    {
      x=1;
      return x;
    }

  x=number;
  for (number--;number>0;number--)
    {
      x=x*number;
    }
  return x;
}

float opx_exponentiation(float number,int power)
{
  float x=1;
  if(power==0)
    {
      x=1;
      return x;
    }
  if(number==0)
    {
      x=0;
      return x;
    }
  for(power;power>0;power--)
    {
      x=x*number;
    }
  return x;
}

//calculating squareroots by the babylonian method
float opx_sqrt(float number)
{
  int i=isqrt;//defines quality of sqareroot
  float x;
  if(number==0)
    {
      x=0;
    }
  else
    {
      x=(number+1)/2;
      for(i;i>0;i--)
	{
	  x=(x+number/x)/2;
	}
    }
  return x;
}
