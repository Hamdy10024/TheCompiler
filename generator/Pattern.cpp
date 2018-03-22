#include "Pattern.h"

Pattern::Pattern(char value) {
    rangeBegin = value;
    rangeEnd = value;
}

Pattern::Pattern(char rangeBegin, char rangeEnd) {
    this->rangeBegin = rangeBegin;
    this->rangeEnd = rangeEnd;
}

Pattern::~Pattern() {}

bool Pattern::accept(char value) {
    return value >= rangeBegin && value <= rangeEnd;
}

char Pattern::get() {
    return rangeBegin;
}
