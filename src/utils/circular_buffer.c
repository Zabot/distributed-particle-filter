#include "utils/circular_buffer.h"


void* circularBufferOffset(void* bufferStart,
                         int bufferLength,
                         int stride,
                         void* pointer,
                         int offset) {
  offset *= stride;
  bufferLength *= stride;
  int unwrapped = ((pointer - bufferStart) + offset);

  if (unwrapped < 0)
    return bufferStart
      + (bufferLength - (-unwrapped % bufferLength)) % bufferLength;
  else
    return bufferStart + unwrapped % bufferLength;
}

