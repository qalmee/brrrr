#ifndef UNTITLED2_TERNARYHUFFMAN_H
#define UNTITLED2_TERNARYHUFFMAN_H

#include "CodeItem.h"

class TernaryHuffman : public CodeItem {
public:
    explicit TernaryHuffman(const std::wstring &text);

    TernaryHuffman(const TernaryHuffman &huffman) = default;

    ~TernaryHuffman() override = default;

    const std::wstring &getText() const;

    const std::vector<std::pair<wchar_t, std::list<bool>>> getSortedCodes() const override;

    const std::vector<std::pair<wchar_t, std::list<uint16_t>>> getSortedTernaryCodes() const;

    const std::unordered_map<wchar_t, std::list<uint16_t>> getMapCodes() const;

protected:
    void generateCodes() override;

private:
    struct Node {
        int64_t freq;
        std::list<wchar_t> letters;

        Node() : freq(0) {

        }

        Node(const int64_t freq, std::list<wchar_t> &&letters) noexcept :
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
