#include "Core.hpp"

Core::Core() {}

bool Core::has_tasks() const {
    return task_queue.get_size() > 0;
}

void Core::add_task(int task_id) {
    task_queue.push_back(task_id);
}

int Core::run_task() {
    return task_queue.pop_front();
}

int Core::steal_task() {
    return task_queue.pop_back();
}

int Core::get_task_count() const {
    return task_queue.get_size();
}

int Core::get_task_capacity() const {
    return task_queue.get_capacity();
}
