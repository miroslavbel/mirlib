/**
 * \file
 *
 * \brief Backport of `stdint.h`
 *
 * \details Tries to backport C23 standard library `stdint.h` header.
 *
 * ## Integer types
 *
 * Not implemented.
 *
 *
 * ## Widths of specified-width integer types
 *
 * Not implemented.
 *
 *
 * ## Width of other integer types
 *
 * The following macros are defined (if they were not previously defined) using
 * predefined macros available in GCC 7.1 and later or Clang 3.0 and later. For
 * GCC see [Common Predefined
 * Macros](https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html) for
 * reference.
 *
 * + `PTRDIFF_WIDTH` - `__PTRDIFF_WIDTH__`
 * + `SIG_ATOMIC_WIDTH` - `__SIG_ATOMIC_WIDTH__`
 * + `SIZE_WIDTH` - `__SIZE_WIDTH__`
 * + `WCHAR_WIDTH` - `__WCHAR_WIDTH__`
 * + `WINT_WIDTH` - `__WINT_WIDTH__`
 *
 *
 * ## Limits of specified-width integer types
 *
 * Not implemented.
 *
 *
 * ## Limits of other integer types
 *
 * The following macros are defined (if they were not previously defined) using
 * predefined macros available in GCC and Clang. For GCC see [Common Predefined
 * Macros](https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html) for
 * reference.
 *
 * + `PTRDIFF_MAX` - `__PTRDIFF_MAX__` (gcc >= 4.5, clang >= 3.5)
 * + `PTRDIFF_MIN` - no known way to implement it
 * + `SIG_ATOMIC_MAX` - `__SIG_ATOMIC_MAX__` (gcc >= 4.5, clang >= 3.5)
 * + `SIG_ATOMIC_MIN` - `__SIG_ATOMIC_MIN__` (gcc >= 4.5)
 * + `SIZE_MAX` - `__SIZE_MAX__` (gcc >= 4.5, clang >= 3.3)
 * + `WCHAR_MAX` - `__WCHAR_MAX__` (gcc >= 3.4, clang >= 3.0)
 * + `WCHAR_MIN` - `__WCHAR_MIN__` (gcc >= 4.5)
 * + `WINT_MAX` - `__WINT_MAX__` (gcc >= 4.5, clang >= 6.0)
 * + `WINT_MIN` - `__WINT_MIN__` (gcc >= 4.5)
 *
 *
 * ## Macros for integer constant
 *
 * Not implemented.
 */


#ifndef _MIR_STDLIB_STDINT_H
#define _MIR_STDLIB_STDINT_H


#if __STDC_VERSION__ >= 199901L
#    include <stdint.h>
#endif


/*******************************************************************************
 * Width of other integer types
 ******************************************************************************/

#ifndef PTRDIFF_WIDTH
#    ifdef __PTRDIFF_WIDTH__
#        define PTRDIFF_WIDTH __PTRDIFF_WIDTH__
#    endif
#endif

#ifndef SIG_ATOMIC_WIDTH
#    ifdef __SIG_ATOMIC_WIDTH__
#        define SIG_ATOMIC_WIDTH __SIG_ATOMIC_WIDTH__
#    endif
#endif

#ifndef SIZE_WIDTH
#    ifdef __SIZE_WIDTH__
#        define SIZE_WIDTH __SIZE_WIDTH__
#    endif
#endif

#ifndef WCHAR_WIDTH
#    ifdef __WCHAR_WIDTH__
#        define WCHAR_WIDTH __WCHAR_WIDTH__
#    endif
#endif

#ifndef WINT_WIDTH
#    ifdef __WINT_WIDTH__
#        define WINT_WIDTH __WINT_WIDTH__
#    endif
#endif


/*******************************************************************************
 * Limits of other integer types
 ******************************************************************************/

#ifndef SIZE_MAX
#    ifdef __SIZE_MAX__
#        define SIZE_MAX __SIZE_MAX__
#    endif
#endif

#ifndef PTRDIFF_MAX
#    ifdef __PTRDIFF_MAX__
#        define PTRDIFF_MAX __PTRDIFF_MAX__
#    endif
#endif

#ifndef SIG_ATOMIC_MIN
#    ifdef __SIG_ATOMIC_MIN__
#        define SIG_ATOMIC_MIN __SIG_ATOMIC_MIN__
#    endif
#endif

#ifndef SIG_ATOMIC_MAX
#    ifdef __SIG_ATOMIC_MAX__
#        define SIG_ATOMIC_MAX __SIG_ATOMIC_MAX__
#    endif
#endif

#ifndef WINT_MIN
#    ifdef __WINT_MIN__
#        define WINT_MIN __WINT_MIN__
#    endif
#endif

#ifndef WINT_MAX
#    ifdef __WINT_MAX__
#        define WINT_MAX __WINT_MAX__
#    endif
#endif

#ifndef WCHAR_MIN
#    ifdef __WCHAR_MIN__
#        define WCHAR_MIN __WCHAR_MIN__
#    endif
#endif

#ifndef WCHAR_MAX
#    ifdef __WCHAR_MAX__
#        define WCHAR_MAX __WCHAR_MAX__
#    endif
#endif


#endif /* _MIR_STDLIB_STDINT_H */
