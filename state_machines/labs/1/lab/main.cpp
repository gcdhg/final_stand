#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <numeric>

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
    bool was_patched_;
    uint16_t patch_;

    Implicant(const Implicant& src, uint16_t patch) {
        this->index_ = src.GetIndex();
        this->value_ = src.GetValue();
        this->was_patched_ = src.WasPatched();
        this->patch_ = patch;
    }

public:
    Implicant(uint16_t index, LogicValue value) : index_(index), value_(value) {
        this->was_patched_ = false;
        this->patch_ = 0;
    }

    Implicant(const Implicant& other) {
        this->index_ = other.GetIndex();
        this->value_ = other.GetValue();
        this->was_patched_ = other.WasPatched();
        this->patch_ = other.GetPatch();
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

    uint16_t GetPatch() const {
        return this->patch_;
    }

    bool WasPatched() const {
        return this->was_patched_;
    }

    bool CanPatch(const Implicant& other) const {
        return (other.GetIndex() > this->GetIndex() &&
                this->GetDiffPopcount(other) == 1 &&
                this->GetPatch() == other.GetPatch());
    }

    uint16_t GetDiffPopcount(const Implicant& other) const {
        uint16_t diff = (other.GetIndex() > this->GetIndex())
                        ? other.GetIndex() - this->GetIndex()
                        : this->GetIndex() - other.GetIndex();

        return CountOnes16(diff);
    }

    // Non-const functions
    // Really sorry to write them
    // But life's hard, eh?


    Implicant Patch(Implicant& other) {
        // TODO: properly mutate the properties
        // It seems not to be working correctly
        if (this->CanPatch(other)) {
            this->was_patched_ = true;
            other.SetPatched(true); // those with the flag will be removed
            return Implicant(*this, other.GetIndex() - this->GetIndex());
        } else {
            throw runtime_error("Can't patch. Please, use Implicant::CanPatch/1 before calling Implicant::Patch");
        }
    }

    void SetPatched(bool value) {
        this->was_patched_ = value;
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

void PrintVector(vector<Implicant>& vec) {
    cout << "N: ";

    for_each(vec.begin(), vec.end(), [](const Implicant& x) {
        cout << setw(2) << x.GetIndex() << " ";
    });

    cout << endl;

    cout << "I: ";
    for_each(vec.begin(), vec.end(), [](const Implicant& x) {
        cout << setw(2) << x.GetPopcount() << " ";
    });

    cout << endl;
    cout << "P: ";
    for_each(vec.begin(), vec.end(), [](const Implicant& x) {
        cout << setw(2) << x.GetPatch() << " ";
    });


    cout << endl;
    cout << "W: ";
    for_each(vec.begin(), vec.end(), [](const Implicant& x) {
        cout << setw(2) << x.WasPatched() << " ";
    });

    cout << endl;
}

void PatchVectors(vector<Implicant>& source, vector<Implicant>& target) {
    for (uint16_t i = 0; i < source.size(); i++) {
        for (uint16_t j = i + 1; j < source.size(); j++) {
            if (source[i].CanPatch(source[j])) {
                target.push_back(source[i].Patch(source[j]));

//                cout << "Patching " << source[i].GetIndex() << " with " << source[j].GetIndex() << endl;
            }
        }
    }

    for (uint16_t i = 0; i < source.size(); i++) {
        if (!source[i].WasPatched()) {
//            cout << "Adding unpached value: " << source[i].GetIndex() << endl;
            target.push_back(Implicant(source[i]));
        }
    }
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

    PrintVector(m_1);

    cout << endl;

    // M2: Patching values

    cout << "M2:" << endl;

    vector<Implicant> m_2;

    PatchVectors(m_1, m_2);

    PrintVector(m_2);

    cout << endl;

    // M3: patch M2 until no patching is possible

    cout << "M3:" << endl;

    vector<Implicant> m_3_prev;

    transform(m_2.begin(), m_2.end(), back_inserter(m_3_prev), [](Implicant x) {
        x.SetPatched(false);
        return x;
    });



    // TODO: It *IS* bugged. M3 size keeps growing. Apparently, Patch is not working correctly.
    
    vector<Implicant> m_3;

    uint16_t patched_implicants = 0;

    int tmp = 0;

    do {

        cout << "A new attempt to minimize M3. Patched implicants: " << patched_implicants << endl;

        // Clear M3 before doing anything

        m_3.clear();

        PatchVectors(m_3_prev, m_3);

        // Clean up: set m_3_prev, calculate patched implicants

        m_3_prev.clear();

        transform(m_3.begin(), m_3.end(), back_inserter(m_3_prev), [](Implicant x) {
            x.SetPatched(false);
            return x;
        });

        patched_implicants = accumulate(m_3.begin(), m_3.end(), (uint16_t) 0, [](uint16_t acc, const Implicant &x) {
            return (x.WasPatched()) ? acc + 1 : acc;
        });
    } while(patched_implicants > 0 && (++tmp) < 2);


    cout << "Patched implicants: " << patched_implicants << endl;

    PrintVector(m_3);

    cout << endl;

    // Cleaning up

    scale.close();
    mdnf.close();

    return 0;
}