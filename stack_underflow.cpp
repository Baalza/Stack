#include "stack_underflow.h"

stack_underflow::stack_underflow(const std::string &message) 
    : std::runtime_error(message) {}




