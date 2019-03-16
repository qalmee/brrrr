//
// Created by margo on 15.03.2019.
//

#include "CodeItem.h"

CodeItem::CodeItem(std::wstring text1) : text(std::move(text1)) {
    if (this->text.empty()) {
        throw std::runtime_error("Text is empty");
    }
    for (const wchar_t &ch : this->text) {
        symbolsTable[ch].first++;
    }
    for (auto &p : symbolsTable) {
        p.second.second = (double) p.second.first / this->text.size();
    }
}

const std::unordered_map<wchar_t, std::pair<long long int, double>> &CodeItem::getSymbolsTable() const {
    return this->symbolsTable;
}

const std::unordered_map<wchar_t, std::list<bool>> &CodeItem::getCodes() const {
    return this->codes;
}
