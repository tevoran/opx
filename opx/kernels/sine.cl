__kernel void sine(__global float *in,__global float *out)
{
	int id=get_global_id(0);
	out[id]=sin(in[id]);
}
