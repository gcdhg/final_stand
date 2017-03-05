#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ifstream scale("scale.txt");
    ofstream mdnf("mdnf.txt");
    string buff;
    vector<uint16_t> func;

    getline(scale, buff);

    transform(buff.begin(), buff.end(), back_inserter(func), [](char x) {
        switch (x) {
            case '0': return 0;
            case '1': case '-': return 1;
            default: {
                const string error = (string) "Invalid DNF value: " + x;
                throw runtime_error(error);
            }
        }
    });

    uint16_t function_size = (uint16_t) log2(func.size());

    cout << "Loaded function of " << function_size << " arguments:" << endl;

    cout << buff << endl;

    for_each(func.begin(), func.end(), [](uint16_t x) {
        cout << x;
    });

    scale.close();
    mdnf.close();

    return 0;
}