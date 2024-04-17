#ifndef _MIR_TESTS_TESTINFO_H
#define _MIR_TESTS_TESTINFO_H

#include <stddef.h>


typedef struct __tagMIR_TEST_TestInfo {
    char const *name;
    void (*fn)(void);
    char const *file;
    int line;
    int severity;
} MIR_TEST_TestInfo;

#define MIR_TEST_TEST_INFOS_LEN ((size_t)0)

extern const MIR_TEST_TestInfo *MIR_TEST_TEST_INFOS[MIR_TEST_TEST_INFOS_LEN];

#endif /* _MIR_TESTS_TESTINFO_H */
