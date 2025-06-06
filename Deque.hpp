#ifndef DEQUE_HPP
#define DEQUE_HPP

class Deque {
private:
    int *tasks;
    int capacity;
    int size;
    int front;
    int back;

    void resize(int new_capacity);

public:
    Deque();
    ~Deque();
    void push_back(int task_id);
    int pop_front();
    int pop_back();
    int get_size() const;
    int get_capacity() const;
};

#endif
