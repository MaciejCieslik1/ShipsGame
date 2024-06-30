#include "TemplateClassForTesting.h"

TemplateClassForTesting::TemplateClassForTesting(int value) : value(value) { }

int TemplateClassForTesting::getValue() const { return value; }

bool TemplateClassForTesting::operator==(const TemplateClassForTesting& other) const {
    return this->value == other.value;
}

std::ostream& operator<<(std::ostream& os, const TemplateClassForTesting& x) {
    os << x.value;
    return os;
}