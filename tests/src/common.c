#include <mir/tests/common.h>

#include <string.h>


void setUp(void) {
    /* empty */
    return;
}
void tearDown(void) {
    /* empty */
    return;
}

void MIR_TEST_ExecuteOne(MIR_TEST_TestInfo const *testInfo) {
    UnitySetTestFile(testInfo->file);
    UnityDefaultTestRun(testInfo->fn, testInfo->name, testInfo->line);
}

void MIR_TEST_ExecuteAll(void) {
    size_t i = 0;

    for (; i < MIR_TEST_TEST_INFOS_LEN; ++i) {
        MIR_TEST_ExecuteOne(MIR_TEST_TEST_INFOS[i]);
    }
}

int MIR_TEST_cmpTestName2TestInfo(const char *testName, const MIR_TEST_TestInfo **testInfo) {
    return strcmp(testName, (*testInfo)->name);
}

void MIR_TEST_PrintIncorrectUsage(void) {
    (void)fwrite("fatal: incorrect usage\n", sizeof(char), 23, stderr);
}
