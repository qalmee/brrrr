#include "HilbertMoore.h"

HilbertMoore::HilbertMoore(const std::wstring &text1) :
        ShannonInterface(text1, [](const trio &a, const trio &b) { return a.symbol < b.symbol; }) {

}



