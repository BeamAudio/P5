#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

namespace Utils {

    vector<float> load_wavetable(std::string filename) {
        //load from .wtb file to a vector of floats
        vector<float> wavetable;
        
        //the .wtb file is a text file with floats separated by spaces
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open wavetable file " << filename << endl;
            return wavetable;
        }
        float value;
        while (file >> value) {
            wavetable.push_back(value);
        }
        file.close();
        return wavetable;
    }
}