//
// Created by margo on 14.03.2019.
//

#ifndef UNTITLED2_HUFFMAN_H
#define UNTITLED2_HUFFMAN_H


#include "CodeItem.h"
#include <map>
#include <unordered_map>
#include <string>
#include <functional>

class Huffman : public CodeItem {
public:
    explicit Huffman(const std::wstring &text);

    Huffman(const Huffman &huffman) = default;

    ~Huffman() override = default;

    Huffman &operator=(const Huffman &huffman);

    const std::wstring &getText() const;

    const std::vector<std::pair<wchar_t, std::list<bool>>> getSortedCodes() const override;

protected:
    void generateCodes() override;

private:
    struct Node {
        long long freq;
        std::list<wchar_t> letters;

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


#endif //UNTITLED2_HUFFMAN_H
