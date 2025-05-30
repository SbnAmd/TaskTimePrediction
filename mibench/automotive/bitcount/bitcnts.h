//
// Created by sbn on 5/25/25.
//

#ifndef BITCNTS_H
#define BITCNTS_H

void _bitcnts(int argc, char *argv[]);


static inline void _bitcnts_large_() {
    _bitcnts(2, (char *[]){"bitcnts", "1125000"});
}

static inline void _bitcnts_small_() {
    _bitcnts(2, (char *[]){"bitcnts", "75000"});
}



#endif //BITCNTS_H
