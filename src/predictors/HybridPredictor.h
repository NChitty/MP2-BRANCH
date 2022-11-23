//
// Created by nicho on 11/22/2022.
//

#ifndef MP2_BRANCH_HYBRIDPREDICTOR_H
#define MP2_BRANCH_HYBRIDPREDICTOR_H


#include "Predictor.h"
#include "GsharePredictor.h"
#include "BimodalPredictor.h"

class HybridPredictor: public Predictor {
public:
    HybridPredictor(int pc_bits_chooser, int pc_bits_gbh, int gbh_bits, int pc_bits_bimodal, string trace_file);

    bool make_prediction(uint32_t block) override;

    void update(uint32_t block, bool guess, bool actual) override;

    void print() override;

protected:
    GsharePredictor* gshare;
    BimodalPredictor* bimodal;
    vector<int> chooser_table;
    uint32_t pc_mask;
};


#endif //MP2_BRANCH_HYBRIDPREDICTOR_H
