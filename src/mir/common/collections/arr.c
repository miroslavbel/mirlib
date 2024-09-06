#include <mir/common/collections/arr.h>


#include <stddef.h> /* NULL, size_t */
#if __STDC_VERSION__ >= 199901L
#    include <stdint.h> /* SIZE_MAX  */
#else
#    include <mir/stdlib/stdint.h> /* SIZE_MAX */
#endif

#include <mir/common/arith.h> /* MIR_u_Mul_WillOverflow */


/**
 * \brief Inits \ref MIR_Arr by calling provided malloc-like function.
 *
 * \param[in]  malloc_f    malloc-like function to be used as an allocator
 * \param[out] member_data pointer to `data` member
 * \param[out] member_len  pointer to `len` member
 * \param      length      number of elements in array. **MAY** be `0`
 * \param      elemSize    size of element. **MAY** be `0`
 *
 * \return `0` if succeed, `1` otherwise
 */
int __MIR_Arr_InitByMallocF_impl(
    void *(*malloc_f)(size_t), void const **member_data, size_t *member_len,
    size_t length, size_t elemSize
) {
    void const *ptr;
    size_t alloc_size;

    if (MIR_u_Mul_WillOverflow(length, elemSize, SIZE_MAX) != 0) {
        return 1;
    }

    /* NOTE: malloc-like function can return non-NULL pointer even if the size
     *       is 0 */
    alloc_size = length * elemSize;
    if (alloc_size == 0u) {
        *member_data = NULL;
        *member_len = 0;
        return 0;
    }

    ptr = malloc_f(alloc_size);
    if (ptr == NULL) {
        return 1;
    }

    *member_data = ptr;
    *member_len = length;

    return 0;
}

/**
 * \brief Deinits \ref MIR_Arr by calling provided free-like function.
 *
 * \param[in,out] member_data pointer to `data` member
 * \param[out]    member_len  pointer to `len` member
 * \param[in]     freeF       free-like function
 *
 * \warning If `*member_len` is equal to `0` then `*member_data` **MUST** be
 * `NULL`.
 */
void __MIR_Arr_DeinitByFreeF_impl(
    void **member_data, size_t *member_len, void (*freeF)(void *)
) {
    /* NOTE: since it is guaranteed by the user that if `*member_len == 0`, then
     *       `*member_data == NULL`, there is no need to check for `len == 0`.
     *       A free-like function is guaranteed to do nothing when `NULL` is
     *       passed as an argument. */
    freeF(*member_data);

    *member_data = NULL;
    *member_len = 0;
}
