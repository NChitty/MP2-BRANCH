//
// Created by nicho on 11/22/2022.
//

#ifndef MP2_BRANCH_SMITHPREDICTOR_H
#define MP2_BRANCH_SMITHPREDICTOR_H


#include <ostream>
#include "Predictor.h"

class SmithPredictor: public Predictor {
public:
    SmithPredictor(string cmd, int n);
    void update(uint32_t block, bool guess, bool actual) override;
    bool make_prediction(uint32_t block) override;
    void print() override;

protected:
    uint32_t counter;
    uint32_t criteria;
    uint32_t max;
};


#endif //MP2_BRANCH_SMITHPREDICTOR_H
