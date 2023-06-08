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
                Array_Ex<int>::Element copyElement(element);
                Array_Ex<int>::Element assignCopyElement = copyElement;

                TEST testElement("Test Data Specific Element Ctor");
                testElement.assertEquals(element.m_data, 10, 1);
                testElement.assertTrue(element.m_empty == false, 2);

                TEST testElement2("Test Copy CTor");
                testElement2.assertEquals(element.m_data, copyElement.m_data, 1);
                testElement2.assertTrue(copyElement.m_empty == false, 2);

                TEST testElement3("Test Copy Assignment Operator");
                testElement3.assertEquals(assignCopyElement.m_data, copyElement.m_data, 1);
                testElement3.assertTrue(assignCopyElement.m_empty == false, 2);
            }

            {
                Array_Ex<double>::Element element(5.5);
                Array_Ex<double>::Element moveElement(std::move(element));

                TEST test1("Test Move CTor/AssignOp");
                test1.assertEquals(moveElement.m_data, element.m_data, 1);

                Array_Ex<double>::Element moveAssign = std::move(moveElement);
                test1.assertEquals(moveAssign.m_data, moveElement.m_data, 2);
            }

            #if 0
                Array_Ex Testing:
                [x] Default constructor
                [x] Specified constructor
                [ ] Constructor with initialization list
                    [ ] std::initliazer list
                    [x] take an array as arrguemnt
                    [ ] Variadic arg -- parameterpack
                [ ] Copy Constructors
                [ ] Move Constructor
                [ ] Copy Assignment Operator
                [ ] Move Assignment Operator
                [ ] Destructor
                [x] Size method
                [ ] Data methods
                [ ] operator [] methods
                [ ] At method
                [ ] Append
                [ ] SetElement
            #endif

            // Test Array_Ex Rule of 5
            {
                Array_Ex<int> array1;
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
            }

            {
                Array_Ex<int> array1(10,5);
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
                
            }

            {
                TEST test1("Test Constructor with Initialization list (T[] argument)");
                int someData[] = {1, 2, 3, 4, 5, 6, 7};

                Array_Ex<int> array1(someData, 7);
                for(size_t i = 0; i < array1.Size(); ++i) {
                    test1.assertEquals(array1.At(i), someData[i], i+1);
                }
                test1.assertTrue(array1.GetCount() == 7,8);

                TEST test2("Test Constructor with Initliazatiion List (Parameter Pack)");



                TEST test2("Test Constructor with Initliazatiion List (std::initializerlist)");
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