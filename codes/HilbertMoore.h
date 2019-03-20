#ifndef UNTITLED2_HILBERTMOORE_H
#define UNTITLED2_HILBERTMOORE_H

#include "ShannonInterface.h"
#include <map>

class HilbertMoore : public ShannonInterface {
public:
    explicit HilbertMoore(const std::wstring &text1);

    ~HilbertMoore() override = default;
};


#endif //UNTITLED2_HILBERTMOORE_H
