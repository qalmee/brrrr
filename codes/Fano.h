#ifndef UNTITLED2_FANO_H
#define UNTITLED2_FANO_H


#include "CodeItem.h"
#include <vector>

class Fano : public CodeItem {
public:
    explicit Fano(const std::wstring &text);

    const std::vector<std::pair<wchar_t, std::list<bool>>> getSortedCodes() const override;

    ~Fano() override = default;

protected:
    void generateCodes() override;

private:

    std::vector<wchar_t> schema;
    std::vector<int64_t> schemaCumulative;

    void dfs(int32_t start, int32_t end);
};


#endif //UNTITLED2_FANO_H
