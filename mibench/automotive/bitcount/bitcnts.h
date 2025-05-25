//
// Created by sbn on 5/25/25.
//

#ifndef BITCNTS_H
#define BITCNTS_H

int _bitcnts(int argc, char *argv[]);


void _bitcnts_large() {
    _bitcnts(2, (char *[]){"bitcnts", "1125000"});
}

void _bitcnts_small() {
    _bitcnts(2, (char *[]){"bitcnts", "75000"});
}



#endif //BITCNTS_H
