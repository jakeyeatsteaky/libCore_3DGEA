#ifndef TEST_H
#define TEST_H

#include "Array.h"
#include "ArrayDeprecated.h"

class TEST {
public:
    TEST(const std::string& name): m_testName(name) {};
    ~TEST() = default;

    template <typename T>
    void assertEquals(const T& expected, const T& actual, size_t count = 0);

    template <typename T>
    void assertTrue(const T& condition, size_t count = 0);

    bool getEndCheck() { return m_endCheck; }

private:
    std::string m_testName;
    bool m_endCheck;
};

namespace TestCases 
{
    void TestArray(bool experimental);
    void RunTestSuite();
}


#endif