#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab3_QuickSort\Sort.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortTest
{
	TEST_CLASS(SortTest)
	{
	public:
		
		TEST_METHOD(IntQuickSort)
		{
			int arr[10] = {10, 5, 9, 6, 3, 4, 1, 8, 2, 7};
			quickSort(arr, arr + 9, [](int a, int b) { return a < b; });
			for (int i = 0; i < 9; i++) Assert::IsTrue(arr[i] < arr[i + 1]);
		}

		TEST_METHOD(IntInsSort)
		{
			int arr[10] = { 10, 5, 9, 6, 3, 4, 1, 8, 2, 7 };
			insertionSort(arr, arr + 9, [](int a, int b) { return a < b; });
			for (int i = 0; i < 9; i++) Assert::IsTrue(arr[i] < arr[i + 1]);
		}

		TEST_METHOD(IntQuickSortSingle)
		{
			int arr[1] = { 10 };
			quickSort(arr, arr, [](int a, int b) { return a < b; });
			Assert::IsTrue(*arr == 10);
		}

		TEST_METHOD(IntInsSortSingle)
		{
			int arr[1] = { 10 };
			insertionSort(arr, arr, [](int a, int b) { return a < b; });
			Assert::IsTrue(*arr == 10);
		}

		TEST_METHOD(IntQuickSortEqual)
		{
			int arr[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			quickSort(arr, arr, [](int a, int b) { return a < b; });
			for (int i = 0; i < 9; i++) Assert::IsTrue(arr[i] <= arr[i + 1]);
		}

		TEST_METHOD(IntInsSortEqual)
		{
			int arr[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			insertionSort(arr, arr, [](int a, int b) { return a < b; });
			for (int i = 0; i < 9; i++) Assert::IsTrue(arr[i] <= arr[i + 1]);
		}

		TEST_METHOD(StrQuickSort)
		{
			std::string arr[10] = { "Here is 19 symbols!", "But here only 16", "12345678", "", "testtesttest", "12345678", "Yet another string",
				"And another one", "And another one", "Meh..."};
			quickSort(arr, arr + 9, [](std::string a, std::string b) { return a.size() < b.size(); });
			for (int i = 0; i < 9; i++) Assert::IsTrue(arr[i].size() <= arr[i + 1].size());
			Assert::IsTrue(arr[9] == "Here is 19 symbols!");
			Assert::IsTrue(arr[0] == "");
		}

		TEST_METHOD(StrInsSort)
		{
			std::string arr[10] = { "Here is 19 symbols!", "But here only 16", "12345678", "", "testtesttest", "12345678", "Yet another string",
				"And another one", "And another one", "Meh..." };
			insertionSort(arr, arr + 9, [](std::string a, std::string b) { return a.size() < b.size(); });
			for (int i = 0; i < 9; i++) Assert::IsTrue(arr[i].size() <= arr[i + 1].size());
			Assert::IsTrue(arr[9] == "Here is 19 symbols!");
			Assert::IsTrue(arr[0] == "");
		}
	};
}
