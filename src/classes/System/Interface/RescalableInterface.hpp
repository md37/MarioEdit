#pragma once

#include <memory>
#include "classes/System/Scale.hpp"

class Scale;

class RescalableInterface {

public:

    virtual void rescale(std::unique_ptr<Scale>& scale)=0;

};