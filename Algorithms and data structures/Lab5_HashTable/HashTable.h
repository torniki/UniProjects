#pragma once
#include "List.h"

namespace Mine
{
    class HashTable
    {
    public:
        HashTable();
        void push (int value);
        int itemSearch (int key) const;
        void delItem (int key);


        void print() const;

    private:
        int Hash(int value) const;
        static const int LENGHT = 10;
        List arr[LENGHT];
    };
}
