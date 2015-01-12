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
#define DYNACL_INTERNAL
#include <windows.h>
#include <CL/dynacl.h>

static HMODULE dynacl_dll = NULL;

/*!
 * Loads each function from the library.
 *
 * \return DYNACL_SUCCESS on success, DYNACL_IMPORT_ERROR on error
 */
static unsigned int dynacl_loadLibraries();

unsigned int dynacl_init(LPCSTR dllLibrary) {
  dynacl_dll = LoadLibrary(dllLibrary); /* FIXME: Check if the file exists before calling this function */

  if(dynacl_dll != NULL) { /* Module has been loaded */
    return dynacl_loadLibraries();
  } else { /* Module has not been loaded */
    DWORD err = GetLastError();

    switch(err) {
      case ERROR_MOD_NOT_FOUND:
        return DYNACL_FILE_NOT_FOUND;
      case ERROR_TOO_MANY_OPEN_FILES:
      case ERROR_ACCESS_DENIED:
      case ERROR_NOT_ENOUGH_MEMORY:
      case ERROR_OUTOFMEMORY:
      case ERROR_INVALID_DRIVE:
        return DYNACL_CANNOT_OPEN_FILE;
      default:
        return DYNACL_UNKNOWN_ERROR;
    }
  }
}

static unsigned int dynacl_loadLibraries() {
  #define DYNACL_LOADFUNC(functype, funcvar) if((funcvar = (functype)GetProcAddress(dynacl_dll, TEXT(#funcvar))) == NULL) return DYNACL_IMPORT_ERROR
    DYNACL_LOADFUNC(CLGETPLATFORMIDS_PTR, clGetPlatformIDs);
    DYNACL_LOADFUNC(CLGETPLATFORMINFO_PTR, clGetPlatformInfo);
    DYNACL_LOADFUNC(CLGETDEVICEIDS_PTR, clGetDeviceIDs);
    DYNACL_LOADFUNC(CLGETDEVICEINFO_PTR, clGetDeviceInfo);
    DYNACL_LOADFUNC(CLCREATECONTEXT_PTR, clCreateContext);
    DYNACL_LOADFUNC(CLCREATECONTEXTFROMTYPE_PTR, clCreateContextFromType);
    DYNACL_LOADFUNC(CLRETAINCONTEXT_PTR, clRetainContext);
    DYNACL_LOADFUNC(CLRELEASECONTEXT_PTR, clReleaseContext);
    DYNACL_LOADFUNC(CLGETCONTEXTINFO_PTR, clGetContextInfo);
    DYNACL_LOADFUNC(CLCREATECOMMANDQUEUE_PTR, clCreateCommandQueue);
    DYNACL_LOADFUNC(CLRETAINCOMMANDQUEUE_PTR, clRetainCommandQueue);
    DYNACL_LOADFUNC(CLRELEASECOMMANDQUEUE_PTR, clReleaseCommandQueue);
    DYNACL_LOADFUNC(CLGETCOMMANDQUEUEINFO_PTR, clGetCommandQueueInfo);
    #ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
      DYNACL_LOADFUNC(CLSETCOMMANDQUEUEPROPERTY_PTR, clSetCommandQueueProperty);
    #endif
    DYNACL_LOADFUNC(CLCREATEBUFFER_PTR, clCreateBuffer);
    DYNACL_LOADFUNC(CLCREATESUBBUFFER_PTR, clCreateSubBuffer);
    DYNACL_LOADFUNC(CLCREATEIMAGE2D_PTR, clCreateImage2D);
    DYNACL_LOADFUNC(CLCREATEIMAGE3D_PTR, clCreateImage3D);
    DYNACL_LOADFUNC(CLRETAINMEMOBJECT_PTR, clRetainMemObject);
    DYNACL_LOADFUNC(CLRELEASEMEMOBJECT_PTR, clReleaseMemObject);
    DYNACL_LOADFUNC(CLGETSUPPORTEDIMAGEFORMATS_PTR, clGetSupportedImageFormats);
    DYNACL_LOADFUNC(CLGETMEMOBJECTINFO_PTR, clGetMemObjectInfo);
    DYNACL_LOADFUNC(CLGETIMAGEINFO_PTR, clGetImageInfo);
    DYNACL_LOADFUNC(CLSETMEMOBJECTDESTRUCTORCALLBACK_PTR, clSetMemObjectDestructorCallback);
    DYNACL_LOADFUNC(CLCREATESAMPLER_PTR, clCreateSampler);
    DYNACL_LOADFUNC(CLRETAINSAMPLER_PTR, clRetainSampler);
    DYNACL_LOADFUNC(CLRELEASESAMPLER_PTR, clReleaseSampler);
    DYNACL_LOADFUNC(CLGETSAMPLERINFO_PTR, clGetSamplerInfo);
    DYNACL_LOADFUNC(CLCREATEPROGRAMWITHSOURCE_PTR, clCreateProgramWithSource);
    DYNACL_LOADFUNC(CLCREATEPROGRAMWITHBINARY_PTR, clCreateProgramWithBinary);
    DYNACL_LOADFUNC(CLRETAINPROGRAM_PTR, clRetainProgram);
    DYNACL_LOADFUNC(CLRELEASEPROGRAM_PTR, clReleaseProgram);
    DYNACL_LOADFUNC(CLBUILDPROGRAM_PTR, clBuildProgram);
    DYNACL_LOADFUNC(CLUNLOADCOMPILER_PTR, clUnloadCompiler);
    DYNACL_LOADFUNC(CLGETPROGRAMINFO_PTR, clGetProgramInfo);
    DYNACL_LOADFUNC(CLGETPROGRAMBUILDINFO_PTR, clGetProgramBuildInfo);
    DYNACL_LOADFUNC(CLCREATEKERNEL_PTR, clCreateKernel);
    DYNACL_LOADFUNC(CLCREATEKERNELSINPROGRAM_PTR, clCreateKernelsInProgram);
    DYNACL_LOADFUNC(CLRETAINKERNEL_PTR, clRetainKernel);
    DYNACL_LOADFUNC(CLRELEASEKERNEL_PTR, clReleaseKernel);
    DYNACL_LOADFUNC(CLSETKERNELARG_PTR, clSetKernelArg);
    DYNACL_LOADFUNC(CLGETKERNELINFO_PTR, clGetKernelInfo);
    DYNACL_LOADFUNC(CLGETKERNELWORKGROUPINFO_PTR, clGetKernelWorkGroupInfo);
    DYNACL_LOADFUNC(CLWAITFOREVENTS_PTR, clWaitForEvents);
    DYNACL_LOADFUNC(CLGETEVENTINFO_PTR, clGetEventInfo);
    DYNACL_LOADFUNC(CLCREATEUSEREVENT_PTR, clCreateUserEvent);
    DYNACL_LOADFUNC(CLRETAINEVENT_PTR, clRetainEvent);
    DYNACL_LOADFUNC(CLRELEASEEVENT_PTR, clReleaseEvent);
    DYNACL_LOADFUNC(CLSETUSEREVENTSTATUS_PTR, clSetUserEventStatus);
    DYNACL_LOADFUNC(CLSETEVENTCALLBACK_PTR, clSetEventCallback);
    DYNACL_LOADFUNC(CLGETEVENTPROFILINGINFO_PTR, clGetEventProfilingInfo);
    DYNACL_LOADFUNC(CLFLUSH_PTR, clFlush);
    DYNACL_LOADFUNC(CLFINISH_PTR, clFinish);
    DYNACL_LOADFUNC(CLENQUEUEREADBUFFER_PTR, clEnqueueReadBuffer);
    DYNACL_LOADFUNC(CLENQUEUEREADBUFFERRECT_PTR, clEnqueueReadBufferRect);
    DYNACL_LOADFUNC(CLENQUEUEWRITEBUFFER_PTR, clEnqueueWriteBuffer);
    DYNACL_LOADFUNC(CLENQUEUEWRITEBUFFERRECT_PTR, clEnqueueWriteBufferRect);
    DYNACL_LOADFUNC(CLENQUEUECOPYBUFFER_PTR, clEnqueueCopyBuffer);
    DYNACL_LOADFUNC(CLENQUEUECOPYBUFFERRECT_PTR, clEnqueueCopyBufferRect);
    DYNACL_LOADFUNC(CLENQUEUEREADIMAGE_PTR, clEnqueueReadImage);
    DYNACL_LOADFUNC(CLENQUEUEWRITEIMAGE_PTR, clEnqueueWriteImage);
    DYNACL_LOADFUNC(CLENQUEUECOPYIMAGE_PTR, clEnqueueCopyImage);
    DYNACL_LOADFUNC(CLENQUEUECOPYIMAGETOBUFFER_PTR, clEnqueueCopyImageToBuffer);
    DYNACL_LOADFUNC(CLENQUEUECOPYBUFFERTOIMAGE_PTR, clEnqueueCopyBufferToImage);
    DYNACL_LOADFUNC(CLENQUEUEMAPBUFFER_PTR, clEnqueueMapBuffer);
    DYNACL_LOADFUNC(CLENQUEUEMAPIMAGE_PTR, clEnqueueMapImage);
    DYNACL_LOADFUNC(CLENQUEUEUNMAPMEMOBJECT_PTR, clEnqueueUnmapMemObject);
    DYNACL_LOADFUNC(CLENQUEUENDRANGEKERNEL_PTR, clEnqueueNDRangeKernel);
    DYNACL_LOADFUNC(CLENQUEUETASK_PTR, clEnqueueTask);
    DYNACL_LOADFUNC(CLENQUEUENATIVEKERNEL_PTR, clEnqueueNativeKernel);
    DYNACL_LOADFUNC(CLENQUEUEMARKER_PTR, clEnqueueMarker);
    DYNACL_LOADFUNC(CLENQUEUEWAITFOREVENTS_PTR, clEnqueueWaitForEvents);
    DYNACL_LOADFUNC(CLENQUEUEBARRIER_PTR, clEnqueueBarrier);
    DYNACL_LOADFUNC(CLGETEXTENSIONFUNCTIONADDRESS_PTR, clGetExtensionFunctionAddress);
  #undef DYNACL_LOADFUNC

  return DYNACL_SUCCESS;
}

void dynacl_shutdown() {
  #define DYNACL_UNLOADFUNC(funcvar) funcvar = NULL
    DYNACL_UNLOADFUNC(clGetPlatformIDs);
    DYNACL_UNLOADFUNC(clGetPlatformInfo);
    DYNACL_UNLOADFUNC(clGetDeviceIDs);
    DYNACL_UNLOADFUNC(clGetDeviceInfo);
    DYNACL_UNLOADFUNC(clCreateContext);
    DYNACL_UNLOADFUNC(clCreateContextFromType);
    DYNACL_UNLOADFUNC(clRetainContext);
    DYNACL_UNLOADFUNC(clReleaseContext);
    DYNACL_UNLOADFUNC(clGetContextInfo);
    DYNACL_UNLOADFUNC(clCreateCommandQueue);
    DYNACL_UNLOADFUNC(clRetainCommandQueue);
    DYNACL_UNLOADFUNC(clReleaseCommandQueue);
    DYNACL_UNLOADFUNC(clGetCommandQueueInfo);
    #ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
      DYNACL_UNLOADFUNC(clSetCommandQueueProperty);
    #endif
    DYNACL_UNLOADFUNC(clCreateBuffer);
    DYNACL_UNLOADFUNC(clCreateSubBuffer);
    DYNACL_UNLOADFUNC(clCreateImage2D);
    DYNACL_UNLOADFUNC(clCreateImage3D);
    DYNACL_UNLOADFUNC(clRetainMemObject);
    DYNACL_UNLOADFUNC(clReleaseMemObject);
    DYNACL_UNLOADFUNC(clGetSupportedImageFormats);
    DYNACL_UNLOADFUNC(clGetMemObjectInfo);
    DYNACL_UNLOADFUNC(clGetImageInfo);
    DYNACL_UNLOADFUNC(clSetMemObjectDestructorCallback);
    DYNACL_UNLOADFUNC(clCreateSampler);
    DYNACL_UNLOADFUNC(clRetainSampler);
    DYNACL_UNLOADFUNC(clReleaseSampler);
    DYNACL_UNLOADFUNC(clGetSamplerInfo);
    DYNACL_UNLOADFUNC(clCreateProgramWithSource);
    DYNACL_UNLOADFUNC(clCreateProgramWithBinary);
    DYNACL_UNLOADFUNC(clRetainProgram);
    DYNACL_UNLOADFUNC(clReleaseProgram);
    DYNACL_UNLOADFUNC(clBuildProgram);
    DYNACL_UNLOADFUNC(clUnloadCompiler);
    DYNACL_UNLOADFUNC(clGetProgramInfo);
    DYNACL_UNLOADFUNC(clGetProgramBuildInfo);
    DYNACL_UNLOADFUNC(clCreateKernel);
    DYNACL_UNLOADFUNC(clCreateKernelsInProgram);
    DYNACL_UNLOADFUNC(clRetainKernel);
    DYNACL_UNLOADFUNC(clReleaseKernel);
    DYNACL_UNLOADFUNC(clSetKernelArg);
    DYNACL_UNLOADFUNC(clGetKernelInfo);
    DYNACL_UNLOADFUNC(clGetKernelWorkGroupInfo);
    DYNACL_UNLOADFUNC(clWaitForEvents);
    DYNACL_UNLOADFUNC(clGetEventInfo);
    DYNACL_UNLOADFUNC(clCreateUserEvent);
    DYNACL_UNLOADFUNC(clRetainEvent);
    DYNACL_UNLOADFUNC(clReleaseEvent);
    DYNACL_UNLOADFUNC(clSetUserEventStatus);
    DYNACL_UNLOADFUNC(clSetEventCallback);
    DYNACL_UNLOADFUNC(clGetEventProfilingInfo);
    DYNACL_UNLOADFUNC(clFlush);
    DYNACL_UNLOADFUNC(clFinish);
    DYNACL_UNLOADFUNC(clEnqueueReadBuffer);
    DYNACL_UNLOADFUNC(clEnqueueReadBufferRect);
    DYNACL_UNLOADFUNC(clEnqueueWriteBuffer);
    DYNACL_UNLOADFUNC(clEnqueueWriteBufferRect);
    DYNACL_UNLOADFUNC(clEnqueueCopyBuffer);
    DYNACL_UNLOADFUNC(clEnqueueCopyBufferRect);
    DYNACL_UNLOADFUNC(clEnqueueReadImage);
    DYNACL_UNLOADFUNC(clEnqueueWriteImage);
    DYNACL_UNLOADFUNC(clEnqueueCopyImage);
    DYNACL_UNLOADFUNC(clEnqueueCopyImageToBuffer);
    DYNACL_UNLOADFUNC(clEnqueueCopyBufferToImage);
    DYNACL_UNLOADFUNC(clEnqueueMapBuffer);
    DYNACL_UNLOADFUNC(clEnqueueMapImage);
    DYNACL_UNLOADFUNC(clEnqueueUnmapMemObject);
    DYNACL_UNLOADFUNC(clEnqueueNDRangeKernel);
    DYNACL_UNLOADFUNC(clEnqueueTask);
    DYNACL_UNLOADFUNC(clEnqueueNativeKernel);
    DYNACL_UNLOADFUNC(clEnqueueMarker);
    DYNACL_UNLOADFUNC(clEnqueueWaitForEvents);
    DYNACL_UNLOADFUNC(clEnqueueBarrier);
    DYNACL_UNLOADFUNC(clGetExtensionFunctionAddress);
  #undef DYNACL_UNLOADFUNC

  FreeLibrary(dynacl_dll);
  dynacl_dll = NULL;
}
