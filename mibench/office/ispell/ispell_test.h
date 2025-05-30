//
// Created by sbn on 5/25/25.
//

#ifndef ISPELL_TEST_H
#define ISPELL_TEST_H

#define ISPELL_PREFIX_PATH     "/home/sbn/Work/Paper/perf_counter_exploit/mibench/office/ispell/tests/"
#define ISPELL_INPUT_LARGE     ISPELL_PREFIX_PATH "large.txt"
#define ISPELL_INPUT_SMALL     ISPELL_PREFIX_PATH "small.txt"

#define SPELL_PATH      ISPELL_PREFIX_PATH "americanmed+"

int __ispell (int argc, char *	argv[]);

static inline void _ispell_large() {
    __ispell(5, (char* []){"ispell", "-a", "-d", SPELL_PATH,  ISPELL_INPUT_LARGE});
}

static inline void _ispell_small() {
    __ispell(5, (char* []){"ispell", "-a", "-d", SPELL_PATH,  ISPELL_INPUT_SMALL});
}

#endif //ISPELL_TEST_H
