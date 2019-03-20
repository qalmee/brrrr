#ifndef UNTITLED2_SHANNONIMPL_H
#define UNTITLED2_SHANNONIMPL_H

#include "ShannonInterface.h"

class ShannonImpl : public ShannonInterface {

public:

    explicit ShannonImpl(const std::wstring &text1);

    ~ShannonImpl() override = default;
};


#endif //UNTITLED2_SHANNONIMPL_H
