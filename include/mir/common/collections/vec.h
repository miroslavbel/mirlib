/**
 * \file
 *
 * \brief \ref MIR_Vec utilities
 */

#ifndef _MIR_COMMON_COLLECTIONS_VEC_H
#define _MIR_COMMON_COLLECTIONS_VEC_H


#include <stddef.h> /* NULL, size_t */
#if __STDC_VERSION__ >= 199901L
#    include <stdint.h> /* SIZE_MAX */
#else
#    include <mir/stdlib/stdint.h> /* SIZE_MAX */
#endif
#ifndef MIR_NO_STD_ALLOCATOR
#    include <stdlib.h> /* free, malloc */
#endif

#include <mir/common/arith.h>    /* MIR_u_Mul_WillOverflow */
#include <mir/internal/assert.h> /* __MIR_ASSERT_MSG */


/**
 * \brief Defines a dynamic size array struct - a vector.
 *
 * \param type      elements type. **MAY** consist of several tokens
 * \param structTag struct tag. **MAY** be empty if no struct tag is desired
 *
 * \note Be aware that prior to C99, the C standard did not specify behavior for
 * macros with empty arguments.
 *
 * \details Members:
 *   1. `data` - pointer to the first element of underlying array. **MAY** be
 *      `NULL`
 *   2. `len` - number of elements currently stored in the underlying array.
 *       **MAY** be `0`
 *   3. `cap` - capacity (in elements) of the underlying array. **MAY** be `0`
 *
 * Rules:
 *   1. `type`'s `sizeof` **MUST** be greater than `0`
 *   2. member `cap` **MUST** be always greater or equal to member `len`
 *   3. member `data` **MUST** be `NULL` only if member `cap` is equal to `0`.
 *      Member `data` **MUST NOT** be `NULL` if member `cap` is not equal to `0`
 *
 * ## Interface
 *
 * \note \ref MIR_Vec_InitWithCapacity, \ref MIR_Vec_Deinit, \ref
 * MIR_Vec_Reserve will be defined only if `MIR_NO_STD_ALLOCATOR` is not
 * defined.
 *
 * + initialization
 *   - \ref MIR_Vec_Init - with zero capacity
 *   - \ref MIR_Vec_InitWithCapacity - with given capacity by using standard
 *     library `realloc` function
 *   - \ref MIR_Vec_InitWithCapacityByReallocF - with given capacity by using
 *     provided realloc-like function
 * + reserve
 *   - \ref MIR_Vec_Reserve - by using standard library `realloc` function
 *   - \ref MIR_Vec_ReserveByReallocF - by using provided realloc-like function
 * + push_back
 *   - \ref MIR_Vec_Push - by using standard library `realloc` function
 *   - \ref MIR_Vec_PushByReallocF - by using provided realloc-like function
 * + deinitialization
 *   - \ref MIR_Vec_Deinit - by using standard library `free` function
 *   - \ref MIR_Vec_DeinitByFreeF - by using provided free-like function
 */
#define MIR_Vec(type, structTag)                                               \
    struct structTag {                                                         \
        type *data;                                                            \
        size_t len;                                                            \
        size_t cap;                                                            \
    }


#ifdef __cplusplus
extern "C" {
#endif


extern int __MIR_Vec_ReserveByReallocF_impl(
    void *(*realloc_f)(void *, size_t), void **member_data, size_t *member_cap,
    size_t capacity, size_t elemSize
);


#ifdef __cplusplus
}
#endif

/**
 * \brief Init vector with zero capacity.
 *
 * \param[out] vec pointer to \ref MIR_Vec struct
 */
#define MIR_Vec_Init(vec)                                                      \
    __MIR_ASSERT_MSG((vec) != NULL, "param `vec' MUST not be NULL");           \
    (vec)->data = NULL;                                                        \
    (vec)->len = 0;                                                            \
    (vec)->cap = 0

/**
 * \brief Reserves enough space to hold at least `new_capacity` items by using
 * provided realloc-like function.
 *
 * \details Does nothing if `new_capacity` is equal or less then `arr->cap`.
 *
 * \param         type          type of elements. **MUST** be the same type as
 *                              that passed to \ref MIR_Vec macro
 * \param[in]     reallocF      realloc-like function to be used
 * \param[in,out] vec           pointer to \ref MIR_Vec struct
 * \param         new_capacity  minimum new capacity
 *
 * \return `0` on success; any other number indicates failure
 */
#define MIR_Vec_ReserveByReallocF(type, reallocF, vec, new_capacity)           \
    /* clang-format off */                                                     \
    (                                                                          \
        (                                                                      \
            __MIR_ASSERT_MSG(                                                  \
                sizeof(type) > 0u, "`sizeof(type)' MUST be greater then 0"     \
            ),                                                                 \
            __MIR_ASSERT_MSG(                                                  \
                (reallocF) != NULL, "param `reallocF' MUST not be NULL"        \
            ),                                                                 \
            __MIR_ASSERT_MSG((vec) != NULL, "param `vec' MUST no be NULL"),    \
            __MIR_ASSERT_MSG(                                                  \
                ((vec)->cap == 0u) ? ((vec)->data == NULL) : 1,                \
                "if `vec->cap == 0' then `vec->data' MUST be NULL"             \
            )                                                                  \
        ),                                                                     \
        __MIR_Vec_ReserveByReallocF_impl(                                      \
            reallocF, (void **)&(vec)->data, &(vec)->cap,                      \
            new_capacity, sizeof(type)                                         \
        )                                                                      \
    ) /* clang-format on */

/**
 * \brief Inits \ref MIR_Vec struct with given capacity by using provided
 * realloc-like function.
 *
 * \param      type     type of elements. **MUST** be the same type as that
 *                      passed to \ref MIR_Vec macro
 * \param[in]  reallocF realloc-like function to be used
 * \param[out] vec      pointer to \ref MIR_Vec struct to be initalized
 * \param      capacity initial capacity
 *
 * \return `0` on success; any other number indicates failure
 */
#define MIR_Vec_InitWithCapacityByReallocF(type, reallocF, vec, capacity)      \
    /* clang-format off */                                                     \
    (                                                                          \
        (vec)->data = NULL,                                                    \
        (vec)->len = 0,                                                        \
        (vec)->cap = 0,                                                        \
        MIR_Vec_ReserveByReallocF(type, reallocF, vec, capacity)               \
    ) /* clang-format on */

/**
 * \brief Appends the given element to the end of the vector by using
 * provided realloc-like function.
 *
 * \param         type     type of elements. **MUST** be the same type as that
 *                         passed to \ref MIR_Vec macro
 * \param[in]     reallocF realloc-like function to be used
 * \param[in,out] vec      pointer to \ref MIR_Vec struct
 * \param         elem     pointer to the element to be appended. **MUST** point
 *                         to the same type as that passed to \ref MIR_Vec macro
 *
 * \return `0` on success; any other number indicates failure
 */
#define MIR_Vec_PushByReallocF(type, reallocF, vec, elem)                      \
    /* clang-format off */                                                     \
    (                                                                          \
        __MIR_ASSERT_MSG((elem) != NULL, "param `elem' MUST NOT be NULL"),     \
        (                                                                      \
            MIR_u_Mul_WillOverflow(                                            \
                (vec)->cap, 2u, SIZE_MAX                                       \
            )                                                                  \
                ? 1                                                            \
                :                                                              \
                    (                                                          \
                        MIR_Vec_ReserveByReallocF(                             \
                            type, reallocF, vec,                               \
                            ((vec)->cap == 0u) ? 1u : ((vec)->cap * 2u)        \
                        )                                                      \
                        == 1                                                   \
                    )                                                          \
        )                                                                      \
            ? 1                                                                \
            :                                                                  \
                (                                                              \
                    (vec)->data[(vec)->len] = *(elem),                         \
                    ++((vec)->len),                                            \
                    0                                                          \
                )                                                              \
    ) /* clang-format on */

/**
 * \brief Deinits the \ref MIR_Vec struct by using provided free-like function.
 *
 * \details Frees the memory using free-like function.
 *
 * \warning It only frees the memory. It does not update the struct members.
 *
 * \param[in] freeF free-like function to be used
 * \param[in] vec   pointer to \ref MIR_Vec struct to be deinitialized
 */
#define MIR_Vec_DeinitByFreeF(freeF, vec)                                      \
    /* clang-format off */                                                     \
    (                                                                          \
        (                                                                      \
            __MIR_ASSERT_MSG(                                                  \
                (freeF) != NULL,                                               \
                "param `freeF' MUST not be NULL"                               \
            ),                                                                 \
            __MIR_ASSERT_MSG(                                                  \
                (vec) != NULL,                                                 \
                "param `vec' MUST not be NULL"                                 \
            ),                                                                 \
            __MIR_ASSERT_MSG(                                                  \
                ((vec)->cap == 0u) ? ((vec)->data == NULL) : 1,                \
                "if `vec->cap == 0' then `vec->data' MUST be NULL"             \
            )                                                                  \
        ),                                                                     \
        /* NOTE: it's okay to pass NULL to free function */                    \
        (freeF)((vec)->data)                                                   \
    ) /* clang-format on */


#ifndef MIR_NO_STD_ALLOCATOR

/**
 * \brief Reserves enough space to hold at least `new_capacity` items by using
 * standard library `realloc` function.
 *
 * \note This macros will be defined only if `MIR_NO_STD_ALLOCATOR` is not
 * defined
 *
 * \param         type          type of elements. **MUST** be the same type as
 *                              that passed to \ref MIR_Vec macro. `type`'s
 *                              `sizeof` **MUST** be greater than `0`
 * \param[in,out] vec           pointer to \ref MIR_Vec struct
 * \param         new_capacity  minimum new capacity
 *
 * \return `0` on success; any other number indicates failure
 */
#    define MIR_Vec_Reserve(type, vec, new_capacity)                           \
        MIR_Vec_ReserveByReallocF(type, realloc, vec, new_capacity)

/**
 * \brief Inits \ref MIR_Vec struct with given capacity by using standard
 * library `realloc` function.
 *
 * \note This macros will be defined only if `MIR_NO_STD_ALLOCATOR` is not
 * defined
 *
 * \param      type     type of elements. **MUST** be the same type as that
 *                      passed to \ref MIR_Vec macro
 * \param[out] vec      pointer to \ref MIR_Vec struct to be initalized
 * \param      capacity initial capacity
 *
 * \return `0` on success; any other number indicates failure
 */
#    define MIR_Vec_InitWithCapacity(type, vec, capacity)                      \
        MIR_Vec_InitWithCapacityByReallocF(type, realloc, vec, capacity)

/**
 * \brief Appends the given element to the end of the vector by using standard
 * library `realloc` function.
 *
 * \note This macros will be defined only if `MIR_NO_STD_ALLOCATOR` is not
 * defined
 *
 * \param         type type of elements. **MUST** be the same type as that
 *                     passed to \ref MIR_Vec macro
 * \param[in,out] vec  pointer to \ref MIR_Vec struct
 * \param         elem pointer to the element to be appended. **MUST** point
 *                     to the same type as that passed to \ref MIR_Vec macro
 *
 * \return `0` on success; any other number indicates failure
 */
#    define MIR_Vec_Push(type, vec, elem)                                      \
        MIR_Vec_PushByReallocF(type, realloc, vec, elem)

/**
 * \brief Deinits the \ref MIR_Vec struct
 *
 * \note This macros will be defined only if `MIR_NO_STD_ALLOCATOR` is not
 * defined
 *
 * \details Frees the memory using standard library `free` function.
 *
 * \warning It only frees the memory. It does not update the struct members.
 *
 * \param[in] vec pointer to \ref MIR_Vec struct to be deinitialized
 */
#    define MIR_Vec_Deinit(vec) MIR_Vec_DeinitByFreeF(free, vec)

#endif /* MIR_NO_STD_ALLOCATOR */


#endif /* _MIR_COMMON_COLLECTIONS_VEC_H */
