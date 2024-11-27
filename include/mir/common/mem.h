/**
 * \file
 *
 * \brief Memory routines
 */


#ifndef _MIR_COMMON_MEM_H_
#define _MIR_COMMON_MEM_H_


#include <stddef.h> /* size_t */


/**
 * \brief Realloc-like function that always fails.
 *
 * \return It always returns \c NULL.
 */
void *MIR_FailRealloc(void *__ptr, size_t __newSize);


#endif /* _MIR_COMMON_MEM_H_ */
