#include <mir/common/encodings/utf8.h>

#include <stddef.h> /* NULL */

#include <mir/common/macros.h>
#include <mir/internal/assert.h> /* __MIR_ASSERT_MSG */


struct ByteRange {
    unsigned char lo;
    unsigned char hi;
};

int MIR_UTF8_BufIter_Next(struct MIR_UTF8_BufIter *iter, MIR_UCP *cp) {
    const struct ByteRange *byteRange;
    unsigned int n;
    unsigned int mask;
    const struct ByteRange SecondByteRanges[5] = {
        {0x80, 0xBF},
        {0xA0, 0xBF},
        {0x80, 0x9F},
        {0x90, 0xBF},
        {0x80, 0x8F}
    };

    __MIR_ASSERT_MSG(iter != NULL, "param `iter' MUST not be NULL");
    __MIR_ASSERT_MSG(cp != NULL, "param `cp' MUST not be NULL");

    if (iter->lim <= iter->cur) {
        *cp = iter->eofVal;
        return -1;
    }

    if (*iter->cur <= 0x7F) {
        n = 0;
        mask = 0x7F; /* 0b111_1111, 2^7 - 1 */
        /* NOTE: don't set byteRange here */

    } else if (MIR_InRange(*iter->cur, 0xC2, 0xDF)) {
        n = 6;
        mask = 0x1F; /* 0b1_1111, 2^5 - 1 */
        byteRange = &SecondByteRanges[0];

    } else if (MIR_InRange(*iter->cur, 0xE0, 0xE0)) {
        n = 12;
        mask = 0xF; /* 0b1111, 2^4 - 1*/
        byteRange = &SecondByteRanges[1];

    } else if (
        /* clang-format off */ 
        MIR_InRange(*iter->cur, 0xE1, 0xEC) || 
        MIR_InRange(*iter->cur, 0xEE, 0xEF)
        /* clang-format on */
    ) {
        n = 12;
        mask = 0xF; /* 0b1111, 2^4 - 1 */
        byteRange = &SecondByteRanges[0];

    } else if (MIR_InRange(*iter->cur, 0xED, 0xED)) {
        n = 12;
        mask = 0xF; /* 0b1111, 2^4 - 1 */
        byteRange = &SecondByteRanges[2];

    } else if (MIR_InRange(*iter->cur, 0xF0, 0xF0)) {
        n = 18;
        mask = 0x7; /* 0b111, 2^3 - 1 */
        byteRange = &SecondByteRanges[3];

    } else if (MIR_InRange(*iter->cur, 0xF1, 0xF3)) {
        n = 18;
        mask = 0x7; /* 0b111, 2^3 - 1*/
        byteRange = &SecondByteRanges[0];

    } else if (MIR_InRange(*iter->cur, 0xF4, 0xF4)) {
        n = 18;
        mask = 0x7; /* 0b111, 2^3 - 1 */
        byteRange = &SecondByteRanges[4];

    } else {
        *cp = iter->replVal;
        ++iter->cur;
        return 1;
    }

    *cp = (*iter->cur & mask) << n;
    mask = 0x3F; /* reset the mask to 0b11_1111, 2^6 - 1 */
    ++iter->cur;

    while (n >= 6u) {
        if (iter->lim <= iter->cur) {
            *cp = iter->replVal;
            return 1;
        }

        if (!MIR_InRange(*iter->cur, byteRange->lo, byteRange->hi)) {
            *cp = iter->replVal;
            return 1;
        }
        byteRange = &SecondByteRanges[0]; /* reset to 80..BF */

        n -= 6u;
        *cp += (*iter->cur & mask) << n;

        ++iter->cur;
    }

    return 0;
}

int MIR_UTF8_BufIter_PeekNext(struct MIR_UTF8_BufIter *iter, MIR_UCP *cp) {
    unsigned char const *cur;
    int res;

    __MIR_ASSERT_MSG(iter != NULL, "param `iter' MUST NOT be NULL");

    cur = iter->cur;
    res = MIR_UTF8_BufIter_Next(iter, cp);
    iter->cur = cur;

    return res;
}

int MIR_UTF8_BufIter_SkipBOM(struct MIR_UTF8_BufIter *iter) {
    __MIR_ASSERT_MSG(
        iter->cur == iter->buf,
        "iter::cur does not point to the start of the buffer"
    );

    if ((iter->cur == NULL) || ((iter->lim - iter->cur) < 3)) {
        return 1;
    }

    if (
        /* clang-format off */ 
        (iter->buf[0] == (unsigned char)MIR_UTF8_REPLACEMENT_CHARACTER_STR[0])
        &&
        (iter->buf[1] == (unsigned char)MIR_UTF8_REPLACEMENT_CHARACTER_STR[1])
        &&
        (iter->buf[2] == (unsigned char)MIR_UTF8_REPLACEMENT_CHARACTER_STR[2])
        /* clang-format on */
    ) {
        iter->cur += 3;
        return 0;
    } else {
        return 1;
    }
}
