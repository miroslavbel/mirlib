/**
 * \file
 *
 * \brief \ref MIR_Arr utilities
 */


#ifndef _MIR_COMMON_COLLECTIONS_ARR_H
#define _MIR_COMMON_COLLECTIONS_ARR_H


#include <stddef.h> /* NULL, size_t */
#ifndef MIR_NO_STD_ALLOCATOR
#    include <stdlib.h> /* free, malloc */
#endif

#include <mir/internal/assert.h> /* __MIR_ASSERT_MSG */


/**
 * \brief Defines a struct that holds a pointer to the first element of an array
 * and the array's length
 *
 * \param type      elements type. **MAY** consist of several tokens
 * \param structTag struct tag. **MAY** be empty if no struct tag is desired
 *
 * \note Be aware that prior to C99, the C standard did not specify behavior for
 * macros with empty arguments.
 *
 * \details This macro does not enforce any additional semantics. For example,
 * the array can be a slice of another array and it does not enforce the
 * allocation location of the array - whether on the heap, stack, read-only
 * segment, or elsewhere.
 *
 * \warning If member `len` is equal to `0` then member `data` **MUST** be
 * `NULL`.
 *
 * ## Interface
 *
 * \note \ref MIR_Arr_Init, \ref MIR_Arr_Deinit will be defined only if
 * `MIR_NO_STD_ALLOCATOR` is not defined.
 *
 * + initialization
 *   - \ref MIR_Arr_Init - by standard library `malloc` function
 *   - \ref MIR_Arr_InitByMallocF - by given malloc-like function
 * + get
 *   - \ref MIR_Arr_Get - the element
 *   - \ref MIR_Arr_GetPtr - a pointer to the element
 * + set
 *   - \ref MIR_Arr_Set - the element
 * + deinitialization
 *   - \ref MIR_Arr_Deinit - by standard library `free` function
 *   - \ref MIR_Arr_DeinitByFreeF - by given free-like function
 */
#define MIR_Arr(type, structTag)                                               \
    struct structTag {                                                         \
        type *data;                                                            \
        size_t len;                                                            \
    }

/**
 * \brief A constant indicating a successful operation on the \ref MIR_Arr
 * struct.
 */
#define MIR_Arr_OK 0


#ifdef __cplusplus
extern "C" {
#endif


extern int __MIR_Arr_InitByMallocF_impl(
    void *(*malloc_f)(size_t), void const **member_data, size_t *member_len,
    size_t length, size_t elemSize
);

extern void __MIR_Arr_DeinitByFreeF_impl(
    void **member_data, size_t *member_len, void (*freeF)(void *)
);


#ifdef __cplusplus
}
#endif


/**
 * \brief Returns the element at the specified index.
 *
 * \param[in] arr   pointer to \ref MIR_Arr struct
 * \param     index index of the element to be returned
 *
 * \return element at the specified index
 */
#define MIR_Arr_Get(arr, index)                                                \
    /* clang-format off */                                                     \
    (                                                                          \
        __MIR_ASSERT_MSG(                                                      \
            (index) < (arr)->len,                                              \
            "OOB: param `index' MUST be less than (arr)->len"                  \
        ),                                                                     \
        (arr)->data[(index)]                                                   \
    ) /* clang-format on */

/**
 * \brief Returns a pointer to the element at the specified index.
 *
 * \param[in] arr   pointer to \ref MIR_Arr struct
 * \param     index index of the element whose pointer is to be returned
 *
 * \return pointer to the element at the specified index
 */
#define MIR_Arr_GetPtr(arr, index)                                             \
    /* clang-format off */                                                     \
    (                                                                          \
        __MIR_ASSERT_MSG(                                                      \
            (index) < (arr)->len,                                              \
            "OOB: param `index' MUST be less than (arr)->len"                  \
        ),                                                                     \
        &(arr)->data[(index)]                                                  \
    ) /* clang-format on */

/**
 * \brief Sets the element at the specified index.
 *
 * \param[out] arr   pointer to \ref MIR_Arr struct
 * \param      index index of the element to be set
 * \param      elem  element to set at the specified index
 */
#define MIR_Arr_Set(arr, index, elem)                                          \
    /* clang-format off */                                                     \
    (                                                                          \
        __MIR_ASSERT_MSG(                                                      \
            (index) < (arr)->len,                                              \
            "OOB: param `index' MUST be less than (arr)->len"                  \
        ),                                                                     \
        (arr)->data[(index)] = (elem)                                          \
    ) /* clang-format on */

/**
 * \brief Inits \ref MIR_Arr struct using giving malloc-like function as an
 * allocator.
 *
 * \param      type    type of elements. **MUST** be the same type as that
 *                     passed to \ref MIR_Arr macro. `type`'s `sizeof` **MUST**
 *                     be greater than `0`
 * \param      mallocF malloc-like function
 * \param[out] arr     pointer to \ref MIR_Arr struct to be initialized
 * \param      length  number of elements in the array. **MAY** be `0`
 *
 * \return \ref MIR_Arr_OK on success; any other value indicates failure
 */
#define MIR_Arr_InitByMallocF(type, mallocF, arr, length)                      \
    /* clang-format off */                                                     \
    (                                                                          \
        (                                                                      \
            __MIR_ASSERT_MSG(                                                  \
                sizeof(type) > 0u,                                             \
                "`sizeof(type)' MUST be greater than 0"                        \
            ),                                                                 \
            __MIR_ASSERT_MSG((arr) != NULL, "param `arr' MUST NOT be NULL"),   \
            __MIR_ASSERT_MSG(                                                  \
                (mallocF) != NULL,                                             \
                "param `mallocF' MUST NOT be NULL"                             \
            )                                                                  \
        ),                                                                     \
        __MIR_Arr_InitByMallocF_impl(                                          \
            (mallocF), (void **)&(arr)->data, &(arr)->len,                     \
            (length), sizeof(type)                                             \
        )                                                                      \
    ) /* clang-format on */

/**
 * \brief Deinits \ref MIR_Arr struct using giving free-like function as a
 * deallocator.
 *
 * \param[in]     freeF free-like function
 * \param[in,out] arr   pointer to \ref MIR_Arr struct to be deinitialized
 *
 * \warning If `arr->len` is equal to `0` then `arr->data` **MUST** be `NULL`
 */
#define MIR_Arr_DeinitByFreeF(freeF, arr)                                      \
    /* clang-format off */                                                     \
    (                                                                          \
        (                                                                      \
            __MIR_ASSERT_MSG((freeF) != NULL, "param `freeF' MUST no be NULL"),\
            __MIR_ASSERT_MSG((arr) != NULL, "param `arr' MUST not be NULL"),   \
            __MIR_ASSERT_MSG(                                                  \
                (arr)->len == 0 ? (void *)(arr)->data == NULL : 1,             \
                "if `arr->len == 0' then `arr->data' MUST be NULL"             \
            )                                                                  \
        ),                                                                     \
        __MIR_Arr_DeinitByFreeF_impl(                                          \
            (void **)&(arr)->data,                                             \
            &(arr)->len,                                                       \
            (freeF)                                                            \
        )                                                                      \
    ) /* clang-format on */


#ifndef MIR_NO_STD_ALLOCATOR

/**
 * \brief Inits \ref MIR_Arr struct using standard library `malloc` function as
 * an allocator.
 *
 * \param      type   type of elements. **MUST** be the same type as that passed
 *                    to \ref MIR_Arr macro. `type`'s `sizeof` **MUST** be
 *                    greater than `0`
 * \param[out] arr    pointer to \ref MIR_Arr struct to be initialized
 * \param      length number of elements in the array. **MAY** be `0`
 *
 * \return \ref MIR_Arr_OK on success; any other value indicates failure
 *
 * \note This macros will be defined only if `MIR_NO_STD_ALLOCATOR` is not
 * defined
 */
#    define MIR_Arr_Init(type, arr, length)                                    \
        /* clang-format off */                                                 \
        (                                                                      \
            (                                                                  \
                __MIR_ASSERT_MSG(                                              \
                    sizeof(type) > 0u,                                         \
                    "`sizeof(type)' MUST be greater than 0"                    \
                ),                                                             \
                __MIR_ASSERT_MSG(                                              \
                    (arr) != NULL,                                             \
                    "param `arr' MUST NOT be NULL"                             \
                )                                                              \
            ),                                                                 \
            __MIR_Arr_InitByMallocF_impl(                                      \
                malloc, (const void **)&(arr)->data, &(arr)->len, (length),    \
                sizeof(type)                                                   \
            )                                                                  \
        ) /* clang-format on */

/**
 * \brief Deinits \ref MIR_Arr struct using standard library `free` function as
 * a deallocator.
 *
 * \param[in,out] arr pointer to \ref MIR_Arr struct to be deinitialized
 *
 * \warning If `arr->len` is equal to `0` then `arr->data` **MUST** be `NULL`
 *
 * \note This macros will be defined only if `MIR_NO_STD_ALLOCATOR` is not
 * defined
 */
#    define MIR_Arr_Deinit(arr)                                                \
        /* clang-format off */                                                 \
        (                                                                      \
            (                                                                  \
                __MIR_ASSERT_MSG(                                              \
                    (arr) != NULL,                                             \
                    "param `arr' MUST not be NULL"                             \
                ),                                                             \
                __MIR_ASSERT_MSG(                                              \
                    (arr)->len == 0 ? (void *)(arr)->data == NULL : 1,         \
                    "if `arr->len == 0' then `arr->data' MUST be NULL"         \
                )                                                              \
            ),                                                                 \
            __MIR_Arr_DeinitByFreeF_impl(                                      \
                (void **)&(arr)->data, &(arr)->len, free                       \
            )                                                                  \
        ) /* clang-format on */

#endif /* MIR_NO_STD_ALLOCATOR */


#endif /* _MIR_COMMON_COLLECTIONS_ARR_H */
