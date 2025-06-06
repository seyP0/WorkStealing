#include "Deque.hpp"
#include <iostream>

Deque::Deque() : capacity(4), size(0), front(0), back(0) {
    tasks = new int[capacity];
}

Deque::~Deque() {
    delete[] tasks;
}

void Deque::resize(int new_capacity) {
    int *new_tasks = new int[new_capacity];
    for (int i = 0; i < size; i++) {
        new_tasks[i] = tasks[(front + i) % capacity];
    }
    delete[] tasks;
    tasks = new_tasks;
    capacity = new_capacity;
    front = 0;
    back = size;
}

void Deque::push_back(int task_id) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    tasks[back] = task_id;
    back = (back + 1) % capacity;
    size++;
}

int Deque::pop_front() {
    if (size == 0) {
        return -1; // No task to run
    }
    int task_id = tasks[front];
    front = (front + 1) % capacity;
    size--;
    if (size > 0 && size == capacity / 4 && capacity > 4) {
        resize(capacity / 2);
    }
    return task_id;
}

int Deque::pop_back() {
    if (size == 0) {
        return -1;
    }
    back = (back - 1 + capacity) % capacity;
    int task_id = tasks[back];
    size--;
    if (size > 0 && size == capacity / 4 && capacity > 4) {
        resize(capacity / 2);
    }
    return task_id;
}

int Deque::get_size() const {
    return size;
}

int Deque::get_capacity() const {
    return capacity;
}
