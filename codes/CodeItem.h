#ifndef UNTITLED2_CODEITEM_H
#define UNTITLED2_CODEITEM_H

#include <unordered_map>
#include <list>
#include <string>
#include <vector>

class CodeItem {
public:

    explicit CodeItem(const std::wstring &text1);

    explicit CodeItem() = delete;

    CodeItem(const CodeItem &item) = default;

    virtual ~CodeItem() = default;

    virtual const std::vector<std::pair<wchar_t, std::list<bool>>> getSortedCodes() const = 0;

    virtual const std::unordered_map<wchar_t, std::list<bool>> &getCodes() const;

    virtual const std::unordered_map<wchar_t, std::pair<int64_t, double>> &getSymbolsTable() const;

protected:
    virtual void generateCodes() = 0;

    const std::wstring &text;
    std::unordered_map<wchar_t, std::pair<int64_t, double>> symbolsTable;
    std::unordered_map<wchar_t, std::list<bool>> codes;
};

#endif //UNTITLED2_CODEITEM_H
