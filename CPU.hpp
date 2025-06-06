#ifndef CPU_HPP
#define CPU_HPP

#include "Core.hpp"
#include <string>

class CPU {
private:
    Core *cores;
    int num_cores;
    bool is_initialized;

    Core& get_least_loaded_core();
    Core& get_most_loaded_core();

public:
    CPU();
    ~CPU();
    std::string on(int core_count);
    std::string spawn(int task_id);
    std::string run(int core_id);
    std::string sleep(int core_id);
    std::string shutdown();
};

#endif
