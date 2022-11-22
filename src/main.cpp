#include <iostream>
#include <fstream>
#include "predictors/Predictor.h"
#include "predictors/SmithPredictor.h"

int main(int argc, char **argv) {
    Predictor* predictor = nullptr;

    string predictor_type = argv[1];
    string trace_file;
    if(predictor_type == "smith") {
        trace_file = argv[3];
        predictor = new SmithPredictor(atoi(argv[2]), argv[3]);
    }

    ifstream file(trace_file);
    string line;
    bool prediction;
    if(file.is_open()) {
        while (getline(file, line)) {
            int space = line.find(' ');
            string block = line.substr(0, space);
            bool actual = line.substr(space + 1) == "t";
            prediction = predictor->make_prediction(block);
            predictor->update(block, prediction, actual);
        }
        predictor->print();
    }
}
