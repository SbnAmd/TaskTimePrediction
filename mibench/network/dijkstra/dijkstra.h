//
// Created by sbn on 5/25/25.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/network/dijkstra/"
#define INPUT_FILE PREFIX_PATH "input.dat"

int __dijkstra_large(int argc, char *argv[]);
int __dijkstra_small(int argc, char *argv[]);


void _dijkstra_large() {
    __dijkstra_large(2, (char *[]){"dijkstra_large", INPUT_FILE});
}


void _dijkstra_small() {
    __dijkstra_small(2, (char *[]){"dijkstra_small", INPUT_FILE});
}

#endif //DIJKSTRA_H
