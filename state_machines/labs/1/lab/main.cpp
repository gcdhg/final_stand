#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <set>

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
        return (other.GetIndex() > this->GetIndex()) &&
               ((other.GetPopcount() - this->GetPopcount()) == 1) &&
               (this->GetDiffPopcount(other) == 1) &&
               (this->GetPatch() == other.GetPatch());
    }

    uint16_t GetDiffPopcount(const Implicant& other) const {
        uint16_t diff = (other.GetIndex() > this->GetIndex())
                        ? other.GetIndex() - this->GetIndex()
                        : this->GetIndex() - other.GetIndex();

        return CountOnes16(diff);
    }

    bool operator==(const Implicant &rhs) const {
        return index_ == rhs.index_ &&
               value_ == rhs.value_ &&
               was_patched_ == rhs.was_patched_ &&
               patch_ == rhs.patch_;
    }

    bool operator!=(const Implicant &rhs) const {
        return !(rhs == *this);
    }


    // Non-const functions
    // Really sorry to write them
    // But life's hard, eh?


    Implicant Patch(Implicant& other) {
        if (this->CanPatch(other)) {
            this->was_patched_ = true;
            other.SetPatched(true);
            return Implicant(*this, this->GetPatch() + other.GetIndex() - this->GetIndex());
        } else {
            throw runtime_error("Can't patch. Please, use Implicant::CanPatch/1 before calling Implicant::Patch");
        }
    }

    void SetPatched(bool value) {
        this->was_patched_ = value;
    }
};

void PrintVariables(std::ostream& stream, uint8_t count ) {
    for (uint8_t i = 0; i < count; i++) {
        stream << VARIABLE_NAMES[i];
    }
    stream << endl;
}

void PrintImplicant(const Implicant& implicant, uint8_t count) {
    char value = LogicValueToChar(implicant.GetValue());

    for (uint8_t i = 0; i < count; i++) {
        cout << value;
    }
    cout << endl;
}

void PrintSet(set<Implicant>& vec) {
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

string ImplicantStringRepr(const Implicant &source) {
    return (
        string("[") +
        to_string(source.GetIndex()) +
        string(";") +
        to_string(source.GetPopcount()) +
        string(";") +
        to_string(source.GetPatch()) +
        string("]")
    );
}

string ImplicantToString(const Implicant& source, uint8_t size) {
    string result("");

    for (uint8_t i = 0; i < size; i++) {
        bool patched = (source.GetPatch() & (0x1 << i)) >> i;
        uint8_t value = (source.GetIndex() & (0x1 << i)) >> i;

        if (patched) {
            result.insert(0, "-");
        } else if (value == 1) { // Yes, those are conditionals
            result.insert(0, "1");
        } else { // Yes, it is a *better* design than doing casts and other dirty tricks
            result.insert(0, "0");
        }
    }

    return result;
}


void PatchVectors(vector<Implicant>& source, vector<Implicant>& target, bool verbose = false) {
    for (uint16_t i = 0; i < source.size(); i++) {
        for (uint16_t j = i + 1; j < source.size(); j++) {
            if (source[i].CanPatch(source[j])) {
                target.push_back(source[i].Patch(source[j]));

                if (verbose) {
                    cout << "Patching " << ImplicantStringRepr(source[i]) << " with " << ImplicantStringRepr(source[j]) << endl;
                }
            }
        }
    }

    for (uint16_t i = 0; i < source.size(); i++) {
        if (!source[i].WasPatched()) {

            if (verbose) {
                cout << "Adding unpached value: " << ImplicantStringRepr(source[i]) << endl;
            }
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

    PrintVariables(cout, (uint8_t) function_size);

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

    // M3: patch M2 once

    cout << "M3:" << endl;
    

    vector<Implicant> m_3;

    PatchVectors(m_2, m_3);

    PrintVector(m_3);

    cout << endl;

    uint16_t patched_implicants = 0;

    int tmp = 0;

    // M4:  patch M3 until no patching is possible

    cout << "M4: " << endl;

    vector<Implicant> m_4;
    vector<Implicant> m_4_prev;

    transform(m_3.begin(), m_3.end(), back_inserter(m_4_prev), [](Implicant x) {
        x.SetPatched(false);
        return x;
    });

    do {
        // Clear M4 before doing anything

        m_4.clear();

        PatchVectors(m_4_prev, m_4);

        // Clean up: set m_4_prev, calculate patched implicants

        m_4_prev.clear();

        transform(m_4.begin(), m_4.end(), back_inserter(m_4_prev), [](Implicant x) {
            x.SetPatched(false);
            return x;
        });

        // remove duplicates

        vector<Implicant> tmpvec(m_4_prev);

        m_4_prev.clear();

        for_each(tmpvec.begin(), tmpvec.end(), [&tmpvec, &m_4_prev](Implicant x) {
            int count_source = accumulate(tmpvec.begin(), tmpvec.end(), 0, [&x](int acc, const Implicant& y) {
                return (x == y) ? acc + 1 : acc;
            });
            bool dest_contains = accumulate(m_4_prev.begin(), m_4_prev.end(), false, [&x](bool acc, const Implicant& y) {
                return acc || (x == y);
            });
            if (count_source == 1 || !dest_contains) {
                m_4_prev.push_back(x);
            }
        });

        patched_implicants = accumulate(m_4.begin(), m_4.end(), (uint16_t) 0, [](uint16_t acc, const Implicant &x) {
            return (x.WasPatched()) ? acc + 1 : acc;
        });
    } while(patched_implicants > 0 && (++tmp) < 10);

    PrintVector(m_4);

    cout << endl;

    // Cleaning up

    cout << "--------------------------";
    cout << "MDNF:" << endl;

    vector<Implicant> mdnf_source;

    remove_copy_if(func.begin(), func.end(), back_inserter(mdnf_source), [](const Implicant& x) {
        return (x.GetValue() == INDETERMINATE);
    });

    // Remove redundant dnf implicants
    vector<Implicant> mdnf_m;

    remove_copy_if(m_4.begin(), m_4.end(), back_inserter(mdnf_m), [&m_4, &mdnf_source, &func](const Implicant& x) {

        vector<Implicant> other_implicants;
        remove_copy_if(m_4.begin(), m_4.end(), back_inserter(other_implicants), [&x](const Implicant& y) {
            return x == y;
        });

        // Function values covered by x
        vector<Implicant> covered_by_x;
        remove_copy_if(func.begin(), func.end(), back_inserter(covered_by_x), [&x](const Implicant& y) {
            return ((y.GetIndex() & ~x.GetPatch()) != x.GetIndex()) || y.GetValue() != TRUE;
        });

        // Check if every implicant is covered
        bool everything_is_covered = accumulate(covered_by_x.begin(), covered_by_x.end(), true, [&other_implicants](bool acc, const Implicant& y) {
            bool covered = accumulate(other_implicants.begin(), other_implicants.end(), false, [&y](bool acc, const Implicant& z) {
                return acc || ((y.GetIndex() & ~z.GetPatch()) == z.GetIndex());
            });

            return acc && covered;
        });

        return everything_is_covered;
    });

    cout << "Implicants after redundant were removed:" << endl;

    PrintVector(mdnf_m);

    cout << setw(10) << " ";

    cout << endl;

    PrintVariables(cout, (uint8_t) function_size);
    PrintVariables(mdnf, (uint8_t) function_size);

    for_each(mdnf_m.begin(), mdnf_m.end(), [&function_size, &mdnf](const Implicant& x) {
        cout << ImplicantToString(x, function_size) << endl;
        mdnf << ImplicantToString(x, function_size) << endl;
    });

    scale.close();
    mdnf.close();

    return 0;
}