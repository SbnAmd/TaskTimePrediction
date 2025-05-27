//
// Created by sbn on 5/25/25.
//

#ifndef ISPELL_TEST_H
#define ISPELL_TEST_H

#define PREFIX_PATH     "/home/sbn/Work/Paper/perf_counter_exploit/mibench/office/ispell/tests/"
#define INPUT_LARGE     PREFIX_PATH "large.txt"
#define INPUT_SMALL     PREFIX_PATH "small.txt"

#define SPELL_PATH      PREFIX_PATH "americanmed+"

int __ispell (int argc, char *	argv[]);

void _ispell_large() {
    __ispell(5, (char* []){"ispell", "-a", "-d", SPELL_PATH,  INPUT_LARGE});
}

void _ispell_small() {
    __ispell(5, (char* []){"ispell", "-a", "-d", SPELL_PATH,  INPUT_SMALL});
}

#endif //ISPELL_TEST_H
