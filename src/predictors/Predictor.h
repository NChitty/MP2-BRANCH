//
// Created by nicho on 11/22/2022.
//

#ifndef MP2_BRANCH_PREDICTOR_H
#define MP2_BRANCH_PREDICTOR_H

#include <string>
#include <ostream>
#include <iomanip>
#include "../Stats.h"

using namespace std;
class Predictor {
public:
    /**
     *
     * @param block The address of the block
     * @return True for a branch taken or false for predict branch not taken
     */
    virtual bool make_prediction(string block) = 0;
    virtual void update(string block, bool guess, bool actual) = 0;
    virtual void print() = 0;

protected:
    Stats* stats;
    string command = "./sim";
};


#endif //MP2_BRANCH_PREDICTOR_H
