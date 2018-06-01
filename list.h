#ifndef RGZLANG_LIST_H
#define RGZLANG_LIST_H
#include <iostream>
#include "Matrix.h"

using namespace std;

// Линейный двунаправленный список со вставкой элементов в начало
template <class type> class list
{
public:
    list()
    {
        items = nullptr;
    }
private:
    struct element
    {
        type data;
        element* prev;
        element* next;
        ~element()
        {
            cout << "~element(): " << data << endl;
        }
    };
    // Указатель на начало списка
    element* items;
public:
    // Добавление нового элемента в начало списка
    void add(type data)
    {
        if(items == nullptr)
        {
            items = new element;
            items->prev = nullptr;
            items->next = nullptr;
            items->data = data;
        }
        else
        {
            element* e = new element;
            e->data = data;
            e->prev = nullptr;
            e->next = items;
            items->prev = e;
            items = e;
        }
    }

    // Вывод всех элементов списка на экран
    void print()
    {
        if(items != nullptr)
        {
            element* e = items;
            while(e)
            {
                cout << e->data << endl;
                e = e->next;
            }
        }
    }
    //Поиск элемента в списке

    // Удаление всех элементов из списка
    void remove_all()
    {
        while(items)
        {
            element* temp = items->next;
            delete items;
            items = temp;
        }
    }
    // Удаление элемента из списка
    bool remove_item(int index)
    {
        if(items != nullptr)
        {
            if(index <= get_amount()-1 && index >= 0)
            {
                auto e = find(index);
                if(e != nullptr)
                {
                    if(e->prev == nullptr) // Начало списка
                    {
                        items = items->next;
                        items->prev = nullptr;
                    }
                    else if(e->next == nullptr) // Конец списка
                    {
                        auto endlist = find(get_amount()-1);
                        endlist = endlist->prev;
                        endlist->next = nullptr;
                    }
                    else // Середина списка
                    {
                        e->prev->next = e->next;
                        e->next->prev = e->prev;
                    }
                    delete e;
                    return true;
                }
                else return false;
            }
            else return false;
        }
        else return false;
    }
private:
    // Поиск элемента по его индексу
    element* find(int index)
    {
        int amount = 0;
        element* e = items;
        while(e)
        {
            if(index == amount)
                return e;
            e = e->next;
            amount++;
        }
        return nullptr;
    }
public:
    // Общее количество элементов в списке
    int get_amount()
    {
        if(items != nullptr)
        {
            int amount = 0;
            element* e = items;
            while(e)
            {
                e = e->next;
                amount++;
            }
            return amount;
        }
        else
        {
            return -1;
        }
    }
    // Перегрузка оператора []
    type& operator [] (const int& index)
    {
        auto e = find(index);
        return e->data;
    }
    // Деструктор
    ~list()
    {
        remove_all();
    }
};
// Тестирование функций добавления и вставки элемента
//    list<Matrix> q;
//    Matrix A;
//    q.add(A);
// Вывод на экран всего списка
//    q.print();
// Удаление последнего элемента списка
//    q.remove_item(5);
// Вывод на экран текущего количества элементов
//    auto amount = q.get_amount();
//    cout << "amount: " << amount << endl;
//Тестирование перегрузки оператора []
//    for(int i = 0; i < amount; i++)
//        cout<<q[i];
//
//Удаление всех элементов списка
//    q.remove_all();

#endif //RGZLANG_LIST_H
