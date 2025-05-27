//
// Created by sbn on 5/25/25.
//

#ifndef LOUT_H
#define LOUT_H

#define PREFIX_PATH         "/home/sbn/Work/Paper/perf_counter_exploit/mibench/consumer/typeset/"
#define LOUT_INC           PREFIX_PATH "lout-3.24/include"
#define LOUT_DATA          PREFIX_PATH "lout-3.24/data"
#define LOUT_FONT          PREFIX_PATH "lout-3.24/font"
#define LOUT_MAPS          PREFIX_PATH "lout-3.24/maps"
#define LOUT_HYPH          PREFIX_PATH "lout-3.24/hyph"
#define INPUT_LARGE        PREFIX_PATH "large.lout"
#define INPUT_SMALL        PREFIX_PATH "small.lout"

int _lout(int argc, char *argv[]);

void _lout_large() {
    _lout(12, (char*[]){"lout-3.24/lout", "-I", LOUT_INC, "-D", LOUT_DATA, "-F", LOUT_FONT, "-C", LOUT_MAPS, "-H", LOUT_HYPH, INPUT_LARGE});
}

void _lout_small() {
    _lout(12, (char*[]){"lout-3.24/lout", "-I", LOUT_INC, "-D", LOUT_DATA, "-F", LOUT_FONT, "-C", LOUT_MAPS, "-H", LOUT_HYPH, INPUT_SMALL});
}

#endif //LOUT_H
