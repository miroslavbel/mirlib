#ifndef _MIR_TESTS_COMMON_H
#define _MIR_TESTS_COMMON_H

#include <unity.h>

#include <mir/tests/testinfo.h>


#define EXIT_TEST_FAILED 1
#define EXIT_USAGE_ERROR 4

#define TEST_VITAL 3
#define TEST_MAJOR 2
#define TEST_MINOR 1

#define mir_test_min(lhs, rhs) ((lhs) < (rhs) ? (lhs) : (rhs))

#define MIR_TEST_DECL(name) extern const MIR_TEST_TestInfo __MIR_TEST_INFO_##name

#define MIR_TEST_DEF(severity, name)                                                               \
    extern void(test_##name)(void);                                                                \
    const MIR_TEST_TestInfo __MIR_TEST_INFO_##name = {                                             \
        #name, test_##name, __FILE__, __LINE__, (severity)};                                       \
    void(test_##name)(void)


extern void setUp(void);
extern void tearDown(void);

/**
 * \brief Executes one given test.
 *
 * \note Doesn't call `UNITY_BEGIN` and `UNITY_END`.
 *
 * \param testInfo
 */
extern void MIR_TEST_ExecuteOne(MIR_TEST_TestInfo const *testInfo);

/**
 * \brief Executes all tests.
 *
 * \note Doesn't call `UNITY_BEGIN` and `UNITY_END`.
 */
extern void MIR_TEST_ExecuteAll(void);

extern int MIR_TEST_cmpTestName2TestInfo(const char *testName, const MIR_TEST_TestInfo **testInfo);

extern void MIR_TEST_PrintIncorrectUsage(void);

#endif /* _MIR_TESTS_COMMON_H */
