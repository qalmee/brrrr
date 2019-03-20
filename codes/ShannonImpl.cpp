#include "ShannonImpl.h"

ShannonImpl::ShannonImpl(const std::wstring &text1) :
        ShannonInterface(text1, [](const trio &a, const trio &b) { return a.p > b.p; }) {

}
