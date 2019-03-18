//
// Created by margo on 18.03.2019.
//

#ifndef UNTITLED2_TERNARYHUFFMAN_H
#define UNTITLED2_TERNARYHUFFMAN_H

#include "CodeItem.h"

class TernaryHuffman : public CodeItem {
public:
    explicit TernaryHuffman(const std::wstring &text);

    TernaryHuffman(const TernaryHuffman &huffman) = default;

    ~TernaryHuffman() override = default;

    TernaryHuffman &operator=(const TernaryHuffman &huffman);

    const std::wstring &getText() const;

    const std::vector<std::pair<wchar_t, std::list<bool>>> getSortedCodes() const override;

    const std::vector<std::pair<wchar_t, std::list<short>>> getSortedTernaryCodes() const;

protected:
    void generateCodes() override;

private:
    struct Node {
        long long freq;
        std::list<wchar_t> letters;

        Node() : freq(0) {

        }

        Node(const long long freq, std::list<wchar_t> &&letters) noexcept :
                freq(freq), letters(std::move(letters)) {}

        Node(const Node &other) noexcept {
            freq = other.freq;
            letters = other.letters;
        }

        friend bool operator<(const Node &a, const Node &b) {
            return a.freq < b.freq;
        }

        friend Node operator+(Node &&a, Node &&b) {
            b.letters.splice(b.letters.cbegin(), a.letters);
            Node node(a.freq + b.freq, std::move(b.letters));
            return node;
        }
    };
};


#endif //UNTITLED2_TERNARYHUFFMAN_H