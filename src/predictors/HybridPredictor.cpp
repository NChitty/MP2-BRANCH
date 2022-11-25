//
// Created by nicho on 11/22/2022.
//

#include "HybridPredictor.h"
#include <math.h>

bool HybridPredictor::make_prediction(uint32_t block) {
    stats->access++;
    uint32_t index = (block >> 2) & pc_mask;
    if(chooser_table.at(index) >= 2) {
        return gshare->make_prediction(block);
    } else {
        return bimodal->make_prediction(block);
    }
}

void HybridPredictor::update(uint32_t block, bool guess, bool actual) {
    // check if misprediction
    if (guess != actual) {
        stats->mispredict++;
    }
    // index
    uint32_t index = (block >> 2) & pc_mask;
    // get the current value in chooser table
    int currentVal = chooser_table.at(index);

    // get guesses
    bool gshare_guess = gshare->make_prediction(block);
    bool bimodal_guess = bimodal->make_prediction(block);

    // update gshare and bimodal
    if(currentVal >= 2) {
        gshare->update(block, guess, actual);
    } else {
        bimodal->update(block, guess, actual);
        gshare->update_gbh(actual); // always update global branch history
    }

    // not the same
    if(gshare_guess != bimodal_guess) {
        // gshare correct
        if (gshare_guess == actual) {
            // saturate at 3
            if (currentVal < 3) {
                chooser_table.at(index) = currentVal + 1;
            }
        // bimodal correct
        } else if (bimodal_guess == actual) {
            // saturate at 0
            if(currentVal > 0) {
                chooser_table.at(index) = currentVal - 1;
            }
        }
    } // otherwise do nothing with chooser table
}

void HybridPredictor::print() {
    printf("COMMAND\n");
    printf("%s\n", command.c_str());
    printf("OUTPUT\n");
    printf("number of predictions:%12d\n", stats->access);
    printf("number of mispredictions:%9d\n", stats->mispredict);
    printf("misprediction rate:%14.2f%%\n", ((double) stats->mispredict / stats->access) * 100);
    printf("FINAL CHOOSER CONTENTS\n");
    for(int i = 0; i < chooser_table.size(); i++) {
        printf("%5d%2d\n", i, chooser_table.at(i));
    }
    gshare->print_contents();
    bimodal->print_contents();
}

HybridPredictor::HybridPredictor(int pc_bits_chooser, int pc_bits_gbh, int gbh_bits, int pc_bits_bimodal,
                                 string trace_file) {
    command += " hybrid ";
    command += to_string(pc_bits_chooser) + " ";
    command += to_string(pc_bits_gbh);
    command += " " + to_string(gbh_bits) + " " + to_string(pc_bits_bimodal) + " " + trace_file;
    gshare = new GsharePredictor(pc_bits_gbh, gbh_bits, trace_file);
    bimodal = new BimodalPredictor(pc_bits_bimodal, trace_file);

    stats = (Stats*) calloc(1, sizeof(Stats));
    stats->access = 0;
    stats->mispredict = 0;

    pc_mask = pow(2, pc_bits_chooser) - 1;
    chooser_table.assign(pow(2, pc_bits_chooser), 1);
}
