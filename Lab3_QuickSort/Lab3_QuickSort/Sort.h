#pragma once

#ifndef SORT_H
#define SORT_H 1

#define SHIFT_BORDER 25


template<typename T>
bool comp(const T& a, const T& b)
{
    return a < b;
}

template<typename T, typename Compare>
T* partitionHoare(T* low, T* high, Compare comp)
{
    T pivot = pivotSelection(low, (low + (high - low) / 2), high, comp);
    T* i = low;
    T* j = high;
    while (true)
    {
        while (comp(*i, pivot)) i += 1;
        while (comp(pivot, *j)) j -= 1;
        if (i >= j)
        {
            return j;
            break;
        }
        std::swap(*i, *j);
        i += 1;
        j -= 1;
    }
}

template<typename T, typename Compare>
T pivotSelection(T* low, T* middle, T* high, Compare comp)
{
    if (comp(*middle, *low)) std::swap(*low, *middle);
    if (comp(*high, *low)) std::swap(*low, *high);
    if (comp(*high, *middle)) std::swap(*high, *middle);
    return *middle;
}

template<typename T, typename Compare>
void quickSort(T* low, T* high, Compare comp)
{
    while (high > low)
    {
        T* pivot = partitionHoare(low, high, comp);
        if (pivot - low < high - (pivot + 1))
        {
            quickSort(low, pivot, comp);
            low = pivot + 1;
        }
        else
        {
            quickSort(pivot + 1, high, comp);
            high = pivot;
        }
    }
}

template<typename T, typename Compare>
void insertionSort(T* low, T* high, Compare comp)
{
    T key;
    int i, j;
    for (i = 1; i < high - low + 1; i++)
    {
        key = std::move(*(low + i));
        j = i - 1;

        while (j >= 0 && comp(key, *(low + j)))
        {
            *(low + j + 1) = std::move(*(low + j));
            j -= 1;
        }
        *(low + j + 1) = std::move(key);
    }
}

template<typename T, typename Compare>
void sort(T* low, T* high, Compare comp)
{
    if (high - low + 1 < SHIFT_BORDER) insertionSort(low, high, comp);
    else quickSort(low, high, comp);
}

#endif