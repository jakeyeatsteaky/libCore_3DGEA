#ifndef TEST_H
#define TEST_H

#include "Array.h"

class TEST {
public:
    TEST(const std::string& name): m_testName(name) {};
    ~TEST() = default;

    template <typename T>
    void assertEquals(const T& expected, const T& actual);

    template <typename T>
    void assertTrue(const T& condition);

private:
    std::string m_testName;
};

namespace TestCases 
{
    void TestArray();
}


#endif