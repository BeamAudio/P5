#include "wavetable_loader.h"
#include <fstream>
#include <iostream>

using namespace std;

namespace upc {
    WavetableLoader& WavetableLoader::getInstance() {
        static WavetableLoader instance;
        return instance;
    }

    const vector<float>* WavetableLoader::load(const string& filename) {
        // Check cache first
        if (cache.find(filename) != cache.end()) {
            return &cache[filename];
        }

        // Try to open file
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open wavetable file " << filename << endl;
            // Cache an empty vector to avoid retrying failed files repeatedly
            cache[filename] = vector<float>(); 
            return &cache[filename];
        }

        vector<float> wavetable;
        float value;
        while (file >> value) {
            wavetable.push_back(value);
        }
        file.close();
        
        if (wavetable.empty()) {
             cerr << "Warning: Wavetable file " << filename << " is empty" << endl;
        } else {
             cout << "Loaded wavetable '" << filename << "' with " << wavetable.size() << " samples." << endl;
        }

        cache[filename] = wavetable;
        return &cache[filename];
    }
}
