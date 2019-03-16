//
// Created by margo on 14.03.2019.
//

#include "ShannonInterface.h"

#include <iostream>

ShannonInterface::ShannonInterface(const std::wstring &text1,
                                   const std::function<bool(const trio &, const trio &)> &comp)
        : CodeItem(text1), compFuntion(comp) {
    generateCodes();
}

const std::vector<std::pair<wchar_t, std::list<bool>>> ShannonInterface::getSortedCodes() const {
    std::vector<std::pair<wchar_t, std::list<bool>>> v;
    v.reserve(schema.size());
    for (const auto &row : schema) {
        v.emplace_back(row.symbol, this->codes.at(row.symbol));
    }
    return v;
}

void ShannonInterface::generateCodes() {
    schema.reserve(this->symbolsTable.size());
    for (const auto &p : this->symbolsTable) {
        schema.emplace_back(p.first, p.second.second, countPowerOfTwo(p.second.second));
    }
    std::sort(schema.begin(), schema.end(), compFuntion);
    long double cml = 0.0L;
    for (const auto &row : schema) {
        this->codes[row.symbol] = getCode(cml, row.powerOfTwo);
        cml += row.p;
    }
}

int ShannonInterface::countPowerOfTwo(long double p) {
    int l = 0;
    for (long double val = 1; val > p; val /= 2.0L) {
        l++;
    }
    return l;
}

std::list<bool> ShannonInterface::getCode(long double p, int l) {
    std::list<bool> code;
    long double val = 0.5l;
    for (int i = 0; i < l; i++) {
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

ShannonInterface::~ShannonInterface() = default;