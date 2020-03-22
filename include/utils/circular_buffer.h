#ifndef UTILS_CIRCULAR_BUFFER_H
#define UTILS_CIRCULAR_BUFFER_H

/**
 * @brief Computes a pointer to an element offset from a pointer in a circular
 *        buffer
 * @param bufferStart The pointer to the start of the buffer
 * @param bufferLength The length of the buffer
 * @param stride The number of bytes in each element of the buffer
 * @param pointer The base of the offset
 * @param offset The distance of the offset
 * @return a pointer to the offset value
 */
void* circularBufferOffset(void* bufferStart,
                         int bufferLength,
                         int stride,
                         void* pointer,
                         int offset);

#endif

