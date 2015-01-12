/*
 * DynaCL: Dynamic OpenCL library loader for Windows
 * 
 * Copyright (c) 2015 Alfredo Mungo
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __DYANCL_H
#define __DYANCL_H

#include <windows.h>
#include <CL/cl.h> /* FIXME: After fixing all the files, change this to CL/opencl.h */

#ifdef DYNACL_INTERNAL
  #define DYNACL_EXTERN
  #define DYNACL_NULLPTR = NULL
#else
  #define DYNACL_EXTERN extern
  #define DYNACL_NULLPTR
#endif /* DYNACL_INTERNAL */

/* ERROR CODES: */
#define DYNACL_SUCCESS 0
#define DYNACL_FILE_NOT_FOUND 1
#define DYNACL_CANNOT_OPEN_FILE 2
#define DYNACL_IMPORT_ERROR 3
#define DYNACL_UNKNOWN_ERROR 0xffffffff
/* ERROR CODES END */

/* OPENCL FUNCTION POINTERS: */
DYNACL_EXTERN CLGETPLATFORMIDS_PTR clGetPlatformIDs DYNACL_NULLPTR;
DYNACL_EXTERN CLGETPLATFORMINFO_PTR clGetPlatformInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLGETDEVICEIDS_PTR clGetDeviceIDs DYNACL_NULLPTR;
DYNACL_EXTERN CLGETDEVICEINFO_PTR clGetDeviceInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATECONTEXT_PTR clCreateContext DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATECONTEXTFROMTYPE_PTR clCreateContextFromType DYNACL_NULLPTR;
DYNACL_EXTERN CLRETAINCONTEXT_PTR clRetainContext DYNACL_NULLPTR;
DYNACL_EXTERN CLRELEASECONTEXT_PTR clReleaseContext DYNACL_NULLPTR;
DYNACL_EXTERN CLGETCONTEXTINFO_PTR clGetContextInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATECOMMANDQUEUE_PTR clCreateCommandQueue DYNACL_NULLPTR;
DYNACL_EXTERN CLRETAINCOMMANDQUEUE_PTR clRetainCommandQueue DYNACL_NULLPTR;
DYNACL_EXTERN CLRELEASECOMMANDQUEUE_PTR clReleaseCommandQueue DYNACL_NULLPTR;
DYNACL_EXTERN CLGETCOMMANDQUEUEINFO_PTR clGetCommandQueueInfo DYNACL_NULLPTR;
#ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
  DYNACL_EXTERN CLSETCOMMANDQUEUEPROPERTY_PTR clSetCommandQueueProperty DYNACL_NULLPTR;
#endif
DYNACL_EXTERN CLCREATEBUFFER_PTR clCreateBuffer DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATESUBBUFFER_PTR clCreateSubBuffer DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATEIMAGE2D_PTR clCreateImage2D DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATEIMAGE3D_PTR clCreateImage3D DYNACL_NULLPTR;
DYNACL_EXTERN CLRETAINMEMOBJECT_PTR clRetainMemObject DYNACL_NULLPTR;
DYNACL_EXTERN CLRELEASEMEMOBJECT_PTR clReleaseMemObject DYNACL_NULLPTR;
DYNACL_EXTERN CLGETSUPPORTEDIMAGEFORMATS_PTR clGetSupportedImageFormats DYNACL_NULLPTR;
DYNACL_EXTERN CLGETMEMOBJECTINFO_PTR clGetMemObjectInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLGETIMAGEINFO_PTR clGetImageInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLSETMEMOBJECTDESTRUCTORCALLBACK_PTR clSetMemObjectDestructorCallback DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATESAMPLER_PTR clCreateSampler DYNACL_NULLPTR;
DYNACL_EXTERN CLRETAINSAMPLER_PTR clRetainSampler DYNACL_NULLPTR;
DYNACL_EXTERN CLRELEASESAMPLER_PTR clReleaseSampler DYNACL_NULLPTR;
DYNACL_EXTERN CLGETSAMPLERINFO_PTR clGetSamplerInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATEPROGRAMWITHSOURCE_PTR clCreateProgramWithSource DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATEPROGRAMWITHBINARY_PTR clCreateProgramWithBinary DYNACL_NULLPTR;
DYNACL_EXTERN CLRETAINPROGRAM_PTR clRetainProgram DYNACL_NULLPTR;
DYNACL_EXTERN CLRELEASEPROGRAM_PTR clReleaseProgram DYNACL_NULLPTR;
DYNACL_EXTERN CLBUILDPROGRAM_PTR clBuildProgram DYNACL_NULLPTR;
DYNACL_EXTERN CLUNLOADCOMPILER_PTR clUnloadCompiler DYNACL_NULLPTR;
DYNACL_EXTERN CLGETPROGRAMINFO_PTR clGetProgramInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLGETPROGRAMBUILDINFO_PTR clGetProgramBuildInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATEKERNEL_PTR clCreateKernel DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATEKERNELSINPROGRAM_PTR clCreateKernelsInProgram DYNACL_NULLPTR;
DYNACL_EXTERN CLRETAINKERNEL_PTR clRetainKernel DYNACL_NULLPTR;
DYNACL_EXTERN CLRELEASEKERNEL_PTR clReleaseKernel DYNACL_NULLPTR;
DYNACL_EXTERN CLSETKERNELARG_PTR clSetKernelArg DYNACL_NULLPTR;
DYNACL_EXTERN CLGETKERNELINFO_PTR clGetKernelInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLGETKERNELWORKGROUPINFO_PTR clGetKernelWorkGroupInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLWAITFOREVENTS_PTR clWaitForEvents DYNACL_NULLPTR;
DYNACL_EXTERN CLGETEVENTINFO_PTR clGetEventInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLCREATEUSEREVENT_PTR clCreateUserEvent DYNACL_NULLPTR;
DYNACL_EXTERN CLRETAINEVENT_PTR clRetainEvent DYNACL_NULLPTR;
DYNACL_EXTERN CLRELEASEEVENT_PTR clReleaseEvent DYNACL_NULLPTR;
DYNACL_EXTERN CLSETUSEREVENTSTATUS_PTR clSetUserEventStatus DYNACL_NULLPTR;
DYNACL_EXTERN CLSETEVENTCALLBACK_PTR clSetEventCallback DYNACL_NULLPTR;
DYNACL_EXTERN CLGETEVENTPROFILINGINFO_PTR clGetEventProfilingInfo DYNACL_NULLPTR;
DYNACL_EXTERN CLFLUSH_PTR clFlush DYNACL_NULLPTR;
DYNACL_EXTERN CLFINISH_PTR clFinish DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEREADBUFFER_PTR clEnqueueReadBuffer DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEREADBUFFERRECT_PTR clEnqueueReadBufferRect DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEWRITEBUFFER_PTR clEnqueueWriteBuffer DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEWRITEBUFFERRECT_PTR clEnqueueWriteBufferRect DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUECOPYBUFFER_PTR clEnqueueCopyBuffer DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUECOPYBUFFERRECT_PTR clEnqueueCopyBufferRect DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEREADIMAGE_PTR clEnqueueReadImage DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEWRITEIMAGE_PTR clEnqueueWriteImage DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUECOPYIMAGE_PTR clEnqueueCopyImage DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUECOPYIMAGETOBUFFER_PTR clEnqueueCopyImageToBuffer DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUECOPYBUFFERTOIMAGE_PTR clEnqueueCopyBufferToImage DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEMAPBUFFER_PTR clEnqueueMapBuffer DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEMAPIMAGE_PTR clEnqueueMapImage DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEUNMAPMEMOBJECT_PTR clEnqueueUnmapMemObject DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUENDRANGEKERNEL_PTR clEnqueueNDRangeKernel DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUETASK_PTR clEnqueueTask DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUENATIVEKERNEL_PTR clEnqueueNativeKernel DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEMARKER_PTR clEnqueueMarker DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEWAITFOREVENTS_PTR clEnqueueWaitForEvents DYNACL_NULLPTR;
DYNACL_EXTERN CLENQUEUEBARRIER_PTR clEnqueueBarrier DYNACL_NULLPTR;
DYNACL_EXTERN CLGETEXTENSIONFUNCTIONADDRESS_PTR clGetExtensionFunctionAddress DYNACL_NULLPTR;
/* OPENCL FUNCTION POINTERS END */

/*!
 * Initialize OpenCL function pointers.
 *
 * \p dllLibrary File path to the OpenCL DLL file
 *
 * \return DYNACL_SUCCESS on success, other error codes on error
 * \see ERROR CODES
 */
DYNACL_EXTERN unsigned int dynacl_init(LPCSTR dllLibrary);

/*!
 * Cleans the function pointers used by this library and frees any
 * allocated resource.
 *
 * \return DYNACL_SUCCESS on success, other error codes on error
 * \see ERROR CODES
 */
DYNACL_EXTERN void dynacl_shutdown();

#endif /* __DYANCL_H */