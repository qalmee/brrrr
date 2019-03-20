//
// Created by margo on 20.03.2019.
//

#ifndef UNTITLED2_COMPRESSER_H
#define UNTITLED2_COMPRESSER_H

#include <fstream>
#include <unordered_map>
#include <list>

namespace std {
    template<>
    struct hash<std::list<bool>> {
        size_t operator()(const std::list<bool> &list) const {
            unsigned long long t = 1;
            for (const bool val : list) {
                t = t << 1U | val;
            }
            return hash<unsigned long long>{}(t);
        }
    };
}

class ArchiveManager {
public:
    ArchiveManager() = delete;

    ArchiveManager(const std::wstring &_text,
                   const std::unordered_map<wchar_t, std::pair<long long int, double>> &_symbolsTale,
                   const std::unordered_map<wchar_t, std::list<bool>> &_codes,
                   const char *encodeFileName = nullptr, const char *decodeFileName = nullptr);

    ~ArchiveManager() = default;


private:
    const std::wstring &text;
    std::fstream fEncoded;
    std::wfstream fDecoded;
    const std::unordered_map<wchar_t, std::pair<long long, double>> &symbolsMetrics;
    const std::unordered_map<wchar_t, std::list<bool>> &codes;
    std::unordered_map<std::list<bool>, wchar_t> symbols;
    const char *encodeFileName, *decodeFileName;

    void encode();

    void decode();

    void fillSymbols();

    bool filesAreEqual();
};


#endif //UNTITLED2_COMPRESSER_H
