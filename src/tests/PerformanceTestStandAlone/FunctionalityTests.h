#ifndef FUNCTIONALITYTESTS_H_
#define FUNCTIONALITYTESTS_H_

#include <string>

class FunctionalityTests
{
public:
    FunctionalityTests() {};
    bool executeAllTests() noexcept;
    bool defaultConstructorSelfTests() noexcept;
    bool defaultConstructorAddVector() noexcept;
    bool defaultConstructorAddArray() noexcept;
    bool defaultConstructorAddInitializerList() noexcept;
    bool limitsConstructorAddVector() noexcept;
    bool limitsConstructorAddArray() noexcept;
    bool limitsConstructorAddInitializerList() noexcept;

private:

};

#endif // FUNCTIONALITYTESTS_H_