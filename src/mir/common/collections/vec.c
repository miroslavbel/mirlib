#include <mir/common/collections/vec.h>


#include <stddef.h> /* NULL, size_t */
#if __STDC_VERSION__ >= 199901L
#    include <stdint.h> /* SIZE_MAX */
#endif

#include <mir/common/arith.h> /* MIR_u_Mul_WillOverflow */


/**
 * \brief Reserves enough space to hold at least `new_capacity` items using
 * giving realloc-like function.
 *
 * \details Does nothing if `new_capacity` is equal or less then `*member_cap`.
 *
 * \param[in]     realloc_f    realloc-like function to be used
 * \param[in,out] member_data  pointer to `data` member
 * \param[in,out] member_cap   pointer to `cap` member
 * \param         new_capacity new capacity. **MAY** be `0`
 * \param         elemSize     size of element. **MUST** be greater then `0`
 *
 * \return `0` on success; any other number indicates failure
 */
int __MIR_Vec_ReserveByReallocF_impl(
    void *(*realloc_f)(void *, size_t), void **member_data, size_t *member_cap,
    size_t new_capacity, size_t elemSize
) {

    void *new_ptr;
    size_t new_size;

    if (new_capacity <= *member_cap) {
        return 0;
    }

    if (MIR_u_Mul_WillOverflow(new_capacity, elemSize, SIZE_MAX) != 0) {
        return 1;
    }
    new_size = new_capacity * elemSize;

    /* NOTE: the behavior of `realloc(.., 0)` is implementation defined (prior
     *       to C23) or even undefined (since C23). At this point we know:
     *         1. `elemSize > 0` (by user)
     *         2. `new_capacity > 0` as `new_capacity > *member_cap` and
     *            `*member_cap >= 0`
     *       So we know that `new_size > 0` and it can be passed to realloc
     *
     * NOTE: the behavior of `realloc(NULL, ..)` is the same as calling
     *       `malloc(new_size)`
     */
    new_ptr = realloc_f(*member_data, new_size);
    if (new_ptr == NULL) {
        return 1;
    }

    *member_data = new_ptr;
    *member_cap = new_capacity;
    return 0;
}
