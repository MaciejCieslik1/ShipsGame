#pragma once
#include <string>
#include <iostream>

class TemplateClassForTesting {
public:
    TemplateClassForTesting(int value);
    int getValue() const;

    bool operator==(const TemplateClassForTesting& other) const;
private:
    int value;
    friend std::ostream& operator<<(std::ostream& os, const TemplateClassForTesting& x);
};


