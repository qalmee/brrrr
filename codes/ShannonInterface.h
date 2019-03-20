#ifndef UNTITLED2_SHANNON_H
#define UNTITLED2_SHANNON_H


#include "CodeItem.h"
#include <list>
#include <functional>

class ShannonInterface : public CodeItem {
protected:
    struct trio;
public:

    explicit ShannonInterface(const std::wstring &text1, const std::function<bool(const trio &, const trio &)> &comp);

    const std::vector<std::pair<wchar_t, std::list<bool>>> getSortedCodes() const override;

    ~ShannonInterface() override = 0;

protected:
    void generateCodes() override;

    struct trio {
        long double p;
        int32_t powerOfTwo;
        wchar_t symbol;

        trio(wchar_t a, long double b, int32_t c) : p(b), powerOfTwo(c), symbol(a) {}

    };

private:

    std::function<bool(const trio &, const trio &)> compFuntion;

    int32_t countPowerOfTwo(long double p);

    std::list<bool> getCode(long double p, int32_t l);

    std::vector<trio> schema;
};


#endif //UNTITLED2_SHANNON_H
