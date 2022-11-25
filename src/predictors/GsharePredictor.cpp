//
// Created by nicho on 11/22/2022.
//

#include "GsharePredictor.h"
#include <math.h>

bool GsharePredictor::make_prediction(uint32_t block) {
    stats->access++;
    int index = ((block >> 2) & pc_mask) ^ gbh;
    return prediction_table.at(index) >= 4;
}

void GsharePredictor::update(uint32_t block, bool guess, bool actual) {
    if(guess != actual) {
        stats->mispredict++;
    }

    // get the index from the vector
    int index = ((block >> 2) & pc_mask) ^ gbh;

    /*
     * if actual was taken, increment unless saturated
     * otherwise decrement unless saturated
     */
    if(actual) {
        gbh |= (gbh_mask+1);
        gbh >>= 1;
        gbh &= gbh_mask;
        if(prediction_table.at(index) < 7) {
            prediction_table.at(index) = prediction_table.at(index) + 1;
        }
    } else {
        gbh >>= 1;
        gbh &= gbh_mask;
        if(prediction_table.at(index) > 0) {
            prediction_table.at(index)  = prediction_table.at(index) - 1;
        }
    }
}

void GsharePredictor::print() {
    printf("COMMAND\n");
    printf("%s\n", command.c_str());
    printf("OUTPUT\n");
    printf("number of predictions:%12d\n", stats->access);
    printf("number of mispredictions:%9d\n", stats->mispredict);
    printf("misprediction rate:%14.2f%%\n", ((double) stats->mispredict / stats->access) * 100);
    printf("FINAL GSHARE CONTENTS\n");
    for(int i = 0; i < prediction_table.size(); i++) {
        printf("%7d%2d\n", i, prediction_table.at(i));
    }
}

GsharePredictor::GsharePredictor(string cmd, int pc_bits, int gbh_bits) {
    command = cmd;

    stats = (Stats*) calloc(1, sizeof(Stats));
    stats->access = 0;
    stats->mispredict = 0;

    // assign all the prediction table values to 4
    prediction_table.assign(pow(2, pc_bits), 4);
    gbh = 0;
    // this is to keep the correct values in the gbh
    gbh_mask = ((int) pow(2, gbh_bits)-1);
    pc_mask = pow(2, pc_bits) - 1;
}

void GsharePredictor::update_gbh(bool b) {
    if (b) {
        gbh |= (gbh_mask+1);
        gbh >>= 1;
        gbh &= gbh_mask;
    } else {
        gbh >>= 1;
        gbh &= gbh_mask;
    }
}

void GsharePredictor::print_contents() {
    printf("FINAL GSHARE CONTENTS\n");
    for(int i = 0; i < prediction_table.size(); i++) {
        printf("%7d%2d\n", i, prediction_table.at(i));
    }
}
