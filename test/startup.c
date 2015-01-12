#include <windows.h>
#include <CL/dynacl.h>
#include <stdio.h>

#define DLL_PATH "C:\\Program Files\\NVIDIA Corporation\\OpenCL\\OpenCL64.dll"

/*
 * usage
 *    CHAR msgText[256];
 *    getLastErrorText(msgText,sizeof(msgText));
 */
static CHAR * getLastErrorText(CHAR *pBuf, ULONG bufSize);

int main(int argc, char** argv) {
  unsigned int err;

  puts("Initializing DynaCL...");
  err = dynacl_init(TEXT(DLL_PATH));
  if(err != DYNACL_SUCCESS) {
    CHAR msg[1024];
    printf("dynacl_init() returned error %u.\n", err);
    printf("%s\n", getLastErrorText(msg, 1024));
    
    return 1;
  } else puts("dynacl_init() returned success.");

  puts("Shutting down DynaCL...");
  dynacl_shutdown();

  puts("Quitting...");
  return 0;
}

static CHAR *                      //   return error message
getLastErrorText(                  // converts "Lasr Error" code into text
CHAR *pBuf,                        //   message buffer
ULONG bufSize)                     //   buffer size
{
     DWORD retSize;
     LPTSTR pTemp=NULL;

     if (bufSize < 16) {
          if (bufSize > 0) {
               pBuf[0]='\0';
          }
          return(pBuf);
     }
     retSize=FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
                           FORMAT_MESSAGE_FROM_SYSTEM|
                           FORMAT_MESSAGE_ARGUMENT_ARRAY,
                           NULL,
                           GetLastError(),
                           LANG_NEUTRAL,
                           (LPTSTR)&pTemp,
                           0,
                           NULL );
     if (!retSize || pTemp == NULL) {
          pBuf[0]='\0';
     }
     else {
          pTemp[strlen(pTemp)-2]='\0'; //remove cr and newline character
          sprintf(pBuf,"%0.*s (0x%x)",bufSize-16,pTemp,GetLastError());
          LocalFree((HLOCAL)pTemp);
     }
     return(pBuf);
}
