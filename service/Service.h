#ifndef UNTITLED2_SERVICE_H
#define UNTITLED2_SERVICE_H

#include <string>
#include <fstream>
#include <unordered_map>
#include <list>
#include <map>

class Service {
public:
    Service() = delete;

    static long double
    anyEntropy(const std::wstring &s, size_t width = 1, bool binaryLog = true, std::wofstream *fout = nullptr);

    static std::wstring prepString(const std::wstring &in);

    static double avgLenOfCode(const std::unordered_map<wchar_t, std::pair<int64_t, double>> &symbols,
                               const std::unordered_map<wchar_t, std::list<bool>> &codes);

    static double avgLenOfCode(const std::map<std::wstring, std::pair<int64_t, double>> &symbols,
                               const std::map<std::wstring, std::list<bool>> &codes);

    static void gen();

    static wchar_t to_lower(wchar_t ch);

    static inline long double log3(long double x);

private:
    struct schemaAnyItem {
        std::wstring sequence;
        int64_t count;
        long double p;
    };
};


#endif //UNTITLED2_SERVICE_H
