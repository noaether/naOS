#ifndef STDRETURN_H
#define STDRETURN_H

#define SUCCESS 0
#define ERROR_UNKNOWN 1
#define ERROR_OUT_OF_MEMORY 2
#define ERROR_INVALID_ARGUMENT 3
#define ERROR_NOT_IMPLEMENTED 4
#define ERROR_FILE_NOT_FOUND 5
#define ERROR_PERMISSION_DENIED 6
#define ERROR_BUFFER_SIZE_TOO_SMALL 7

typedef struct ReturnCode {
  int code;
  void *ptr;
} naOSReturnCode;

// Define a macro to combine an error code and a pointer into a single value
#define RETURN_WITH_PTR(code, ptr) ((struct ReturnCode){code, ptr})

// Define a macro to extract the error code from the combined value
#define RETURN_CODE(code) (code.code)

// Define a macro to extract the pointer from the combined value
#define RETURN_PTR(code) (code.ptr)

#endif
