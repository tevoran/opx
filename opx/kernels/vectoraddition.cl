__kernel void vectoraddition(global float *in,global float *in2, global float *out)
{
	*out=*in+*in2;
}