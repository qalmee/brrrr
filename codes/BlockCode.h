//
// Created by margo on 03.04.2019.
//

#ifndef UNTITLED2_BLOCKCODE_H
#define UNTITLED2_BLOCKCODE_H


#include "CodeItem.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>

class BlockCode : public CodeItem {

public:

    explicit BlockCode(const std::wstring &s, int32_t blockSize_ = 5);

    const std::vector<std::pair<wchar_t, std::list<bool>>> getSortedCodes() const override;

    const std::map<std::wstring, std::list<bool>> &getBlockCodes() const;

    const std::map<std::wstring, std::pair<int64_t, double>> &getBlockTable() const;

    std::vector<std::pair<std::wstring, std::list<bool>>> getSortedBlockCodes() const;

    int32_t getBlockSize() const;

protected:
    void generateCodes() override;

private:
    std::map<std::wstring, std::list<bool>> blockCodes;
    std::map<std::wstring, std::pair<int64_t, double>> blockTable;
    int32_t blockSize;

    static std::list<bool> getCode(long double p, int32_t l);

    static int32_t countPowerOfTwo(long double p);
};


#endif //UNTITLED2_BLOCKCODE_H
