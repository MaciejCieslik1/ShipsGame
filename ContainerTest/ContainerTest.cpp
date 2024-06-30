#include "CppUnitTest.h"
#include "TemplateClassForTesting.h"
#include "../Ships/InfoContainer.h"

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<>
    std::wstring ToString<TemplateClassForTesting>(const TemplateClassForTesting& obj) {
        return std::to_wstring(obj.getValue());
    }
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ContainerTest
{
	TEST_CLASS(ContainerTest)
	{
	public:
        TEST_METHOD(TestConstructor) {
            TemplateClassForTesting class1(4);
            TemplateClassForTesting class2(3);
            TemplateClassForTesting class3(2);
            TemplateClassForTesting class4(1);

            std::unique_ptr<TemplateClassForTesting> ptr1 = std::make_unique<TemplateClassForTesting>(class1);
            std::unique_ptr<TemplateClassForTesting> ptr2 = std::make_unique<TemplateClassForTesting>(class2);
            std::unique_ptr<TemplateClassForTesting> ptr3 = std::make_unique<TemplateClassForTesting>(class3);
            std::unique_ptr<TemplateClassForTesting> ptr4 = std::make_unique<TemplateClassForTesting>(class4);

            InfoContainer<TemplateClassForTesting> cont1;
            InfoContainer<TemplateClassForTesting> cont2;
            cont1.addObject(std::move(ptr1));
            cont1.addObject(std::move(ptr2));
            cont2.addObject(std::move(ptr3));
            cont2.addObject(std::move(ptr4));

            cont1 = cont2;

            Assert::AreEqual(cont1.size(), cont2.size());
            for (size_t i = 0; i < cont1.size(); ++i) {
                Assert::IsTrue(cont1.get(i) == cont2.get(i));
            }
        }

        TEST_METHOD(TestCopyConstructor) {
            TemplateClassForTesting class1(4);
            TemplateClassForTesting class2(3);
            TemplateClassForTesting class3(2);
            TemplateClassForTesting class4(1);

            std::unique_ptr<TemplateClassForTesting> ptr1 = std::make_unique<TemplateClassForTesting>(class1);
            std::unique_ptr<TemplateClassForTesting> ptr2 = std::make_unique<TemplateClassForTesting>(class2);
            std::unique_ptr<TemplateClassForTesting> ptr3 = std::make_unique<TemplateClassForTesting>(class3);
            std::unique_ptr<TemplateClassForTesting> ptr4 = std::make_unique<TemplateClassForTesting>(class4);

            InfoContainer<TemplateClassForTesting> originalContainer;
            originalContainer.addObject(std::move(ptr1));
            originalContainer.addObject(std::move(ptr2));
            originalContainer.addObject(std::move(ptr3));
            originalContainer.addObject(std::move(ptr4));

            InfoContainer<TemplateClassForTesting> copiedContainer(originalContainer);

            Assert::AreEqual(originalContainer.size(), copiedContainer.size());
            for (size_t i = 0; i < originalContainer.size(); ++i) {
                Assert::AreEqual(originalContainer.get(i), copiedContainer.get(i));
            }
        }

        TEST_METHOD(TestAddObject)
        {
            InfoContainer<TemplateClassForTesting> container;

            container.addObject(std::make_unique<TemplateClassForTesting>(5));
            container.addObject(std::make_unique<TemplateClassForTesting>(10));
            container.addObject(std::make_unique<TemplateClassForTesting>(15));

            Assert::AreEqual(static_cast<size_t>(3), container.size());
        }

        TEST_METHOD(TestAccessObject)
        {
            InfoContainer<TemplateClassForTesting> container;

            container.addObject(std::make_unique<TemplateClassForTesting>(5));

            auto accessedObject = container.accessObject(TemplateClassForTesting(5));

            Assert::AreEqual(5, accessedObject->getValue());
        }

        TEST_METHOD(TestRemoveObject)
        {
            InfoContainer<TemplateClassForTesting> container;

            container.addObject(std::make_unique<TemplateClassForTesting>(5));

            auto removedObject = container.removeObject(TemplateClassForTesting(5));

            Assert::AreEqual(5, removedObject->getValue());
            Assert::IsTrue(container.isEmpty());
        }

        TEST_METHOD(TestFindObject)
        {
            InfoContainer<TemplateClassForTesting> container;

            container.addObject(std::make_unique<TemplateClassForTesting>(5));

            Assert::IsTrue(container.findObject(TemplateClassForTesting(5)));
        }

        TEST_METHOD(TestIsEmpty)
        {
            InfoContainer<TemplateClassForTesting> container;

            Assert::IsTrue(container.isEmpty());

            container.addObject(std::make_unique<TemplateClassForTesting>(5));

            Assert::IsFalse(container.isEmpty());
        }

        TEST_METHOD(TestIndex)
        {
            InfoContainer<TemplateClassForTesting> container;

            container.addObject(std::make_unique<TemplateClassForTesting>(5));
            container.addObject(std::make_unique<TemplateClassForTesting>(10));
            container.addObject(std::make_unique<TemplateClassForTesting>(15));

            Assert::AreEqual(0, container.index(TemplateClassForTesting(5)));
            Assert::AreEqual(2, container.index(TemplateClassForTesting(15)));
        }

        TEST_METHOD(TestSize)
        {
            InfoContainer<TemplateClassForTesting> container;

            container.addObject(std::make_unique<TemplateClassForTesting>(5));
            container.addObject(std::make_unique<TemplateClassForTesting>(10));
            container.addObject(std::make_unique<TemplateClassForTesting>(15));

            Assert::AreEqual(static_cast<size_t>(3), container.size());
        }

        TEST_METHOD(TestGet)
        {
            InfoContainer<TemplateClassForTesting> container;

            container.addObject(std::make_unique<TemplateClassForTesting>(5));
            container.addObject(std::make_unique<TemplateClassForTesting>(10));
            container.addObject(std::make_unique<TemplateClassForTesting>(15));

            Assert::AreEqual(5, container.get(0).getValue());
            Assert::AreEqual(10, container.get(1).getValue());
            Assert::AreEqual(15, container.get(2).getValue());
        }

        TEST_METHOD(TestClear)
        {
            InfoContainer<TemplateClassForTesting> container;

            container.addObject(std::make_unique<TemplateClassForTesting>(5));
            container.addObject(std::make_unique<TemplateClassForTesting>(10));
            container.addObject(std::make_unique<TemplateClassForTesting>(15));

            container.clear();

            Assert::IsTrue(container.isEmpty());
        }

        TEST_METHOD(TestEqualOperator)
        {
            TemplateClassForTesting class1(4);
            TemplateClassForTesting class2(3);
            TemplateClassForTesting class3(2);
            TemplateClassForTesting class4(1);

            std::unique_ptr<TemplateClassForTesting> ptr1 = std::make_unique<TemplateClassForTesting>(class1);
            std::unique_ptr<TemplateClassForTesting> ptr2 = std::make_unique<TemplateClassForTesting>(class2);
            std::unique_ptr<TemplateClassForTesting> ptr3 = std::make_unique<TemplateClassForTesting>(class3);
            std::unique_ptr<TemplateClassForTesting> ptr4 = std::make_unique<TemplateClassForTesting>(class4);

            InfoContainer<TemplateClassForTesting> cont1;
            InfoContainer<TemplateClassForTesting> cont2;

            cont1.addObject(std::move(ptr1));
            cont2.addObject(std::move(ptr2));
            cont1.addObject(std::move(ptr3));
            cont2.addObject(std::move(ptr4));

            Assert::IsTrue(cont1 != cont2);
            Assert::IsFalse(cont1 == cont2);
        }

        TEST_METHOD(TestAssignmentOperator)
        {
            TemplateClassForTesting class1(4);
            TemplateClassForTesting class2(3);
            TemplateClassForTesting class3(2);
            TemplateClassForTesting class4(1);

            std::unique_ptr<TemplateClassForTesting> ptr1 = std::make_unique<TemplateClassForTesting>(class1);
            std::unique_ptr<TemplateClassForTesting> ptr2 = std::make_unique<TemplateClassForTesting>(class2);
            std::unique_ptr<TemplateClassForTesting> ptr3 = std::make_unique<TemplateClassForTesting>(class3);
            std::unique_ptr<TemplateClassForTesting> ptr4 = std::make_unique<TemplateClassForTesting>(class4);

            InfoContainer<TemplateClassForTesting> cont1;
            InfoContainer<TemplateClassForTesting> cont2;

            cont1.addObject(std::move(ptr1));
            cont2.addObject(std::move(ptr2));
            cont1.addObject(std::move(ptr3));
            cont2.addObject(std::move(ptr4));

            cont1 = cont2;

            Assert::AreEqual(static_cast<size_t>(3), cont1.size());
            Assert::IsTrue(cont1.findObject(class2));
            Assert::IsFalse(cont1.findObject(class1));

        }

        TEST_METHOD(TestIndexOperator)
        {
            TemplateClassForTesting class1(4);
            TemplateClassForTesting class2(3);
            TemplateClassForTesting class3(2);
            TemplateClassForTesting class4(1);

            std::unique_ptr<TemplateClassForTesting> ptr1 = std::make_unique<TemplateClassForTesting>(class1);
            std::unique_ptr<TemplateClassForTesting> ptr2 = std::make_unique<TemplateClassForTesting>(class2);
            std::unique_ptr<TemplateClassForTesting> ptr3 = std::make_unique<TemplateClassForTesting>(class3);
            std::unique_ptr<TemplateClassForTesting> ptr4 = std::make_unique<TemplateClassForTesting>(class4);

            InfoContainer<TemplateClassForTesting> container;

            container.addObject(std::move(ptr1));
            container.addObject(std::move(ptr2));
            container.addObject(std::move(ptr3));
            container.addObject(std::move(ptr4));

            Assert::AreEqual(container[0], class1);
            Assert::AreEqual(container[1], class2);
            Assert::AreEqual(container[2], class3);
            Assert::AreEqual(container[3], class4);
        }

        //TEST_METHOD(TestOutStreamOperator)
        //{
        //    TemplateClassForTesting class1(4);
        //    TemplateClassForTesting class2(3);
        //    TemplateClassForTesting class3(2);
        //    TemplateClassForTesting class4(1);

        //    std::unique_ptr<TemplateClassForTesting> ptr1 = std::make_unique<TemplateClassForTesting>(class1);
        //    std::unique_ptr<TemplateClassForTesting> ptr2 = std::make_unique<TemplateClassForTesting>(class2);
        //    std::unique_ptr<TemplateClassForTesting> ptr3 = std::make_unique<TemplateClassForTesting>(class3);
        //    std::unique_ptr<TemplateClassForTesting> ptr4 = std::make_unique<TemplateClassForTesting>(class4);

        //    InfoContainer<TemplateClassForTesting> container;

        //    container.addObject(std::move(ptr1));
        //    container.addObject(std::move(ptr2));
        //    container.addObject(std::move(ptr3));
        //    container.addObject(std::move(ptr4));

        //    std::ostringstream oss;
        //    oss << container;

        //    std::string expectedOutput = "4\n3\n2\n1\n";
        //    Assert::AreEqual(expectedOutput.c_str(), oss.str().c_str());
        //}
	};
}
