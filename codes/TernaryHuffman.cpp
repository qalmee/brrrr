//
// Created by margo on 18.03.2019.
//

#include "TernaryHuffman.h"
#include <set>
#include <iostream>
#include <algorithm>

TernaryHuffman::TernaryHuffman(const std::wstring &text1) : CodeItem(text1) {
    generateCodes();
}

TernaryHuffman &TernaryHuffman::operator=(const TernaryHuffman &huffman) {
    this->text = huffman.text;
    this->symbolsTable = huffman.symbolsTable;
    return *this;
}

void TernaryHuffman::generateCodes() {
    std::multiset<Node> q;
    for (const auto &p : this->symbolsTable) {
        q.emplace(p.second.first, std::list<wchar_t>(1, p.first));
    }
    while (q.size() > 1) {
        Node first, second, third;
        first = *q.cbegin();
        q.erase(q.cbegin());
        second = *q.cbegin();
        q.erase(q.cbegin());
        for (const auto ch : first.letters) {
            this->codes[ch].push_front(true);
            this->codes[ch].push_front(false);
        }
        for (const auto ch : second.letters) {
            this->codes[ch].push_front(false);
            this->codes[ch].push_front(true);
        }
        if (!q.empty()) {
            third = *q.cbegin();
            q.erase(q.cbegin());
            for (const auto ch : third.letters) {
                this->codes[ch].push_front(false);
                this->codes[ch].push_front(false);
            }
        }
        if (third.freq == 0) q.insert(std::move(first) + std::move(second));
        else q.insert(std::move(first) + std::move(second) + std::move(third));
    }
}

const std::wstring &TernaryHuffman::getText() const {
    return text;
}

const std::vector<std::pair<wchar_t, std::list<bool>>> TernaryHuffman::getSortedCodes() const {
    std::vector<std::pair<wchar_t, std::list<bool>>> v;
    v.reserve(this->codes.size());
    for (const auto &p : codes) {
        v.emplace_back(p);
    }
    std::sort(v.begin(), v.end(), [mp = &(this->symbolsTable)](const auto &a, const auto &b) {
        return mp->at(a.first).first > mp->at(b.first).first;
    });
    return v;
}

const std::vector<std::pair<wchar_t, std::list<short>>> TernaryHuffman::getSortedTernaryCodes() const {
    std::vector<std::pair<wchar_t, std::list<short>>> v;
    v.reserve(this->codes.size());
    for (const auto &p : codes) {
        std::list<short> list;
        for (auto it = p.second.cbegin(); it != p.second.cend(); it = std::next(it, 2)) {
            auto it1 = it;
            it1++;
            list.push_back(((unsigned short) *it) << 1 | *it1);
        }
        v.emplace_back(p.first, list);
    }
    std::sort(v.begin(), v.end(), [mp = &(this->symbolsTable)](const auto &a, const auto &b) {
        return mp->at(a.first).first > mp->at(b.first).first;
    });
    return v;
}
