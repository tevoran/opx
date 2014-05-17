#include "opx.h"
#include <stdio.h>
#include <CL/cl.h>

//platform and device information variables
cl_platform_id platform_id=NULL;
cl_device_id device_id=NULL;
cl_uint num_devices;
cl_uint num_platforms;

//context
cl_context context;

void opx_init_opencl()
{
  cl_int ret;//variable for error codes

  //getting platformids
  ret=clGetPlatformIDs(1,&platform_id,&num_platforms);
  if(ret!=CL_SUCCESS)
    {
      printf("OpenCL error while getting platform ids\n");
    }

  //getting deviceids
  ret=clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_GPU,1,&device_id,&num_devices);
  if(ret!=CL_SUCCESS)
    {
      printf("OpenCL error while getting device id of GPU\n");
    }
  if(ret==CL_INVALID_DEVICE_TYPE)
    {
      printf("it is not possible to perform OpenCL on the GPU\n");
    }

  //getting information about the device
  clGetDeviceInfo(device_id,CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_int),&ret,NULL);
  printf("\n    Number of maximal compute units: %i\n",ret);


  //creating context
  //context=clCreateContext(
}
