//
// Created by margo on 03.04.2019.
//

#include "BlockCode.h"
#include <iostream>

BlockCode::BlockCode(const std::wstring &s, const int32_t blockSize_) :
        CodeItem(s), blockSize(blockSize_) {
    generateCodes();
    std::cout << text.size() << std::endl;
}

const std::vector<std::pair<wchar_t, std::list<bool>>> BlockCode::getSortedCodes() const {
    return std::vector<std::pair<wchar_t, std::list<bool>>>();
}

void BlockCode::generateCodes() {
    //blockTable.reserve(text.size() / blockSize * 4);
    for (size_t i = 0; i < text.size(); i += blockSize) {
        std::wstring t;
        t.reserve(blockSize);
        for (int32_t j = 0; j < blockSize; j++) {
            t.push_back(text[i + j]);
        }
        blockTable[t].first++;
    }
    for (auto &pair : blockTable) {
        pair.second.second = (double) pair.second.first / (text.size() / blockSize);
    }
    double cml = 0;
    for (auto &pair : blockTable) {
        blockCodes[pair.first] = getCode(cml, countPowerOfTwo(pair.second.second));
        cml += pair.second.second;
    }
    std::cout << "check = " << cml << std::endl;
}

const std::map<std::wstring, std::list<bool>> &BlockCode::getBlockCodes() const {
    return blockCodes;
}

std::list<bool> BlockCode::getCode(long double p, int32_t l) {
    std::list<bool> code;
    long double val = 0.5l;
    for (int32_t i = 0; i < l; i++) {
        if (p >= val) {
            p -= val;
            code.push_back(true);
        } else {
            code.push_back(false);
        }
        val /= 2.0L;
    }
    return code;
}

int32_t BlockCode::countPowerOfTwo(long double p) {
    int32_t l = 0;
    for (long double val = 1; val > p; val /= 2.0L) {
        l++;
    }
    return l;
}

const std::map<std::wstring, std::pair<int64_t, double>> &BlockCode::getBlockTable() const {
    return blockTable;
}

std::vector<std::pair<std::wstring, std::list<bool>>> BlockCode::getSortedBlockCodes() const {
    std::vector<std::pair<std::wstring, std::list<bool>>> v;
    v.reserve(blockCodes.size());
    for (const auto &pair : blockCodes) {
        v.emplace_back(pair);
    }
    std::sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
        return a.first < b.first;
    });
    return v;
}

int32_t BlockCode::getBlockSize() const {
    return blockSize;
}

