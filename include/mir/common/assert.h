#ifndef _MIR_COMMON_ASSERT_H
#define _MIR_COMMON_ASSERT_H

#include <assert.h>

/**
 * \brief Simple wrapper around `assert`.
 *
 * \param expr expression
 */
#define MIR_ASSERT(expr) assert(expr)

/**
 * \brief Simple wrapper around `assert`.
 *
 * \param expr expression
 * \param msg  message
 */
#define MIR_ASSERT_MSG(expr, msg) assert((expr) && (msg))

#endif /* _MIR_COMMON_ASSERT_H */
