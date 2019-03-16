//
// Created by margo on 14.03.2019.
//

#include "Fano.h"
#include <algorithm>
#include <iostream>

Fano::Fano(const std::wstring &text1) : CodeItem(text1) {
    generateCodes();
}

void Fano::generateCodes() {
    schema.reserve(this->symbolsTable.size());
    for (const auto &t : this->symbolsTable) {
        schema.push_back(t.first);
    }
    std::sort(schema.begin(), schema.end(), [mp = (this->symbolsTable)](const wchar_t a, const wchar_t b) {
        return mp.at(a).first > mp.at(b).first;
    });

    schemaCumulative.resize(schema.size(), 0);
    for (size_t i = 0; i < schema.size(); i++) {
        schemaCumulative[i] = (i != 0 ? schemaCumulative[i - 1] : 0) + symbolsTable[schema[i]].first;
    }
    if (!schema.empty()) dfs(0, (int) schema.size());
}

void Fano::dfs(int start, int end) {
    int border = start;
    for (auto i = start + 1; i < end; i++) {
        long long leftBorder = schemaCumulative[border] - (start == 0 ? 0 : schemaCumulative[start - 1]);
        long long rightBorder = schemaCumulative[end - 1] - schemaCumulative[border];
        long long leftI = schemaCumulative[i] - (start == 0 ? 0 : schemaCumulative[start - 1]);
        long long rightI = schemaCumulative[end - 1] - schemaCumulative[i];
        if (llabs(leftBorder - rightBorder) > llabs(leftI - rightI)) {
            border = i;
        }
    }
    for (auto i = start; i <= border; i++) {
        this->codes[schema[i]].push_back(false);
    }
    for (auto i = border + 1; i < end; i++) {
        this->codes[schema[i]].push_back(true);
    }
    if (border - start > 0) {
        dfs(start, border + 1);
    }
    if (end - border > 2) {
        dfs(border + 1, end);
    }
}

const std::vector<std::pair<wchar_t, std::list<bool>>> Fano::getSortedCodes() const {
    std::vector<std::pair<wchar_t, std::list<bool>>> v;
    v.reserve(this->codes.size());
    for (const auto &p : schema) {
        v.emplace_back(p, this->codes.at(p));
    }

    return v;
}
