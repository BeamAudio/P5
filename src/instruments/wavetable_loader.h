#ifndef WAVETABLE_LOADER_H
#define WAVETABLE_LOADER_H

#include <string>
#include <vector>
#include <map>

namespace upc {
    class WavetableLoader {
    private:
        std::map<std::string, std::vector<float>> cache;
        WavetableLoader() {}
        
    public:
        // Singleton access
        static WavetableLoader& getInstance();
        
        // Load a wavetable from a file (or return cached version)
        // Returns a pointer to the vector, or nullptr/empty vector on failure
        const std::vector<float>* load(const std::string& filename);
    };
}

#endif
