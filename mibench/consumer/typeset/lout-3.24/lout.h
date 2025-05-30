//
// Created by sbn on 5/25/25.
//

#ifndef LOUT_H
#define LOUT_H

#define LOUT_PREFIX_PATH         "/home/sbn/Work/Paper/perf_counter_exploit/mibench/consumer/typeset/"
#define LOUT_INC           LOUT_PREFIX_PATH "lout-3.24/include"
#define LOUT_DATA          LOUT_PREFIX_PATH "lout-3.24/data"
#define LOUT_FONT          LOUT_PREFIX_PATH "lout-3.24/font"
#define LOUT_MAPS          LOUT_PREFIX_PATH "lout-3.24/maps"
#define LOUT_HYPH          LOUT_PREFIX_PATH "lout-3.24/hyph"
#define LOUT_INPUT_LARGE        LOUT_PREFIX_PATH "large.lout"
#define LOUT_INPUT_SMALL        LOUT_PREFIX_PATH "small.lout"

int _lout(int argc, char *argv[]);

static inline void _lout_large() {
    _lout(12, (char*[]){"lout-3.24/lout", "-I", LOUT_INC, "-D", LOUT_DATA, "-F", LOUT_FONT, "-C", LOUT_MAPS, "-H", LOUT_HYPH, LOUT_INPUT_LARGE});
}

static inline void _lout_small() {
    _lout(12, (char*[]){"lout-3.24/lout", "-I", LOUT_INC, "-D", LOUT_DATA, "-F", LOUT_FONT, "-C", LOUT_MAPS, "-H", LOUT_HYPH, LOUT_INPUT_SMALL});
}

#endif //LOUT_H
