#include "CPU.hpp"
#include <iostream>

int main() {
    CPU cpu;
    std::string command;
    
    while (std::cin >> command) {
        if (command == "ON") {
            int cores;
            std::cin >> cores;
            std::cout << cpu.on(cores);
        } else if (command == "SPAWN") {
            int task_id;
            std::cin >> task_id;
            std::cout << cpu.spawn(task_id);
        } else if (command == "RUN") {
            int core_id;
            std::cin >> core_id;
            std::cout << cpu.run(core_id);
        } else if (command == "SLEEP") {
            int core_id;
            std::cin >> core_id;
            std::cout << cpu.sleep(core_id);
        } else if (command == "SHUTDOWN") {
            std::cout << cpu.shutdown();
        } else if (command == "EXIT") {
            break;
        }
    }
    
    return 0;
}
