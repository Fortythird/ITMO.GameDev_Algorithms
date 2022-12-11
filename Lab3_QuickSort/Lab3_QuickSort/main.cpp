#include <iostream>
#include <windows.h>
#include "..\Lab3_QuickSort\Sort.h"

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

void main()
{

    std::string arr[10] = { "Here is 19 symbols!", "But here only 16", "12345678", "", "testtesttest", "12345678", "Yet another string",
                "And another one", "And another one", "Meh..." };
    quickSort(arr, arr + 9, [](std::string a, std::string b) { return a.size() < b.size(); });
    for (int i = 0; i < 10; i++) std::cout << arr[i] << std::endl;
    /*int array[100];
    int arrForIns[100];
    int copy[100];
    float counter;

    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 100; i++) array[i] = rand() % 100;

    for (int i = 0; i < 100; i++) arrForIns[i] = 100 - i;

    for (int i = 0; i < 100; i++)
    {
        counter = 0;
        for (int j = 0; j < 1000; j++)
        {
            for (int k = 0; k < 100; k++) copy[k] = array[k];
            StartCounter();
            quickSort(copy, copy + i, [](int a, int b) { return a < b; });
            counter += GetCounter();
        }
        std::cout << counter / 1000 << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0; i < 100; i++)
    {
        counter = 0;
        for (int j = 0; j < 1000; j++)
        {
            for (int k = 0; k < 100; k++) copy[k] = arrForIns[k];
            StartCounter();
            insertionSort(copy, copy + i, [](int a, int b) { return a < b; });
            counter += GetCounter();
        }
        std::cout << counter / 1000 << std::endl;
    }

    for (int i = 0; i < 100; i++)
    {
        counter = 0;
        for (int j = 0; j < 1000; j++)
        {
            for (int k = 0; k < 100; k++) copy[k] = array[k];
            StartCounter();
            sort(copy, copy + i, [](int a, int b) { return a < b; });
            counter += GetCounter();
        }
        std::cout << counter / 1000 << std::endl;
    }*/
}