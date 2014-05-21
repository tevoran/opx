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
size_t max_workgroup_size;
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
  opx_cl_error(ret,"OpenCL error while getting platform ids\n");

  //getting deviceids
  ret=clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_GPU,1,&device_id,&num_devices);
  opx_cl_error(ret,"OpenCL error while getting device id of GPU\n");

  //getting information about the device
  clGetDeviceInfo(device_id,CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_int),&ret,NULL);
  printf("\n    Number of maximal compute units: %i\n",ret);

  clGetDeviceInfo(device_id,CL_DEVICE_MAX_WORK_GROUP_SIZE,sizeof(size_t),&max_workgroup_size,NULL);
  printf("    max workgroup size is: %i\n",(int)max_workgroup_size);

  //creating context
  context=clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);
  opx_cl_error(ret,"OpenCL error while creating a context\n");

  //creating command queue
  command_queue=clCreateCommandQueue(context,device_id,0,&ret);
  opx_cl_error(ret,"OpenCL error while creating a command queue\n");

  //creating kernels from opx/kernels/
    //vector addition
    printf("    loading kernel: opx/kernels/vectoraddition.cl\n");
    kernel_file=fopen("opx/kernels/vectoraddition.cl","r");
      //allocate memory for the src
      fseek(kernel_file,0,SEEK_END);
      kernel_size=ftell(kernel_file);
      fseek(kernel_file,0,SEEK_SET);
      vectoraddition_src=malloc(kernel_size+1);

    kernel_size=fread(vectoraddition_src,1,kernel_size,kernel_file);

      printf("    kernel_size: %i\n",(int)kernel_size);
      fclose(kernel_file);//close FILE pointer;
    program=clCreateProgramWithSource(context,1,(const char**)&vectoraddition_src,NULL,&ret);
    opx_cl_error(ret,"OpenCL error while creating program\n");

    ret=clBuildProgram(program,1,&device_id,NULL,NULL,NULL);
    opx_cl_error(ret,"OpenCL error while building program\n");

    kernel_vectoraddition=clCreateKernel(program,"vectoraddition",&ret);
    opx_cl_error(ret,"OpenCL error while creating kernel 'vectoraddition'\n");

    //execute kernel
    float c=0;
    cl_mem d=clCreateBuffer(context,CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,sizeof(float),&c,&ret);

    ret=clSetKernelArg(kernel_vectoraddition,0,sizeof(d),&d);

    ret=clEnqueueNDRangeKernel(command_queue,kernel_vectoraddition,1,0,&global_item_size,&local_item_size,0,NULL,NULL);
    opx_cl_error(ret,"error while executing kernel\n");

    ret=clEnqueueReadBuffer(command_queue,d,CL_TRUE,0,sizeof(float),&c,0,NULL,NULL);
    opx_cl_error(ret,"not successfully read from buffer\n");
    printf("c: %f\n",c);
}

void opx_cl_error(cl_int ret,const char *error_msg)
{
  if(ret!=CL_SUCCESS)
    {
      printf("%s",error_msg);
    }
}
