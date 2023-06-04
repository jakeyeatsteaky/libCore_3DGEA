#include "TEST.h"

#include "Array.h"

template <typename T>
void TEST::assertEquals(const T& expected, const T& actual) {
    if(expected == actual) {
        std::cout << "PASSED: " << m_testName << std::endl;
    } 
    else {
        std::cout << "FAILED: " << m_testName << std::endl;
        std::cout << "Expected: " << expected << ", Actual: " << actual << std::endl;
    }
}

template <typename T>
void TEST::assertTrue(const T& condition) {
    if (condition) {
        std::cout << "PASSED: " << m_testName << std::endl;
    } else {
        std::cout << "FAILED: " << m_testName << std::endl;
    }
}

namespace TestCases 
{
    void TestArray() {
        Array<int> array1(5,5);
        array1.SetElement(0, 0);
        array1.SetElement(1, 1);
        array1.SetElement(2, 2);
        array1.SetElement(3, 3);
        array1.SetElement(4, 4);

        TEST test1("Test Array::SetElement()");
        test1.assertEquals(0,array1[0]);
        test1.assertEquals(1,array1[1]);
        test1.assertEquals(2,array1[2]);
        test1.assertEquals(3,array1[3]);
        test1.assertEquals(4,array1[4]);
    }
}