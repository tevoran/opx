#include "opx.h"
#include <stdlib.h>
#include <string.h>


//this function randomly generates a japanese like name
/*char* opx_name_gen(long seed)
{
  int length;
  long new_seed;
  int mora_choose;

  //deciding how many mores the name has
  length=opx_random(seed)%7;
  char output[14];
  //deciding which mores are used
    //62 japanese mores
  new_seed=seed;
  for(length;length>0;length--)
    {
      new_seed=opx_random(new_seed);
      mora_choose=new_seed%14;
      switch(mora_choose)
	{
	case(0):output[length]="k";break;
	case(1):output[length]="s";break;
	case(2):output[length]="t";break;
	case(3):output[length]="n";break;
	case(4):output[length]="h";break;
	case(5):output[length]="m";break;
	case(6):output[length]="y";break;
	case(7):output[length]="r";break;
	case(8):output[length]="w";break;
	case(9):output[length]="g";break;
	case(10):output[length]="z";break;
	case(11):output[length]="d";break;
	case(12):output[length]="b";break;
	case(13):output[length]="p";break;
	}

       new_seed=opx_random(new_seed);
      mora_choose=new_seed%5;
      switch(mora_choose)
	{
	case(0):output[length]="a";break;
	case(1):output[length]="i";break;
	case(2):output[length]="u";break;
	case(3):output[length]="e";break;
	case(4):output[length]="o";break;
	}
    }
  return output;
  }*/
