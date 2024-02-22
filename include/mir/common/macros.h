/**
 * \file
 * 
 * \brief Highly-used macros
 */

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
