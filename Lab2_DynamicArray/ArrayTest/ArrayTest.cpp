#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab2_DynamicArray\MyArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ArrayTest
{
	TEST_CLASS(ArrayTest)
	{
	public:
		
		TEST_METHOD(InitInt)
		{
			MyArray<int> arr;
			Assert::IsTrue(arr.size() == 0);
			Assert::IsTrue(arr.getCapacity() == 8);
		}

		TEST_METHOD(ExpandInt)
		{
			MyArray<int> arr(2);
			int* firstPtr = arr.getPointer();
			int firstCap = arr.getCapacity();
			arr.insert(1);
			arr.insert(2); // массив заполнен
			arr.insert(3);
			int* secPtr = arr.getPointer();
			int secCap = arr.getCapacity();
			Assert::IsTrue(firstCap != secCap);
			Assert::IsTrue(firstPtr != secPtr);
		}

		TEST_METHOD(ContentInt)
		{
			MyArray<int> arr(7);
			arr.insert(1);
			arr.insert(2);
			arr.insert(3);
			arr.insert(4);
			arr.insert(5);
			arr.insert(6);
			arr.insert(7);
			Assert::IsTrue(arr[0] == 1);
			Assert::IsTrue(arr[1] == 2);
			Assert::IsTrue(arr[2] == 3);
			Assert::IsTrue(arr[3] == 4);
			Assert::IsTrue(arr[4] == 5);
			Assert::IsTrue(arr[5] == 6);
			Assert::IsTrue(arr[6] == 7);
		}

		TEST_METHOD(ContentString)
		{
			MyArray<std::string> arr(7);
			arr.insert("One");
			arr.insert("Two");
			arr.insert("Three");
			arr.insert("Four");
			arr.insert("Five");
			arr.insert("Six");
			arr.insert("Seven");
			Assert::IsTrue(arr[0] == "One");
			Assert::IsTrue(arr[1] == "Two");
			Assert::IsTrue(arr[2] == "Three");
			Assert::IsTrue(arr[3] == "Four");
			Assert::IsTrue(arr[4] == "Five");
			Assert::IsTrue(arr[5] == "Six");
			Assert::IsTrue(arr[6] == "Seven");
		}

		TEST_METHOD(InsertAndRemoveString)
		{
			MyArray<std::string> arr(4);
			arr.insert("One");
			arr.insert("Two");
			arr.insert("Three");
			arr.insert(2, "Four"); // массив заполнен
			Assert::IsTrue(arr[2] == "Four");
			arr.insert(0, "Five");
			Assert::IsTrue(arr[0] == "Five");
			Assert::IsTrue(arr[3] == "Four");
			arr.remove(3);
			arr.remove(2);
			Assert::IsTrue(arr[0] == "Five");
			Assert::IsTrue(arr[1] == "One");
			Assert::IsTrue(arr[2] == "Three");
		}

		TEST_METHOD(IterSet)
		{
			MyArray<int> arr(4);
			arr.insert(1);
			arr.insert(2);
			arr.insert(3);
			arr.insert(4);

			auto iter = arr.iterator();
			for (auto iter = arr.iterator(); iter.hasNext(); iter.next()) iter.set(iter.get() + 1);

			Assert::IsTrue(arr[0] == 2);
			Assert::IsTrue(arr[1] == 3);
			Assert::IsTrue(arr[2] == 4);
			Assert::IsTrue(arr[3] == 5);
		}

		TEST_METHOD(IterBorders)
		{
			MyArray<int> arr(8);
			arr.insert(1);
			arr.insert(2);
			arr.insert(3);
			arr.insert(4);
			arr.insert(5);
			arr.insert(6);
			arr.insert(7);
			arr.insert(8);

			auto iter = arr.iterator();
			Assert::IsTrue(iter.get() == arr[0]);
			for (int i = 0; i < arr.size() - 1; i++) iter.next();
			auto rIter = arr.reverseIterator();
			Assert::IsTrue(iter.get() == rIter.get());

			iter = arr.reverseIterator();
			Assert::IsTrue(iter.get() == arr[arr.size() - 1]);
			for (int i = 0; i < arr.size() - 1; i++) iter.next();
			rIter = arr.iterator();
			Assert::IsTrue(iter.get() == rIter.get());
		}

		TEST_METHOD(IterLoop)
		{
			MyArray<int> arr(8);
			arr.insert(1);
			arr.insert(2);
			arr.insert(3);
			arr.insert(4);
			arr.insert(5);
			arr.insert(6);
			arr.insert(7);
			arr.insert(8);

			int i = 0;
			for (auto iter = arr.iterator(); iter.hasNext(); iter.next())
			{
				Assert::IsTrue(arr[i] == iter.get());
				i++;
			}

			i = arr.size() - 1;
			for (auto iter = arr.reverseIterator(); iter.hasNext(); iter.next())
			{
				Assert::IsTrue(arr[i] == iter.get());
				i--;
			}
		}

		TEST_METHOD(InsertWrongIndex)
		{
			MyArray<int> arr(4);
			arr.insert(1);
			arr.insert(2);
			arr.insert(3);
			arr.insert(4);
			arr.insert(10,5);
			Assert::IsTrue(arr.size() == 4);
			Assert::IsTrue(arr.getCapacity() == 4);
		}

		TEST_METHOD(ConstIterLoop)
		{
			MyArray<int> arr(8);
			arr.insert(1);
			arr.insert(2);
			arr.insert(3);
			arr.insert(4);
			arr.insert(5);
			arr.insert(6);
			arr.insert(7);
			arr.insert(8);

			int i = 0;
			for (auto iter = arr.cIterator(); iter.hasNext(); iter.next())
			{
				Assert::IsTrue(arr[i] == iter.get());
				i++;
			}

			i = arr.size() - 1;
			for (auto iter = arr.cReverseIterator(); iter.hasNext(); iter.next())
			{
				Assert::IsTrue(arr[i] == iter.get());
				i--;
			}
		}
	};
}
