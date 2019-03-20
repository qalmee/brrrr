#include "CodeItem.h"

CodeItem::CodeItem(const std::wstring &text1) : text(text1) {
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

const std::unordered_map<wchar_t, std::pair<int64_t, double>> &CodeItem::getSymbolsTable() const {
    return this->symbolsTable;
}

const std::unordered_map<wchar_t, std::list<bool>> &CodeItem::getCodes() const {
    return this->codes;
}

