//
// Created by nicho on 11/22/2022.
//

#include "BimodalPredictor.h"
#include <math.h>

bool BimodalPredictor::make_prediction(uint32_t block) {
    stats->access++;
    // ignore the trailing zeros in PC and get the set bits by masking
    int index = (block >> 2) & pc_mask;
    return prediction_table.at(index) >= 4;
}

void BimodalPredictor::update(uint32_t block, bool guess, bool actual) {
    if(guess != actual) {
        stats->mispredict++;
    }

    // get the index from the vector
    int index = (block >> 2) & pc_mask;

    /*
     * if actual was taken, increment unless saturated
     * otherwise decrement unless saturated
     */
    if(actual) {
        if(prediction_table.at(index) < 7) {
            prediction_table.at(index) = prediction_table.at(index) + 1;
        }
    } else {
        if(prediction_table.at(index) > 0) {
            prediction_table.at(index)  = prediction_table.at(index) - 1;
        }
    }
}

void BimodalPredictor::print() {
    printf("COMMAND\n");
    printf("%s\n", command.c_str());
    printf("OUTPUT\n");
    printf("number of predictions:%12d\n", stats->access);
    printf("number of mispredictions:%9d\n", stats->mispredict);
    printf("misprediction rate:%14.2f%%\n", ((double) stats->mispredict / stats->access) * 100);
    printf("FINAL BIMODAL CONTENTS\n");
    for(int i = 0; i < prediction_table.size(); i++) {
        printf("%2d%2d\n", i, prediction_table.at(i));
    }
}

BimodalPredictor::BimodalPredictor(int n, string trace_file) {
    command += " bimodal ";
    command += to_string(n);
    command += " " + trace_file;

    stats = (Stats*) calloc(1, sizeof(Stats));
    stats->access = 0;
    stats->mispredict = 0;

    // assign all the prediction table values to 4
    prediction_table.assign(pow(2, n), 4);
    // results in the bottom n bits being 1s to get that part of the PC
    pc_mask = pow(2, n)-1;
}

void BimodalPredictor::print_contents() {
    printf("FINAL BIMODAL CONTENTS\n");
    for(int i = 0; i < prediction_table.size(); i++) {
        printf("%2d%2d\n", i, prediction_table.at(i));
    }
}
