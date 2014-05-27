__kernel void vectoraddition(global float *in,global float *in2, global float *out)
{
	out[0]=in[0]+in2[0];
}