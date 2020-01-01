#pragma once

#include <bitset>
#include <stdint.h>

const size_t MAX_ENTITIES = 1000;
const size_t MAX_COMPONENTS = 1000;
using Entity = size_t;
using ComponentID = size_t;
using Signature = std::bitset<MAX_COMPONENTS>;