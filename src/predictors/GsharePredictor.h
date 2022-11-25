//
// Created by nicho on 11/22/2022.
//

#ifndef MP2_BRANCH_GSHAREPREDICTOR_H
#define MP2_BRANCH_GSHAREPREDICTOR_H


#include <vector>
#include "Predictor.h"

class GsharePredictor: public Predictor {
public:
    GsharePredictor(int pc_bits, int gbh_bits, string trace_file);

    bool make_prediction(uint32_t block) override;

    void update(uint32_t block, bool guess, bool actual) override;

    void print() override;

    void update_gbh(bool b);

    void print_contents();

protected:
    vector<int> prediction_table;
    uint32_t gbh;
    uint32_t gbh_mask;
    uint32_t pc_mask;
};


#endif //MP2_BRANCH_GSHAREPREDICTOR_H
