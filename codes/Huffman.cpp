#include "Huffman.h"
#include <set>
#include <iostream>

Huffman::Huffman(const std::wstring &text1) : CodeItem(text1) {
    generateCodes();
}

void Huffman::generateCodes() {
    std::multiset<Node> q;
    for (const auto &p : this->symbolsTable) {
        q.emplace(p.second.first, std::list<wchar_t>(1, p.first));
    }
    while (q.size() > 1) {
        Node first = *q.cbegin();
        q.erase(q.cbegin());
        Node second = *q.cbegin();
        q.erase(q.cbegin());
        for (const auto ch : first.letters) {
            this->codes[ch].push_front(true);
        }
        for (const auto ch : second.letters) {
            this->codes[ch].push_front(false);
        }
        q.insert(std::move(first) + std::move(second));
    }
}

const std::wstring &Huffman::getText() const {
    return text;
}

const std::vector<std::pair<wchar_t, std::list<bool>>> Huffman::getSortedCodes() const {
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
