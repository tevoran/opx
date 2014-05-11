#include "opx.h"

double opx_cos(double number)
{
  int sign=1;
  while(number>pi)
    {
      number=number-pi;
      sign=sign*(-1);
      }
  int i=0;
  double x=0;
  for(i;i<icos;i++)
    {
      x=x+(opx_exponentiation(-1,i)*opx_exponentiation(number,2*i)/opx_factorial(2*i));
    }
  x=x*(double)sign;
  return x;
}


//calculating sine by using productsums
double opx_sin(double number)
{
  int sign=1;
  while(number>pi)
    {
      number=number-pi;
      sign=sign*(-1);
      }
  int i=1;
  double x=number;
  double y=1;
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
      x=x*y*(double)sign;
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

double opx_exponentiation(double number,int power)
{
  double x=1;
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
double opx_sqrt(double number)
{
  int i=isqrt;//defines quality of sqareroot
  double x;
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
