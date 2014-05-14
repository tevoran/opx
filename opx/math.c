#include "opx.h"


//randomgenerator (after Blum-Blum-Shub)
//seed has max. 9 decimals
//the output has also max 9 decimals
long opx_random(long seed)
{
  long p=10007;
  long q=100003;
  long n=p*q;
  long output;
  output=seed;
  while(1)
    {
      output=(output*output)%n;
      if(output<1000000000)
	{
	  break;
	}
    }  
  return output;
}

//calculating cosine by using productsums
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
  float number_square=number*number;
  float pi_square=pi*pi;
  for(i;i<icos;i++)
    {
      y=y*(1-(4*number_square)/((2*i-1)*(2*i-1)*pi_square));
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
  float number_square=number*number;
  float pi_square=pi*pi;
  for(i;i<=isin;i++)
    {
      y=y*(1-(number_square)/(i*i*pi_square));
    }
  x=x*y*(float)sign;
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
