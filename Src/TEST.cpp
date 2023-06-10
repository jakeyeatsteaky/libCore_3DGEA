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
        m_endCheck = true; 
    } 
    else {
        std::cout << "FAILED: " << m_testName;
        if(count == 0)
            std::cout << std::endl;
        else
            std::cout << " #" << count << std::endl;
        std::cout << "Expected: " << expected << ", Actual: " << actual << std::endl;
        m_endCheck = false;
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
        m_endCheck = true;
    } else {
        std::cout << "FAILED: " << m_testName;
        if(count == 0)
            std::cout << std::endl;
        else
            std::cout << " #" << count << std::endl;
        m_endCheck = false;
    }
}

namespace TestCases 
{
    void TestArray(bool testDeprecated) {
        bool endCheck = true;
        
        if(testDeprecated) 
        {
            // Test Array::Element struct Rule of 5;
            {
                Array<int>::Element element1;

                TEST testElement1("Test Default Element Ctor");
                testElement1.assertTrue(sizeof(element1.m_data) == sizeof(int), 1);
                testElement1.assertTrue(element1.m_empty == true, 2);
                
                endCheck = testElement1.getEndCheck();
            }

            {
                Array<int>::Element element(10);
                Array<int>::Element copyElement(element);
                Array<int>::Element assignCopyElement = copyElement;

                TEST testElement("Test Data Specific Element Ctor");
                testElement.assertEquals(element.m_data, 10, 1);
                testElement.assertTrue(element.m_empty == false, 2);

                TEST testElement2("Test Copy CTor");
                testElement2.assertEquals(element.m_data, copyElement.m_data, 1);
                testElement2.assertTrue(copyElement.m_empty == false, 2);

                TEST testElement3("Test Copy Assignment Operator");
                testElement3.assertEquals(assignCopyElement.m_data, copyElement.m_data, 1);
                testElement3.assertTrue(assignCopyElement.m_empty == false, 2);

                endCheck = testElement.getEndCheck();
                endCheck = testElement2.getEndCheck();
                endCheck = testElement3.getEndCheck();
            }

            {
                Array<double>::Element element(5.5);
                Array<double>::Element moveElement(std::move(element));

                TEST test1("Test Move CTor/AssignOp");
                test1.assertEquals(moveElement.m_data, element.m_data, 1);

                Array<double>::Element moveAssign = std::move(moveElement);
                test1.assertEquals(moveAssign.m_data, moveElement.m_data, 2);

                endCheck = test1.getEndCheck();
            }

            // Test Array Rule of 5
            {
                Array<int> array1;
                TEST test1("Test Default Ctor Array");
                test1.assertEquals(array1.Size(), static_cast<size_t>(5), 1);
                test1.assertEquals(array1.GetGrowBy(), static_cast<size_t>(5), 2);
                bool isEmpty;
                for(size_t i = 0; i < array1.Size(); ++i) {
                    if(!array1[i].m_empty) {
                        isEmpty = false;
                        break;
                    }
                    isEmpty = true;
                }
                test1.assertTrue(isEmpty == true, 3);

                endCheck = test1.getEndCheck();
            }

            {
                Array<int> array1(10,5);
                TEST test1("Test Specified Ctor Array");
                test1.assertEquals(array1.Size(), static_cast<size_t>(10), 1);
                test1.assertEquals(array1.GetGrowBy(), static_cast<size_t>(5), 2);
                bool isEmpty;
                for(size_t i = 0; i < array1.Size(); ++i) {
                    if(!array1[i].m_empty) {
                        isEmpty = false;
                        break;
                    }
                    isEmpty = true;
                }
                test1.assertTrue(isEmpty == true, 3);
                
                endCheck = test1.getEndCheck();
            }

            {
                TEST test1("Test Constructor with data array");
                int someData[] = {1, 2, 3, 4, 5, 6, 7};
                int* badData = nullptr;
                size_t testCount = 1;
                Array<int> array1(someData, 7);
                Array<int> array2(badData, 1);
                Array<int> array3(someData, 0);

                for(size_t i = 0; i < array1.Size(); ++i) {

                    test1.assertEquals(array1.At(i), someData[i], testCount);
                    testCount++;
                }
                test1.assertTrue(array1.GetCount() == 7,testCount);
                test1.assertTrue(array2.Size() == 1, testCount+1);
                test1.assertTrue(array2.At(0) == 0xDEADBEEF, testCount+2);
                test1.assertTrue(array3.At(0) == 0xDEADBEEF, testCount+3);
                test1.assertTrue(array3.Size() == 1, testCount+4);

                endCheck = test1.getEndCheck();
            }

            {
                TEST test("Test Constructor with Initliazatiion List (std::initializerlist)");
                size_t testCount = 1;
                Array<int> array({1,2,3,4,5,6,7});

                test.assertEquals(array.Size(), static_cast<size_t>(7), testCount++);
                test.assertEquals(array.GetCount(), static_cast<size_t>(7), testCount++);
                for(size_t i = 0; i < 7; ++i) {
                    test.assertTrue(array[i].m_empty == false, testCount + i + 1);
                    test.assertEquals(array.At(i), static_cast<int>(i+1), testCount + i + 2);
                }

                endCheck = test.getEndCheck();
            }

            {
                TEST test("Test Append Method");
                Array<int> array({1,2,3});
                uint8_t testCount = 1;

                test.assertEquals(array.Size(), static_cast<size_t>(3), testCount++);
                test.assertEquals(array[3].m_data, array[0].m_data, testCount++);
                array.Append(10);
                test.assertEquals(array[3].m_data, 10, testCount++);
                array.Append(33);
                test.assertEquals(array[4].m_data, 33, testCount++);
                array.Append(256);
                test.assertEquals(array[5].m_data, 256, testCount++);

                endCheck = test.getEndCheck();
            }

            {
                TEST test("Test Set Element Method");
                uint8_t testCount = 1;
                Array<int> array(5, 5);

                test.assertTrue(array[0].m_empty == true, testCount++);
                test.assertTrue(array.Size() == 5, testCount++);
                test.assertTrue(array.GetGrowBy() == 5, testCount++);

                array.SetElement(0, 10);
                test.assertTrue(array[0].m_empty == false, testCount++);
                test.assertTrue(array[0].m_data == 10, testCount++);

                array.SetElement(5, 100);
                test.assertTrue(array[5].m_empty == false, testCount++);
                test.assertTrue(array[5].m_data == 100, testCount++);
                test.assertTrue(array.Size() == 6, testCount++);
                
                endCheck = test.getEndCheck();
            }
        }

        else 
        {
            {
                // Test Set Element
                Array_Deprecated<int> array1(5,5);
                array1.SetElement(0, 0);
                array1.SetElement(1, 1);
                array1.SetElement(2, 2);
                array1.SetElement(3, 3);
                array1.SetElement(4, 4);

                TEST test1("Test Array_Deprecated::SetElement()");
                test1.assertEquals<int>(0,array1[0]);
                test1.assertEquals<int>(1,array1[1]);
                test1.assertEquals<int>(2,array1[2]);
                test1.assertEquals<int>(3,array1[3]);
                test1.assertEquals<int>(4,array1[4]);
            }

            {
                // Test GrowBy
                Array_Deprecated<float> array2(1,10);
                TEST test2("Test Array_Deprecated::Append()");
                TEST test3("Test Array_Deprecated::Size()");
                TEST test4("Test Array_Deprecated::GetMaxQuantity()");
    
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

        endCheck ? std::cout << "ALL TEST CASES PASSED\n" : std::cout << "SOME TEST CASE FAILURES\n";
    }
}