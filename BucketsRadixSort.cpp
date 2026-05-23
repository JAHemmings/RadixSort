#include <iostream>
#include <cstdlib>
#include <ctime>

#include "DLinkedList.h"
#include "RadixSort.h"

using namespace std;

int main() {
    srand(time(nullptr));
    DLinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.append(rand() % 1000);
    }
    cout << "Lista original:" << endl;
    list.print();
    RadixSort::sort(list, 10);
    cout << "\nLista ordenada:" << endl;
    list.print();
    return 0;
}