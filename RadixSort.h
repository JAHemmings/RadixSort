#pragma once
#include <iostream>
#include <cmath>
#include "DLinkedList.h"

using std::cout;
using std::endl;

class RadixSort {
private:
    static int getMax(DLinkedList<int>& list) {
        list.goToStart();
        int max = list.getElement();
        for (int i = 0; i < list.getSize(); i++) {
            int value = list.getElement();
            if (value > max)
                max = value;
            list.next();
        }
        return max;
    }

public:
    static void sort(DLinkedList<int>& list, int base) {
        if (list.getSize() == 0)
            return;
        DLinkedList<int>* buckets = new DLinkedList<int>[base];
        int max = getMax(list);
        for (int exp = 1; max / exp > 0; exp *= base) {
            int originalSize = list.getSize();
            list.goToStart();
            for (int i = 0; i < originalSize; i++) {
                int num = list.remove();
                int digit = (num / exp) % base;
                buckets[digit].append(num);
            }
            for (int i = 0; i < base; i++) {
                buckets[i].goToStart();
                while (buckets[i].getSize() > 0) {
                    int value = buckets[i].remove();
                    list.append(value);
                }
            }
        }
        delete[] buckets;
    }
};