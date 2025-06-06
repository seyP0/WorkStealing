#ifndef CORE_HPP
#define CORE_HPP

#include "Deque.hpp"

class Core {
private:
    Deque task_queue;

public:
    Core();
    bool has_tasks() const;
    void add_task(int task_id);
    int run_task();
    int steal_task();
    int get_task_count() const;
    int get_task_capacity() const;
};

#endif
