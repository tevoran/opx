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

//command queues
cl_command_queue command_queue;

//cl program
cl_program program;

//cl kernels
cl_kernel kernel_vectoraddition;

//item sizes
size_t global_item_size=1;
size_t local_item_size=1;

void opx_init_opencl()
{
  cl_int ret;//variable for error codes
  FILE *kernel_file;
  size_t kernel_size;
  char *vectoraddition_src;

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
  context=clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);
  if(ret!=CL_SUCCESS)
    {
      printf("OpenCL error while creating a context\n");
    }

  //creating command queue
  command_queue=clCreateCommandQueue(context,device_id,0,&ret);
  if(ret!=CL_SUCCESS)
    {
      printf("OpenCL error while creating a command queue\n");
    }

  //creating kernels from opx/kernels/
    //vector addition
    printf("    loading kernel: opx/kernels/vectoraddition.cl\n");
    kernel_file=fopen("opx/kernels/vectoraddition.cl","r");
      //allocate memory for the src
      fseek(kernel_file,0,SEEK_END);
      kernel_size=ftell(kernel_file);
      fseek(kernel_file,0,SEEK_SET);
      vectoraddition_src=malloc(kernel_size);

    kernel_size=fread(vectoraddition_src,1,kernel_size,kernel_file);

      printf("    kernel_size: %i\n",(int)kernel_size);
      fclose(kernel_file);//close FILE pointer;
    program=clCreateProgramWithSource(context,1,(const char**)&vectoraddition_src,NULL,&ret);
    if(ret!=CL_SUCCESS)
      {
	printf("OpenCL error while creating kernel\n");
      }

    ret=clBuildProgram(program,1,&device_id,NULL,NULL,NULL);
    switch(ret)
      {
      case(CL_INVALID_PROGRAM):
	{
	printf("program is not a valid program object\n");
	}
      case(CL_INVALID_VALUE):
	{
	  printf("device_list is NULL and num_devices is greater\n"
		 "than zero, or if device_list is not NULL and\n"
		 "num_devices is zero.\n"
		 "OR:\n"
		 "pfn_notify is NULL but user_data is not NULL .\n");
	}
      case(CL_INVALID_DEVICE):
	{
	  printf("invalid device\n");
	}
      case(CL_INVALID_BUILD_OPTIONS):
	{
	  printf("invalid build options\n");
	}
      case(CL_INVALID_OPERATION):
	{
	  printf("previous build was not complete\n"
		 "OR:\n"
		 "there are kernel objects attached\n"
		 "to this program\n");
	}
      case(CL_COMPILER_NOT_AVAILABLE):
	{
	  printf("compiler is not available\n");
	}
      case(CL_BUILD_PROGRAM_FAILURE):
	{
	  printf("build program failure\n");
	}
      }

    kernel_vectoraddition=clCreateKernel(program,"vectoraddition",&ret);
    if(ret!=CL_SUCCESS)
      {
	printf("OpenCL error while creating kernel 'vectoraddition'\n");
      }
    if(ret==CL_INVALID_KERNEL_NAME)
      {
	printf("the kernel name was not found\n");
      }

    //execute kernel
    ret=clEnqueueNDRangeKernel(command_queue,kernel_vectoraddition,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);
    if(ret==CL_SUCCESS)
      {
	printf("successfull first started kernel\n");
      }
}
