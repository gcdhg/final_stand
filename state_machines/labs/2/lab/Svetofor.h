#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

const int NO_TRANSITION_IDENTIFICATOR = 9;


vector<string> outputs = { "G\tr","YL\tr","YL\tr","R\tg","R\tyl","R\tyl" };


class svetofor_sm {
private:
    int initial_state;
    int current_state;

    vector< vector<int> > state_table;

public:
    svetofor_sm(const string& filename, int initial_state) : initial_state(initial_state), current_state(initial_state) {
        ifstream file(filename);

        string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                vector<int> buff;

                istringstream ss(line);
                copy(istream_iterator<int>(ss), istream_iterator<int>(), back_inserter(buff));

                state_table.push_back(buff);
            }
        }
        else {
            std::cout << "ERROR: can't open " << filename << std::endl;
        }

    }

    const vector< vector<int> > getStateTable() const {
        return state_table;
    }

    int getInitialState() const {
        return initial_state;
    }

    int getState() const {
        return current_state;
    }

    void reset() {
        current_state = getInitialState();
    }

    void changeState(int input) {
        if (state_table[input][getState()] != NO_TRANSITION_IDENTIFICATOR) {
            current_state = state_table[input][getState()];
        }
    }

    string getResult() const {
        return outputs[getState()];
    }
};