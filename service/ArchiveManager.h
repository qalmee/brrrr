//
// Created by margo on 20.03.2019.
//

#ifndef UNTITLED2_COMPRESSER_H
#define UNTITLED2_COMPRESSER_H

#include <fstream>
#include <unordered_map>
#include <list>

class ArchiveManager {
public:
    ArchiveManager() = delete;

    ArchiveManager(const std::wstring &_text,
                   const std::unordered_map<wchar_t, std::pair<long long int, double>> &_symbolsTale,
                   const std::unordered_map<wchar_t, std::list<bool>> &_codes,
                   const char *encodeFileName, const char *decodeFileName);

    ~ArchiveManager() = default;


private:
    const std::wstring &text;
    std::fstream fCoded;
    const std::unordered_map<wchar_t, std::pair<long long, double>> &symbolsTable;
    const std::unordered_map<wchar_t, std::list<bool>> &codes;
    const char *encodeFileName, *decodeFileName;

    void encode();

    void decode();

};


#endif //UNTITLED2_COMPRESSER_H
