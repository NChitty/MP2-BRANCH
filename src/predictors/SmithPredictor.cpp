//
// Created by nicho on 11/22/2022.
//

#include <math.h>
#include "SmithPredictor.h"

SmithPredictor::SmithPredictor(int n, string trace_file) {
    command += " smith ";
    command += to_string(n);
    command += " " + trace_file;

    stats = (Stats*) calloc(1, sizeof(Stats));
    stats->access = 0;
    stats->mispredict = 0;
    // this is half the maximum number of bits
    criteria = pow(2, n-1);
    max = pow(2, n); // this is maximum value of the counter
    counter = criteria; // initialize the counter to "weak taken"
}

void SmithPredictor::update(uint32_t block, bool guess, bool actual) {
    if(guess != actual) {
        stats->mispredict++;
    }

    /*
     * if actual was "taken", increment unless saturated
     * else decrement unless saturated
     */
    if(actual) {
        if(counter < max-1) {
            counter++;
        }
    } else {
        if(counter  > 0) {
            counter--;
        }
    }
}

bool SmithPredictor::make_prediction(uint32_t block) {
    stats->access++;
    return counter >= criteria;
}

void SmithPredictor::print() {
    printf("COMMAND\n");
    printf("%s\n", command.c_str());
    printf("OUTPUT\n");
    printf("number of predictions:%12d\n", stats->access);
    printf("number of mispredictions:%9d\n", stats->mispredict);
    printf("misprediction rate:%14.2f%%\n", ((double) stats->mispredict / stats->access) * 100);
    printf("FINAL COUNTER CONTENT:%12d\n", counter);
}
