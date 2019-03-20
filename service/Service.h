//
// Created by margo on 20.03.2019.
//

#ifndef UNTITLED2_SERVICE_H
#define UNTITLED2_SERVICE_H

#include <string>
#include <fstream>
#include <unordered_map>
#include <list>

namespace std {
    template<>
    struct hash<pair<wchar_t, wchar_t>> {
        size_t operator()(const pair<wchar_t, wchar_t> &a) const {
            return hash<long long>{}(((size_t)
            a.first << 32) +a.second);
        }
    };
}

class Service {
public:
    Service() = delete;

    static double
    anyEntropy(const std::wstring &s, size_t width = 1, bool binaryLog = true, std::wofstream *fout = nullptr);

    static std::wstring prepString(const std::wstring &in);

    static double avgLenOfCode(const std::unordered_map<wchar_t, std::pair<long long, double>> &symbols,
                               const std::unordered_map<wchar_t, std::list<bool>> &codes);

    static void gen();

    static wchar_t to_lower(wchar_t ch);

    static inline double log3(double x);

private:
    struct schemaAnyItem {
        std::wstring sequence;
        long long count;
        double p;
    };
};


#endif //UNTITLED2_SERVICE_H
