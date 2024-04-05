#ifndef _MIR_COMMON_ASSERT_H
#define _MIR_COMMON_ASSERT_H

/**
 * \file
 *
 * \brief Assert macros
 *
 * \details See:
 * + #_MIR_ASSERT
 * + #_MIR_ASSERT_MSG
 */

#include <assert.h>

/**
 * \brief Simple wrapper around `assert`.
 *
 * \note The reason why this macro starts with an underscore is because it is recommended that one
 * should create a custom macro for one's project, which will be expanded into this macro. This way
 * it will be possible to disable asserts for the particular project. This can be useful for
 * projects with heavy calculations, for example.
 *
 * \code{.c}
 * #ifdef PROJECT_NAME_NDEBUG
 *
 * // Here we give one the ability to disable asserts for the particular project without disabling
 * // asserts for other projects (i.e. without defining `NDEBUG` globally)
 * #define PROJECT_NAME_ASSERT(expr) ((void)0)
 *
 * #else
 *
 * // The default case: this is expanded into `assert`, and depends only on `NDEBUG`
 * #define PROJECT_NAME_ASSERT(expr) _MIR_ASSERT(expr)
 *
 * #endif
 * \endcode
 *
 * \param expr expression
 *
 * \sa _MIR_ASSERT_MSG
 */
#define _MIR_ASSERT(expr) assert(expr)

/**
 * \brief Simple wrapper around `assert`.
 *
 * \note The reason why this macro starts with an underscore is because it is recommended that one
 * should create a custom macro for one's project, which will be expanded into this macro. This way
 * it will be possible to disable asserts for the particular project. This can be useful for
 * projects with heavy calculations, for example.
 *
 * \code{.c}
 * #ifdef PROJECT_NAME_NDEBUG
 *
 * // Here we give one the ability to disable asserts for the particular project without disabling
 * // asserts for other projects (i.e. without defining `NDEBUG` globally)
 * #define PROJECT_NAME_ASSERT_MSG(expr, msg) ((void)0)
 *
 * #else
 *
 * // The default case: this is expanded into `assert`, and depends only on `NDEBUG`
 * #define PROJECT_NAME_ASSERT_MSG(expr, msg) _MIR_ASSERT_MSG(expr, msg)
 *
 * #endif
 * \endcode
 *
 * \param expr expression
 * \param msg  message
 *
 * \sa #_MIR_ASSERT
 */
#define _MIR_ASSERT_MSG(expr, msg) assert((expr) && (msg))

#endif /* _MIR_COMMON_ASSERT_H */
