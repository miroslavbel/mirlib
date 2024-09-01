/**
 * \file
 *
 * \brief Arithmetic utilities.
 */


#ifndef _MIR_COMMON_ARITH_H
#define _MIR_COMMON_ARITH_H


/**
 * \brief Checks whether the addiction of unsigned integers `lhs` and `rhs` will
 * overflow.
 *
 * \note Implementation details: it actually performs the addiction as the
 * operations has defined behavior for unsigned integer types.
 *
 * \param lhs augend. **MUST** be of an unsigned integer type. **MAY** be of a
 *            different type than `rhs`
 * \param rhs addend. **MUST** be of an unsigned integer type. **MAY** be of a
 *            different type than `lhs`
 *
 * \return `1` if the operation will overflow, `0` otherwise
 */
#define MIR_u_Add_WillOverflow(lhs, rhs) (((lhs) + (rhs)) < (lhs) ? 1 : 0)

/**
 * \brief Checks whether the subtraction of unsigned integers `lhs` and `rhs`
 * will underflow.
 *
 * \param lhs minuend. **MUST** be of an unsigned integer type. **MAY** be of a
 *            different type than `rhs`
 * \param rhs subtrahend. **MUST** be of an unsigned integer type. **MAY** be of
 *            a different type than `lhs`
 *
 * \return `1` if the operation will overflow, `0` otherwise
 */
#define MIR_u_Sub_WillUnderflow(lhs, rhs) ((lhs) < (rhs))

/**
 * \brief Checks whether the multiplication of unsigned integers `lhs` and `rhs`
 * will overflow.
 *
 * \param lhs multiplier. **MUST** be of an unsigned integer type. **MAY** be of
 *            a different type than `rhs`
 * \param rhs multiplicand. **MUST** be of an unsigned integer type. **MAY** be
 *            of a different type than `lhs`
 * \param MAX maximum value of `lhs` and `rhs` *common type*
 *
 * \return `1` if the operation will overflow, `0` otherwise
 */
#define MIR_u_Mul_WillOverflow(x, y, MAX)                                      \
    /* NOTE: lhs and rhs are guaranteed by the user to be non-negative.        \
     *       Therefore, the result of `/` operator here is guaranteed to be    \
     *       the algebraic quotient with any fractional part discarded (a.k.a. \
     *       truncated towards zero) even prior to C99 */                      \
    (((x) != 0u) ? ((MAX) / (x)) < (y) : 0)


#endif /* _MIR_COMMON_ARITH_H */
