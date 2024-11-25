/**
 * \file
 *
 * \brief UTF-8 routines
 */


#ifndef _MIR_COMMON_ENCODINGS_UTF8_H_
#define _MIR_COMMON_ENCODINGS_UTF8_H_

#include <mir/common/unicode.h>


/**
 * \brief UTF-8 BOM as a string literal.
 *
 * \details TODO
 *
 * \see \ref MIR_UTF8_BOM_BLEN - for length in bytes
 */
#define MIR_UTF8_BOM_STR "\xEF\xBB\xBF"

/**
 * \brief UTF-8 BOM byte length.
 *
 * \see \ref MIR_UTF8_BOM_STR - for string literal
 */
#define MIR_UTF8_BOM_BLEN 3


/**
 * \brief Replacement character (`�`) as a string literal in UTF-8 encoding.
 *
 * \see
 * + \ref MIR_UTF8_REPLACEMENT_CHARACTER_BLEN - for length in bytes in UTF-8
 *   encoding
 * + \ref MIR_REPLACEMENT_CHARACTER_CP - for code point value
 */
#define MIR_UTF8_REPLACEMENT_CHARACTER_STR "\xEF\xBF\xBD"

/**
 * \brief Length of replacement character (`�`) in UTF-8 encoding in bytes.
 *
 * \see
 * + \ref MIR_UTF8_REPLACEMENT_CHARACTER_STR - for string literal in UTF-8
 *   encoding
 * + \ref MIR_REPLACEMENT_CHARACTER_CP - for code point value
 */
#define MIR_UTF8_REPLACEMENT_CHARACTER_BLEN 3


/**
 * \brief UTF-8 code point iterator over continuous buffer.
 *
 * \details
 *
 * ## BOM handling
 *
 * There is no special treatment for BOM. When encountered (anywhere in the
 * buffer) it will be read as \c U+FEFF (`ZERO WIDTH NO-BREAK SPACE`).
 *
 * One can use \ref MIR_UTF8_BufIter_SkipBOM to skip BOM.
 *
 *
 * ## Initialization
 *
 * Both `.buf == .cur` and `.cur <= .lim` **MUST** be true after initialization.
 * If input code unit sequence is empty \a buf **MAY** be \c NULL (which implies
 * that in this case \a lim **MAY** be \c NULL too).
 *
 * There are also two fields - \a replVal and \a eofVal which **MAY** be left
 * initialized if one is not cared.
 *
 *
 * ## Interface
 *
 * + \ref MIR_UTF8_BufIter_SkipBOM - to skip BOM (if any)
 * + \ref MIR_UTF8_BufIter_Next - to get the next code point
 */
struct MIR_UTF8_BufIter {
    /**
     * \brief Cursor.
     *
     * \details It **MUST** be greater or equal to \a buf. It **MUST** be less
     * or equal to \a lim. It **MAY** be \c NULL.
     */
    const unsigned char *cur;

    /**
     * \brief Pointer to the buffer.
     *
     * \details It **MAY** be \c NULL if code unit sequence is empty.
     */
    const unsigned char *buf;

    /**
     * \brief Limit.
     *
     * \details Pointer to the byte immediately following the buffer. For
     * C-strings it will point to \c '0' char.
     *
     * It **MUST** be greater or equal to \a cur. It **MAY** be \c NULL iff \a
     * buf is \c NULL.
     */
    const unsigned char *lim;

    /**
     * \brief Replacement value.
     *
     * \details Replacement value to use when ill-formed code unit sequence
     * is encountered. Usually \ref MIR_REPLACEMENT_CHARACTER_CP is used.
     */
    MIR_UCP replVal;

    /**
     * \brief EOF sentinel value.
     *
     * \details It has similar semantics as stdlib's \c EOF and \c WEOF. It's
     * used by \ref MIR_UTF8_BufIter_Next as code point to return in case of
     * EOF. It's recommended to use \c UINT_LEAST32_MAX here.
     *
     * \note Stdlib's type \c wint_t (as well as \c wchar_t) is implementation
     * defined and doesn't guarantee to support all Unicode code points. This
     * can lead to the situation where \c WEOF is defined to valid Unicode code
     * point which implies that \c WEOF is indistinguishable from a valid
     * Unicode code point.
     */
    MIR_UCP eofVal;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Advances the iterator and returns the next code point.
 *
 * \details
 * ## Error handling
 *
 * \note This associated function may return codepoints which are not assigned
 * to characters.
 *
 * It handles the following cases as error (without distinction):
 * + invalid first byte
 *   - a "continuation byte" (`[0x80–0xBF]` at the start of a character
 *   - bytes that never appear in UTF-8 (`[0xC0, 0xC1]` and `[0xF5-0xFF]`)
 * + invalid second byte
 *   - absence of it (because of unexpected EOF or unexpected first byte of the
 *     next code point)
 *   - an overlong encoding (\c 0xE0 followed by less than \c 0xA0, or \c 0xF0
 *     followed by less than \c 0x90)
 *   - a 4-byte sequence that decodes to a value greater that U+10FFFF (\c 0xF4
 *     followed by \c 0x90 or greater)
 * + invalid third and fourth byte
 *   - absence of it (because of unexpected EOF or unexpected first byte of the
 *     next code point)
 *   - `[0x00, 0x79]` and `[0xC0, 0xFF]`
 *
 *
 * ## BOM
 *
 * There is no special treatment for BOM. BOM will be read as \c U+FEFF (`ZERO
 * WIDTH NO-BREAK SPACE`). To skip BOM one can use \ref MIR_UTF8_BufIter_SkipBOM
 *
 *
 * \param[in,out] iter pointer to iterator
 * \param[out]    cp   pointer where the next code will be written
 *
 * \return
 * + \c -1 - if EOF was encountered. If so writes the EOF sentinel value (from
 *           \ref MIR_UTF8_BufIter "iter->eofVal") to \a cp
 * + \c  1 - if ill-formed code unit sequence was encountered. If so writes the
 *           replacement value (from \ref MIR_UTF8_BufIter::replVal
 *           "iter->replVal") to \a cp
 * + \c  0 - on success
 */
extern int MIR_UTF8_BufIter_Next(struct MIR_UTF8_BufIter *iter, MIR_UCP *cp);

/**
 * \brief Skips BOM (if any).
 *
 * \param[in,out] iter pointer to iterator. It **MUST** point to the beginning
 *                     of the buffer. \ref MIR_UTF8_BufIter::cur "iter->cur"
 *                     **MAY** be \c NULL.
 *
 * \return
 * + \c 0 - if BOM was skipped
 * + \c 1 - otherwise
 *   - the buffer is empty
 *   - the buffer doesn't start with BOM (including the case when the buffer is
 *     too small to simply contain BOM)
 *
 * \sa
 * + \ref MIR_UTF8_BOM_STR - for UTF-8 BOM string literal
 * + \ref MIR_UTF8_BOM_BLEN - for UTF-8 BOM byte length
 */
extern int MIR_UTF8_BufIter_SkipBOM(struct MIR_UTF8_BufIter *iter);

#ifdef __cplusplus
}
#endif


#endif /* _MIR_COMMON_ENCODINGS_UTF8_H_ */
