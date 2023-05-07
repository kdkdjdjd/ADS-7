// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 public:
    TPQueue() : head(nullptr), tail(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;

 private:
    struct Item {
        T value;
        Item* next;
        Item* prev;
    };
    Item* head;
    Item* tail;
    TPQueue::Item* create(const T&);
};
template <typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& value) {
    Item* temp = new Item;
    temp->value = value;
    temp->next = nullptr;
    temp->prev = nullptr;
    return temp;
}

template <typename T>
void TPQueue<T>::push(const T& item) {
    if (head == nullptr) {
       head = create(item);
       tail = head;
    } else if (tail->value.prior >= item.prior) {
        if (tail->value.ch == item.ch) {
            tail->value = item;
        } else {
            tail->next = create(item);
            tail->next->prev = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->prev = create(item);
        head = tail->prev;
        head->next = tail;
    } else {
        Item* temp = tail;
        while (temp != head && temp->value.prior < item.prior) {
        temp = temp->prev;
        }
        if (temp->value.prior > item.prior) {
            Item* a = new Item;
            a->next = temp->next;
            a->prev = temp;
            a->value = item;
            temp->next->prev = a;
            temp->next = a;
        }
        if (temp == head && temp->value.prior < item.prior) {
            head->prev = create(item);
            head = head->prev;
            head->next = temp;
        }
    }
}

template <typename T>
T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("Empty");
    } else {
        Item* temp = head->next;
        T value = head->value;
        delete head;
        head = temp;
        return value;
    }
}

template <typename T>
void TPQueue<T>::print() const {
    Item* temp = head;
    while (temp) {
        std::cout << temp->value << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
