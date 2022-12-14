#include <iostream>
#include <fstream>
#include "predictors/Predictor.h"
#include "predictors/SmithPredictor.h"
#include "predictors/BimodalPredictor.h"
#include "predictors/GsharePredictor.h"
#include "predictors/HybridPredictor.h"

uint32_t from_string(string basicString);

int main(int argc, char **argv) {
    Predictor* predictor = nullptr;
    string command = "";
    for(int i = 0; i < argc;  i++) {
        command = command + argv[i] + " ";
    }
    string predictor_type = argv[1];
    string trace_file;
    if(predictor_type == "smith") {
        trace_file = argv[3];
        predictor = new SmithPredictor(command, atoi(argv[2]));
    } else if (predictor_type == "bimodal") {
        trace_file = argv[3];
        predictor = new BimodalPredictor(command, atoi(argv[2]));
    } else if (predictor_type == "gshare") {
        trace_file = argv[4];
        predictor = new GsharePredictor(command, atoi(argv[2]), atoi(argv[3]));
    } else if (predictor_type == "hybrid") {
        trace_file = argv[6];
        predictor = new HybridPredictor(command, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }

    ifstream file(trace_file);
    string line;
    bool prediction;
    if(file.is_open()) {
        while (getline(file, line)) {
            int space = line.find(' ');
            string block = line.substr(0, space);
            bool actual = line.substr(space + 1) == "t";
            uint32_t addr = from_string(block);
            prediction = predictor->make_prediction(addr);
            predictor->update(addr, prediction, actual);
        }
        predictor->print();
    }
}

uint32_t from_string(string basicString) {
    uint32_t val = 0;
    for(int i = 0; i < basicString.length(); i++) {
        if(isalpha(basicString.at(i))) {
            val += tolower(basicString.at(i)) - 'a' + 10;
        } else if(isdigit(basicString.at(i))) {
            val += basicString.at(i) - '0';
        }
        val *= 16;
    }
    return val/16;
}

