#include <mir/tests/common.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define incorrectUsage                                                                             \
    MIR_TEST_PrintIncorrectUsage();                                                                \
    retCode = EXIT_USAGE_ERROR;                                                                    \
    goto exit


int main(int argc, char *argv[]) {
    MIR_TEST_TestInfo const *const *testInfo;
    char const *testName;
    size_t optionLen;
    int retCode;

    if (argc != 2) {
        incorrectUsage;
    }
    if ((argv[1][0] != '-') && (argv[1][1] != '-')) {
        incorrectUsage;
    }

    optionLen = strcspn(&argv[1][2], "=");

    if (memcmp("help", &argv[1][2], mir_test_min(optionLen, (size_t)4)) == 0) {
        (void)printf(
            "USAGE:\n"
            "  --help                   print this message\n"
            "  --run-all                run all tests\n"
            "  --test=<name>            run specified test and exit\n"
        );
        retCode = EXIT_SUCCESS;
        goto exit;

    } else if (memcmp("test", &argv[1][2], mir_test_min(optionLen, (size_t)4)) == 0) {

        if (argv[1][6] != '=') {
            incorrectUsage;
        }

        testName = &argv[1][7];

        testInfo = (MIR_TEST_TestInfo const *const *)bsearch(
            testName, MIR_TEST_TEST_INFOS, MIR_TEST_TEST_INFOS_LEN, sizeof(MIR_TEST_TestInfo *),
            (int (*)(const void *, const void *)) & MIR_TEST_cmpTestName2TestInfo
        );

        if (testInfo == NULL) {
            (void)fwrite("fatal: test with such name not found\n", sizeof(char), 37, stdout);
            retCode = EXIT_USAGE_ERROR;
            goto exit;
        }

        UNITY_BEGIN();
        MIR_TEST_ExecuteOne(*testInfo);
        retCode = (UNITY_END() != 0) ? EXIT_TEST_FAILED : EXIT_SUCCESS;
        goto exit;

    } else if (memcmp("run-all", &argv[1][2], mir_test_min(optionLen, (size_t)7)) == 0) {
        UNITY_BEGIN();
        MIR_TEST_ExecuteAll();
        retCode = (UNITY_END() != 0) ? EXIT_TEST_FAILED : EXIT_SUCCESS;
        goto exit;

    } else {
        incorrectUsage;
    }

exit:
    return retCode;
}
