/**
 * \file
 *
 * \brief Unicode
 */


#ifndef _MIR_COMMON_UNICODE_H_
#define _MIR_COMMON_UNICODE_H_


#if __STDC_VERSION__ >= 201112L

#    include <uchar.h>
/**
 * \brief Unicode code point.
 */
typedef char32_t MIR_UCP;

#else /* __STDC_VERSION__ */

#    include <stdint.h>
/**
 * \brief Unicode code point.
 */
typedef uint_least32_t MIR_UCP;

#endif /* __STDC_VERSION__ */


/**
 * \brief REPLACEMENT CHARACTER (`�`) code point.
 */
#define MIR_REPLACEMENT_CHARACTER_CP 0xFFFD


#endif /* _MIR_COMMON_UNICODE_H_ */
