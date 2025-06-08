//
// Created by sbn on 5/25/25.
//

#ifndef PATRICIA_TEST_H
#define PATRICIA_TEST_H
#include "mi_def.h"
#define PATRICIA_PREFIX_PATH GLOB_PREFIX_PATH "network/patricia/"
#define PATRICIA_INPUT_LARGE PATRICIA_PREFIX_PATH "large.udp"
#define PATRICIA_INPUT_SMALL PATRICIA_PREFIX_PATH "small.udp"

int __patricia(int argc, char **argv);


static inline void _patricia_large() {
    __patricia(2, (char*[]){"patricia", PATRICIA_INPUT_LARGE});
}

static inline void _patricia_small() {
    __patricia(2, (char*[]){"patricia", PATRICIA_INPUT_SMALL});
}

#endif //PATRICIA_TEST_H
