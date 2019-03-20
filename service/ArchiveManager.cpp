//
// Created by margo on 20.03.2019.
//

#include "ArchiveManager.h"
#include <iostream>

ArchiveManager::ArchiveManager(const std::wstring &_text,
                               const std::unordered_map<wchar_t, std::pair<long long int, double>> &_symbolsTale,
                               const std::unordered_map<wchar_t, std::list<bool>> &_codes,
                               const char *encodeFileName, const char *decodeFileName) :
        text(_text), symbolsMetrics(_symbolsTale), codes(_codes),
        encodeFileName(encodeFileName == nullptr ? "defaultEncode.MosquitoRar" : encodeFileName),
        decodeFileName(decodeFileName == nullptr ? "defaultDecode.txt" : decodeFileName) {
    std::cout << this->encodeFileName << std::endl << this->decodeFileName << std::endl;
    fillSymbols();
    encode();
    decode();
    if (!filesAreEqual()) {
        std::cout << "Files ! equal" << std::endl;
        //throw std::runtime_error("files are not equal");
    }
}

void ArchiveManager::encode() {
    fEncoded.open(encodeFileName, std::ios_base::out | std::ios_base::binary);
    unsigned char byteToWrite = 0;
    unsigned char mask = 1U << (sizeof(unsigned char) * 8 - 1);
    int bitCount = 0;
    for (const auto ch : text) {
        const std::list<bool> &list = codes.at(ch);
        for (const bool val : list) {
            if (val) {
                byteToWrite |= mask;
            }
            bitCount++;
            mask >>= 1;
            if (bitCount == sizeof(unsigned char) * 8) {
                fEncoded << byteToWrite;
                byteToWrite = 0;
                bitCount = 0;
                mask = 1U << (sizeof(unsigned char) * 8 - 1);
            }
        }
    }
    if (bitCount) fEncoded << byteToWrite;
    fEncoded.close();
}

void ArchiveManager::decode() {
    fEncoded.open(encodeFileName, std::ios_base::in | std::ios_base::binary);
    fDecoded.open(decodeFileName, std::ios_base::out);
    unsigned char byteToDecode = 0;
    uint8_t byteMask = 0;
    unsigned int charsWritten = 0;
    std::list<bool> code;
    while (charsWritten < text.size()) {
        if (byteMask == 0) {
            char nextByte;
            fEncoded.readsome(&nextByte, 1);
            byteToDecode = static_cast<uint8_t>(nextByte);
            byteMask = 1U << (sizeof(uint8_t) * 8 - 1);
        }
        code.push_back((byteToDecode & byteMask) > 0);
        byteMask >>= 1;
        if (symbols.count(code) > 0) {
            fDecoded << symbols[code];
            charsWritten++;
            code.clear();
        }
    }
    fEncoded.close();
    fDecoded.close();
}

void ArchiveManager::fillSymbols() {
    symbols.reserve(codes.size() << 1U);
    for (const auto &pair : codes) {
        symbols.emplace(pair.second, pair.first);
    }
}

bool ArchiveManager::filesAreEqual() {
    std::wfstream fsDecoded;
    fsDecoded.open(decodeFileName, std::ios_base::in | std::ios_base::binary);
    std::wstring s((std::istreambuf_iterator<wchar_t>(fsDecoded)), (std::istreambuf_iterator<wchar_t>()));
    return s == text;
}

