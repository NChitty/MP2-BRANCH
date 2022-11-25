//
// Created by nicho on 11/22/2022.
//

#ifndef MP2_BRANCH_BIMODALPREDICTOR_H
#define MP2_BRANCH_BIMODALPREDICTOR_H


#include <vector>
#include "Predictor.h"

class BimodalPredictor: public Predictor {
public:
    BimodalPredictor(string cmd, int n);

    bool make_prediction(uint32_t block) override;

    void update(uint32_t block, bool guess, bool actual) override;

    void print() override;

    void print_contents();

protected:
    vector<uint32_t> prediction_table;
    uint32_t pc_mask;
};


#endif //MP2_BRANCH_BIMODALPREDICTOR_H
