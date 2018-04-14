#include "Pattern.h"

Pattern::Pattern(char value) {
    rangeBegin = value;
    rangeEnd = value;
}

Pattern::Pattern(char rangeBegin, char rangeEnd) {
    this->rangeBegin = rangeBegin;
    this->rangeEnd = rangeEnd;
}

bool Pattern::accept(char value) {
    return value >= rangeBegin && value <= rangeEnd;
}

char Pattern::get() {
    return rangeBegin;
}

bool Pattern::operator ==(const Pattern &c) {
    return this->rangeBegin == c.rangeBegin && this->rangeEnd == c.rangeEnd;
}

bool Pattern::operator <(const Pattern &c) {
    return this->rangeBegin < c.rangeBegin || this->rangeBegin == c.rangeBegin && this->rangeEnd < c.rangeEnd;

}

bool Pattern::operator >(const Pattern &c) {

    return this->rangeEnd > c.rangeEnd || this->rangeBegin > c.rangeBegin && this->rangeEnd == c.rangeEnd;
}
