//
// Created by sbn on 5/25/25.
//

#ifndef LOUT_H
#define LOUT_H

#define LOUT_INC            "lout-3.24/include"
#define LOUT_DATA           "lout-3.24/data"
#define LOUT_FONT           "lout-3.24/font"
#define LOUT_MAPS           "lout-3.24/maps"
#define LOUT_HYPH           "lout-3.24/hyph"
#define INPUT_LARGE         "large.lout"
#define INPUT_SMALL         "small.lout"

int _lout(int argc, char *argv[]);

void lout_large() {
    _lout(12, (char*[]){"lout-3.24/lout", "-I", LOUT_INC, "-D", LOUT_DATA, "-F", LOUT_FONT, "-C", LOUT_MAPS, "-H", LOUT_HYPH, INPUT_LARGE});
}

void lout_small() {
    _lout(12, (char*[]){"lout-3.24/lout", "-I", LOUT_INC, "-D", LOUT_DATA, "-F", LOUT_FONT, "-C", LOUT_MAPS, "-H", LOUT_HYPH, INPUT_SMALL});
}

#endif //LOUT_H
