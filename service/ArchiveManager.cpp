//
// Created by margo on 20.03.2019.
//

#include "ArchiveManager.h"
#include <iostream>

ArchiveManager::ArchiveManager(const std::wstring &_text,
                               const std::unordered_map<wchar_t, std::pair<long long int, double>> &_symbolsTale,
                               const std::unordered_map<wchar_t, std::list<bool>> &_codes,
                               const char *encodeFileName, const char *decodeFileName) :
        text(_text), symbolsTable(_symbolsTale), codes(_codes),
        encodeFileName(encodeFileName == nullptr ? "defaultEncode.MosquitoRar" : encodeFileName),
        decodeFileName(decodeFileName == nullptr ? "defaultDecode.txt" : decodeFileName) {
    std::cout << encodeFileName << std::endl << decodeFileName << std::endl;
    std::cout << "ASDASD" << std::endl;
    encode();
    decode();
}

void ArchiveManager::encode() {
    std::cout << encodeFileName << std::endl << decodeFileName << std::endl;
    std::cout << "ASDASD" << std::endl;
}

void ArchiveManager::decode() {
    std::cout << encodeFileName << std::endl << decodeFileName << std::endl;
    std::cout << "ASDASD" << std::endl;
}

