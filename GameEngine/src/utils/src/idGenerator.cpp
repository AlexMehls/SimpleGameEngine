#include "idGenerator.hpp"

namespace IdGenerator
{
    uint64_t getObjectId()
    {
        static uint64_t nextId = 0;
        return nextId++;
    }
} // namespace IdGenerator
