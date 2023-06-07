#ifndef TEST_H
#define TEST_H

#include "Array.h"
#include "ArrayExperiment.h"

class TEST {
public:
    TEST(const std::string& name): m_testName(name) {};
    ~TEST() = default;

    template <typename T>
    void assertEquals(const T& expected, const T& actual, size_t count = 0);

    template <typename T>
    void assertTrue(const T& condition, size_t count = 0);

private:
    std::string m_testName;
};

namespace TestCases 
{
    void TestArray(bool experimental);
}


#endif