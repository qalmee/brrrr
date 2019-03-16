//
// Created by margo on 14.03.2019.
//

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
    std::vector<long long> schemaCumulative;

    void dfs(int start, int end);
};


#endif //UNTITLED2_FANO_H
