#include "stack_overflow.h"

stack_overflow::stack_overflow(const std::string &message) 
    : std::runtime_error(message) {}




