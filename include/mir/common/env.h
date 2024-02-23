#ifndef _MIR_COMMON_ENV_H
#define _MIR_COMMON_ENV_H

/**
 * \file
 *
 * \brief Detecting compiler environment.
 *
 * \details Tries to detect the compiler and define one of the following macros:
 * + \ref MIR_COMPILER_MSVC "MIR_COMPILER_MSVC" - for [Microsoft Visual C/C++
 * compiler](https://en.wikipedia.org/wiki/Microsoft_Visual_C)
 * + \ref MIR_COMPILER_GCC "MIR_COMPILER_GCC" - for [GNU Compiler
 * Collection](https://en.wikipedia.org/wiki/GNU_Compiler_Collection)
 * + \ref MIR_COMPILER_CLANG "MIR_COMPILER_CLANG" - for [Clang](https://en.wikipedia.org/wiki/Clang)
 * compiler
 * + \ref MIR_COMPILER_TCC "MIR_COMPILER_TCC" - for [Tiny C
 * Compiler](https://en.wikipedia.org/wiki/Tiny_C_Compiler)
 */

#if !defined(MIR_COMPILER_MSVC) && !defined(MIR_COMPILER_GCC) && !defined(MIR_COMPILER_CLANG) &&   \
    !defined(MIR_COMPILER_TCC)

#    ifdef _MSC_VER
/**
 * \def MIR_COMPILER_MSVC
 *
 * \brief Microsoft Visual C/C++ compiler.
 *
 * \sa
 * + [Wikipedia](https://en.wikipedia.org/wiki/Microsoft_Visual_C)
 */
#        define MIR_COMPILER_MSVC 1

#    elif defined(__TINYC__)
/**
 * \def MIR_COMPILER_TCC
 *
 * \brief Tiny C Compiler.
 *
 * \sa
 * + [Wikipedia](https://en.wikipedia.org/wiki/Tiny_C_Compiler)
 * + [site](https://bellard.org/tcc)
 */
#        define MIR_COMPILER_TCC 1

#    elif defined(__clang__)
/**
 * \def MIR_COMPILER_CLANG
 *
 * \brief Clang compiler.
 *
 * \sa
 * + [Wikipedia](https://en.wikipedia.org/wiki/Clang)
 * + [site](https://clang.llvm.org)
 */
#        define MIR_COMPILER_CLANG 1

#    elif defined(__GNUC__)
/**
 * \def MIR_COMPILER_GCC
 *
 * \brief GNU Compiler Collection.
 *
 * \sa
 * + [Wikipedia](https://en.wikipedia.org/wiki/GNU_Compiler_Collection)
 * + [site](https://gcc.gnu.org)
 */
#        define MIR_COMPILER_GCC 1

#    endif

#endif

#endif /* _MIR_COMMON_ENV_H */
