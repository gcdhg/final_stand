#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const char VARIABLE_NAMES[16] = {
        'x', 'y', 'z',
        'a', 'b', 'c',
        'd', 'e', 'f',
        'g', 'h', 'i',
        'u', 'v', 'p',
        'q'
};

#ifdef __GNUG__

uint16_t CountOnes16(uint16_t input) {
    return __builtin_popcount(input);
}

#else

uint16_t CountOnes16(uint16_t input) {
    return (uint16_t) (
        ((input & 0x1)) +
        ((input & 0x2) >> 1) +
        ((input & 0x4) >> 2) +
        ((input & 0x8) >> 3) +
        ((input & 0x10) >> 4) +
        ((input & 0x20) >> 5) +
        ((input & 0x30) >> 6) +
        ((input & 0x40) >> 7) +
        ((input & 0x50) >> 8) +
        ((input & 0x60) >> 9) +
        ((input & 0x70) >> 10) +
        ((input & 0x80) >> 11) +
        ((input & 0x90) >> 12) +
        ((input & 0xA0) >> 13) +
        ((input & 0xB0) >> 14) +
        ((input & 0xC0) >> 15)
    );
}

#endif

enum LogicValue {
    FALSE,
    TRUE,
    INDETERMINATE
};

LogicValue LogicValueFromChar(char input) {
    switch (input) {
        case '0': return FALSE;
        case '1': return TRUE;
        case '-': return INDETERMINATE;
        default: {
            const string error = (string) "Invalid DNF value: " + input;
            throw runtime_error(error);
        }
    }
}

char LogicValueToChar(LogicValue input) {
    switch (input) {
        case FALSE: return '0';
        case TRUE: return '1';
        case INDETERMINATE: return '-';
    }
}

class Implicant {
private:
    uint16_t index_;
    LogicValue value_;
public:
    Implicant(uint16_t index, LogicValue value) : index_(index), value_(value) {
    }

    uint16_t GetIndex() const {
        return this->index_;
    }

    LogicValue GetValue() const {
        return this->value_;
    }

    uint16_t GetPopcount() const {
        return CountOnes16(this->GetIndex());
    }

    uint16_t GetDiffPopcount(const Implicant& other) const {
        uint16_t diff = (other.GetValue() > this->GetValue())
            ? other.GetValue() - this->GetValue()
            : this->GetValue() - other.GetValue();

        return CountOnes16(diff);
    }
};

void PrintVariables(uint8_t count ) {
    for (uint8_t i = 0; i < count; i++) {
        cout << VARIABLE_NAMES[i];
    }
    cout << endl;
}

void PrintImplicant(const Implicant& implicant, uint8_t count) {
    char value = LogicValueToChar(implicant.GetValue());

    for (uint8_t i = 0; i < count; i++) {
        cout << value;
    }
    cout << endl;
}   

int main() {
    ifstream scale("scale.txt");
    ofstream mdnf("mdnf.txt");
    string buff;
    vector<Implicant> func;

    uint16_t idx = 0;

    // actual reading

    getline(scale, buff);


    transform(buff.begin(), buff.end(), back_inserter(func), [&idx](char x) {
        return Implicant(idx++, LogicValueFromChar(x));
    });

    uint8_t function_size = (uint8_t) log2(func.size());

    // Debug output

    cout << "Loaded function of " << (uint16_t) function_size << " arguments:" << endl;

    cout << buff << endl;

    for_each(func.begin(), func.end(), [](Implicant x) {
        cout << LogicValueToChar(x.GetValue());
    });

    cout << endl << endl;

    cout << "Truth table for the function:" << endl;

    PrintVariables((uint8_t) function_size);

    for_each(func.begin(), func.end(), [&function_size](Implicant x) {
        PrintImplicant(x, function_size);
    });

    cout << endl << endl;

    // M1: filter out false values. Consider '-' as '1'

    vector<Implicant> m_1;

    remove_copy_if(func.begin(), func.end(), back_inserter(m_1), [](const Implicant& x) {
        return x.GetValue() == FALSE;
    });

    // Print

    cout << "M1:" << endl;

    cout << "N: ";

    for_each(m_1.begin(), m_1.end(), [](const Implicant& x) {
        cout << setw(2) << x.GetIndex() << " ";
    });

    cout << endl;

    cout << "P: ";
    for_each(m_1.begin(), m_1.end(), [](const Implicant& x) {
        cout << setw(2) << x.GetPopcount() << " ";
    });

    cout << endl << endl;

    // Cleaning up

    scale.close();
    mdnf.close();

    return 0;
}