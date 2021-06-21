
// #include "OpenCL/cl.h"
// #include "OpenCL/opencl.h"

// #include <opencl-c.h>
#include <CL/cl.h>
#include <CL/opencl.h>

#include "core/types.h"

const char * matrix_mul_kernel = R"(
int get_block_start_index(int i, int j, int columns, int block_height, int block_width) {
	int block_line = i/block_height;
	int block_column = j/block_width;
	return block_line*(columns/block_width)*(block_height * block_width) + block_column * (block_height * block_width);
}

int get_index(int i, int j, int columns, int block_height, int block_width) {
	int y = i%block_height;
	int x = j%block_width;
	return get_block_start_index(i,j, columns, block_height, block_width) + (y*block_width + x);
}

__kernel void matrix_mul(
	const int block_height,
	const int block_width,
	const int lines,
	const int columns,
	const int A_columns,
	const int B_lines,
  	const __global float* A,
	const __global float* B,
  	__global float* C
) {
	const int i = get_global_id(0);
	const int j = get_global_id(1);

	// C[get_block_start_index(i, j, columns, block_height, block_width)] = 1;//get_global_id(0)*lines + get_global_id(1);
	// C[get_index(i*block_height, j*block_width, columns, block_height, block_width)] = get_index(i*block_height, j*block_width, columns, block_height, block_width)/(block_height*block_width);
	for(int k=0; k<A_columns/block_width; k++) {
	
		for(int y=0; y<block_height; y++) {
			for(int x=0; x<block_width; x++) {
				for(int q=0; q<block_width; q++) {
					// printf("	c[%i %i] += a[%i %i] * b[%i %i]\n",
					// 	(block_height*i)%lines +  y, (block_width*j)%columns + x,
					// 	(block_height*i)%lines + y, (block_width*k)%A_columns + (x+q)%block_width,
					// 	(block_height*k)%B_lines + (y+q)%block_height, (block_width*j)%columns + x
					// );

					C[
						get_index((block_height*i)%lines + y, (block_width*j)%columns + x, columns, block_height, block_width)
					] += A[
						get_index((block_height*i)%lines + y, (block_width*k)%A_columns + (x+q)%block_width, A_columns, block_height, block_width)
					] * B[
						get_index((block_height*k)%B_lines + (x+q)%block_width, (block_width*j)%columns + x, columns, block_height, block_width)
					];
				}
			}
		}
	}
	
	// C[get_index(i, j, columns, block_height, block_width)] = j;

	// for(int k=0; k < max(A_columns/block_width, B_lines/block_height); k++) {
	// 	for(int y=0; y<block_height; y++) {
	// 		for(int x=0; x<block_width; x++) {
	// 			for(int q=0; q < max(block_height, block_width); q++) {
	// 				int Cl = i+y;
	// 				int Cc = j+x;
	// 				int Al = i+y;
	// 				int Ac = ((i+k*block_width)%A_columns + x + q) % A_columns;
	// 				int Bl = ((i+k*block_height)%B_lines + x + q) % B_lines;
	// 				int Bc = j + x;
					
	// 				C[get_index(Cl, Cc, block_height, block_width)] += 
	// 					A[A.get_index(Al, Ac, block_height, block_width)] * B[get_index(Bl, Bc, block_height, block_width)];
	// 			}
	// 		}
	// 	}
	// }

}
)";

void mul_matrix(
	f32* A,
	f32* B,
	f32* C,
	i32 block_width,
	i32 block_heigth,
	i32 lines,
	i32 columns,
	i32 A_columns,
	i32 B_lines
) {
	cl_int err;
	cl_context context = clCreateContextFromType(NULL, CL_DEVICE_TYPE_ALL, NULL, NULL, &err);
	
	cl_uint num = 1;
	cl_device_id devices;

	clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 0, NULL, &num);

	clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, num, &devices, &num);
	cl_command_queue queue = clCreateCommandQueue(context, devices, 0, &err);

	cl_mem memobjs[] = {
		clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(cl_float) * lines*A_columns, NULL, NULL),
		clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(cl_float) * B_lines*columns, NULL, NULL),
		clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_float) * lines*columns, NULL, NULL),
	};

	clEnqueueWriteBuffer(queue, memobjs[0], CL_TRUE, 0, sizeof(cl_float)*lines*A_columns, A, 0, NULL, NULL);
	clEnqueueWriteBuffer(queue, memobjs[1], CL_TRUE, 0, sizeof(cl_float)*B_lines*columns, B, 0, NULL, NULL);
	clEnqueueWriteBuffer(queue, memobjs[2], CL_TRUE, 0, sizeof(cl_float)*lines*columns, C, 0, NULL, NULL);
	
	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&matrix_mul_kernel, NULL, &err);

	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

	cl_kernel kernel = clCreateKernel(program, "matrix_mul", NULL);

	clSetKernelArg(kernel, 0, sizeof(cl_int), (void*)&block_heigth);
	clSetKernelArg(kernel, 1, sizeof(cl_int), (void*)&block_width);
	clSetKernelArg(kernel, 2, sizeof(cl_int), (void*)&lines);
	clSetKernelArg(kernel, 3, sizeof(cl_int), (void*)&columns);
	clSetKernelArg(kernel, 4, sizeof(cl_int), (void*)&A_columns);
	clSetKernelArg(kernel, 5, sizeof(cl_int), (void*)&B_lines);
	clSetKernelArg(kernel, 6, sizeof(cl_mem), (void *)&memobjs[0]);
	clSetKernelArg(kernel, 7, sizeof(cl_mem), (void *)&memobjs[1]);
	clSetKernelArg(kernel, 8, sizeof(cl_mem), (void *)&memobjs[2]);

	size_t global_work_size[2];
	global_work_size[0] = (size_t)(lines/block_heigth);
	global_work_size[1] = (size_t)(columns/block_width);

	size_t local_work_size[2];
	local_work_size[0] = (size_t)(block_heigth);
	local_work_size[1] = (size_t)(block_width);

	err = clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_work_size, local_work_size, 0, NULL, NULL);
	
	err = clEnqueueReadBuffer(queue, memobjs[2], CL_TRUE, 0, lines*columns*sizeof(cl_float), (void*)C, 0, NULL, NULL);
}