#include "TEST.h"

#include "Array.h"

template <typename T>
void TEST::assertEquals(const T& expected, const T& actual, size_t count) {
    if(expected == actual) {
        std::cout << "PASSED: " << m_testName;
        if(count == 0)
            std::cout << std::endl;
        else
            std::cout << " #" << count << std::endl;
    } 
    else {
        std::cout << "FAILED: " << m_testName;
        if(count == 0)
            std::cout << std::endl;
        else
            std::cout << " #" << count << std::endl;
        std::cout << "Expected: " << expected << ", Actual: " << actual << std::endl;
    }
}

template <typename T>
void TEST::assertTrue(const T& condition, size_t count) {
    if (condition) {
        std::cout << "PASSED: " << m_testName;
        if(count == 0)
            std::cout << std::endl;
        else    
            std::cout << " #" << count << std::endl;
    } else {
        std::cout << "FAILED: " << m_testName;
        if(count == 0)
            std::cout << std::endl;
        else
            std::cout << " #" << count << std::endl;
    }
}

namespace TestCases 
{
    void TestArray(bool experimental) {
        if(experimental) 
        {
            // Test Array_Ex::Element struct Rule of 5;
            {
                Array_Ex<int>::Element element1;

                TEST testElement1("Test Default Element Ctor");
                testElement1.assertTrue(sizeof(element1.m_data) == sizeof(int), 1);
                testElement1.assertTrue(element1.m_empty == true, 2);
            }

            {
                Array_Ex<int>::Element element(10);
                TEST testElement("Test Data Specific Element Ctor");
                testElement.assertEquals(element.m_data, 10, 1);
                testElement.assertTrue(element.m_empty == false, 2);
            }
        }

        else 
        {
            {
                // Test Set Element
                Array<int> array1(5,5);
                array1.SetElement(0, 0);
                array1.SetElement(1, 1);
                array1.SetElement(2, 2);
                array1.SetElement(3, 3);
                array1.SetElement(4, 4);

                TEST test1("Test Array::SetElement()");
                test1.assertEquals<int>(0,array1[0]);
                test1.assertEquals<int>(1,array1[1]);
                test1.assertEquals<int>(2,array1[2]);
                test1.assertEquals<int>(3,array1[3]);
                test1.assertEquals<int>(4,array1[4]);
            }

            {
                // Test GrowBy
                Array<float> array2(1,10);
                TEST test2("Test Array::Append()");
                TEST test3("Test Array::Size()");
                TEST test4("Test Array::GetMaxQuantity()");
    
                array2.SetElement(0, 1.0); 
                test2.assertEquals<float>(1.0, array2[0]);
                test3.assertEquals<size_t>(1, array2.GetCount());
                test4.assertEquals<size_t>(1, array2.Size());
    
                array2.Append(2.0); 
                test2.assertEquals<float>(2.0, array2[1]);
                test3.assertEquals<size_t>(2, array2.GetCount());
                test4.assertEquals<size_t>(11, array2.Size());
    
                array2.Append(3.0); 
                test2.assertEquals<float>(3.0, array2[2]);
                test3.assertEquals<size_t>(3, array2.GetCount());
                test4.assertEquals<size_t>(11, array2.Size());
    
                array2.Append(4.0); 
                test2.assertEquals<float>(4.0, array2[3]);
                test3.assertEquals<size_t>(4, array2.GetCount());
                test4.assertEquals<size_t>(11, array2.Size());
    
                array2.Append(5.0); 
                test2.assertEquals<float>(5.0, array2[4]);
                test3.assertEquals<size_t>(5, array2.GetCount());
                test4.assertEquals<size_t>(11, array2.Size());
    
                array2.Append(6.0);
                test2.assertEquals<float>(6.0, array2[5]);
                test3.assertEquals<size_t>(6, array2.GetCount());
                test4.assertEquals<size_t>(11, array2.Size());
            }
        }

    }
}