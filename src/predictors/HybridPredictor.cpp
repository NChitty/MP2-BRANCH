//
// Created by nicho on 11/22/2022.
//

#include "HybridPredictor.h"
#include <math.h>

bool HybridPredictor::make_prediction(uint32_t block) {
    stats->access++;

    return false;
}

void HybridPredictor::update(uint32_t block, bool guess, bool actual) {

}

void HybridPredictor::print() {

}

HybridPredictor::HybridPredictor(int pc_bits_chooser, int pc_bits_gbh, int gbh_bits, int pc_bits_bimodal,
                                 string trace_file) {
    gshare = new GsharePredictor(pc_bits_gbh, gbh_bits, trace_file);
    bimodal = new BimodalPredictor(pc_bits_bimodal, trace_file);

    stats = (Stats*) calloc(1, sizeof(Stats));

    pc_mask = pow(2, pc_bits_chooser) - 1;
    chooser_table.assign(pow(2, pc_bits_chooser), 1);
}
