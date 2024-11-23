/**
 * \file
 * 
 * \brief Highly-used macros
 */


#ifndef _MIR_COMMON_MACROS_H_
#define _MIR_COMMON_MACROS_H_


/**
 * \brief Checks that \a x is in the range `[min..max]` (both inclusive).
 *
 * \param x   value to check
 * \param min minumum value (inclusive)
 * \param max maximum value (inclusive)
 *
 * \return \a 1 if \a x is in range, \a 0 otherwise
 */
#define MIR_InRange(x, min, max) ((min) <= (x) && (x) <= (max))

/**
 * \brief Iterates through a range of elements within an array.
 *
 * \param[in,out] arr  array to iterate over
 * \param         from starting index of the range (inclusive)
 * \param         to   ending index of the range (exclusive)
 * \param[out]    i    writes the current element index here
 * \param[out]    elem writes the pointer to the current element here
 *
 * ### Example
 *
 * This example will print `"1 2 "`:
 * \code{.c}
 * #include <stdio.h>
 *
 * size_t i;
 * int *elem;
 * int buf[5] = {0, 1, 2, 3, 4};
 *
 * MIR_FOREACH_RANGE (buf, 1, 3, &i, &elem) {
 *     printf("%d ", *elem);
 * }
 * \endcode
 */
#define MIR_FOREACH_RANGE(arr, from, to, i, elem)                                                  \
    for (*(i) = (from); *(elem) = &(arr)[*(i)], *(i) < (to); ++*(i))

/**
 * \brief Iterates over an array.
 *
 * \param[in,out] arr  array to iterate over
 * \param         len  array length
 * \param[out]    i    writes the current element index here
 * \param[out]    elem writes the pointer to the current element here
 *
 * ### Example
 *
 * This example will print `"0 1 2 "`:
 * \code{.c}
 * #include <stdio.h>
 *
 * size_t i;
 * int *elem;
 * int buf[3] = {0, 1, 2};
 *
 * MIR_FOREACH (buf, 3, &i, &elem) {
 *     printf("%d ", *elem);
 * }
 * \endcode
 */
#define MIR_FOREACH(arr, len, i, elem) MIR_FOREACH_RANGE (arr, 0, len, i, elem)


#endif /* _MIR_COMMON_MACROS_H_ */
