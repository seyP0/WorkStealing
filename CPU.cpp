// CPU.cpp
#include "CPU.hpp"
#include <iostream>

CPU::CPU() : cores(nullptr), num_cores(0), is_initialized(false) {}

CPU::~CPU() {
    delete[] cores;
}

Core& CPU::get_least_loaded_core() {
    int min_tasks = cores[0].get_task_count();
    int core_index = 0;

    for (int i = 1; i < num_cores; ++i) {
        if (cores[i].get_task_count() < min_tasks) {
            min_tasks = cores[i].get_task_count();
            core_index = i;
        }
    }
    return cores[core_index];
}

Core& CPU::get_most_loaded_core() {
    int max_tasks = cores[0].get_task_count();
    int core_index = 0;

    for (int i = 1; i < num_cores; ++i) {
        if (cores[i].get_task_count() > max_tasks) {
            max_tasks = cores[i].get_task_count();
            core_index = i;
        }
    }
    return cores[core_index];
}

std::string CPU::on(int core_count) {
    if (is_initialized) {
        return "failure\n";
    }
    num_cores = core_count;
    cores = new Core[num_cores];
    is_initialized = true;
    return "success\n";
}

std::string CPU::spawn(int task_id) {
    if (task_id <= 0) {
        return "failure\n";
    }
    Core& core = get_least_loaded_core();
    core.add_task(task_id);
    return "core " + std::to_string(&core - cores) + " assigned task " + std::to_string(task_id) + "\n";
}

std::string CPU::run(int core_id) {
    // Check if the core ID is valid
    if (core_id < 0 || core_id >= num_cores) {
        return "failure\n";
    }

    // Check if the core has tasks to run
    if (!cores[core_id].has_tasks()) {
        // Output that the core has no tasks to run
        std::string output = "core " + std::to_string(core_id) + " has no tasks to run\n";
        
        // Attempt to steal a task from the most loaded core
        Core& most_loaded_core = get_most_loaded_core();
        if (most_loaded_core.get_task_count() > 0) {
            int stolen_task_id = most_loaded_core.steal_task();
            cores[core_id].add_task(stolen_task_id);  // Add the stolen task to the current core
            
            // Output that a task was stolen
            //output += "core " + std::to_string(core_id) + " stole task " + std::to_string(stolen_task_id) + " from core " + std::to_string(&most_loaded_core - cores) + "\n";
        }
        return output;  // Return output indicating no tasks to run and any stolen task
    }

    // Execute task on the core
    int task_id = cores[core_id].run_task();
    
    // Output message when running a task on the core
    std::string output = "core " + std::to_string(core_id) + " is running task " + std::to_string(task_id) + "\n";

    // If the core has no more tasks, try to steal tasks from another core
    if (!cores[core_id].has_tasks()) {
        Core& most_loaded_core = get_most_loaded_core();
        if (most_loaded_core.get_task_count() > 0) {
            int stolen_task_id = most_loaded_core.steal_task();
            cores[core_id].add_task(stolen_task_id);  // Add the stolen task to the current core
            
            // Output message that a task was stolen
            //output += "core " + std::to_string(core_id) + " stole task " + std::to_string(stolen_task_id) + " from core " + std::to_string(&most_loaded_core - cores) + "\n";
        }
    }

    return output;  // Return output after executing the task and possibly stealing
}


std::string CPU::sleep(int core_id) {
    // Check if the core ID is valid
    if (core_id < 0 || core_id >= num_cores) {
        return "failure\n";
    }

    // Check if the core has any assigned tasks
    if (!cores[core_id].has_tasks()) {
        return "core " + std::to_string(core_id) + " has no tasks to assign\n";
    }

    // String to record task redistribution output
    std::string output = "";

    // Repeat while there are tasks remaining in the current core
    while (cores[core_id].has_tasks()) {
        // Get the last task from the current core (remove it from the queue)
        int task_id = cores[core_id].steal_task();

        // If task_id is invalid (e.g., when there are no tasks), stop this process
        if (task_id == -1) {
            break;
        }

        // Find the core with the least tasks
        int least_loaded_core_id = 0;
        int min_tasks = 999999;  // Use a large arbitrary number instead of INT_MAX

        for (int i = 0; i < num_cores; ++i) {
            if (i != core_id && cores[i].get_task_count() < min_tasks) {
                min_tasks = cores[i].get_task_count();
                least_loaded_core_id = i;
            }
        }

        // Add the task to the core with the least number of tasks
        cores[least_loaded_core_id].add_task(task_id);

        // Add task transfer information to the output message
        output += "task " + std::to_string(task_id) + " assigned to core " + std::to_string(least_loaded_core_id) + " ";
        
    }
    
    return output + "\n";
    
}

std::string CPU::shutdown() {
    for (int i = 0; i < num_cores; ++i) {
        while (cores[i].has_tasks()) {
            int task_id = cores[i].run_task();
            std::cout << "deleting task " << task_id << " from core " << i << " ";
            
        }
    }
    std::cout << std::endl;
    return "";
}
