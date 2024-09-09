#ifndef _MIR_INTERNAL_ASSERT_H
#define _MIR_INTERNAL_ASSERT_H


#include <mir/common/assert.h>


#if defined(NDEBUG) || defined(MIR_NDEBUG)
#    define __MIR_ASSERT(expr) ((void)0)
#    define __MIR_ASSERT_MSG(expr, msg) ((void)0)
#else
#    define __MIR_ASSERT(expr) _MIR_ASSERT(expr)
#    define __MIR_ASSERT_MSG(expr, msg) _MIR_ASSERT_MSG(expr, msg)
#endif


#endif /* _MIR_INTERNAL_ASSERT_H */
