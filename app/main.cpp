#include "main.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [test name]" << std::endl;
        return -1;
    }

    std::string print = argv[1];
    std::unordered_map<std::string, int> test_map = {
        {"vector", 1}, {"array", 2}, {"set", 3}, {"map", 4},
        {"list", 5}, {"stack", 6}, {"queue", 7}, {"string", 8},
        {"memory", 9}, {"preprocessor", 10}, {"pointer", 11}, {"lamda", 12},
        {"lrvalue", 13}, {"pointer", 14}, {"inheritance", 15}, 
        {"thread", 16}, {"thread_sync", 17}
    };

    if (test_map.find(print) != test_map.end())
    {
        int index = test_map[print];
        switch (index)
        {
        case 1: vector_example(); break;
        case 2: array_example(); break;
        case 3: set_example(); break;
        case 4: map_example(); break;
        case 5: list_example(); break;
        case 6: stack_example(); break;
        case 7: queue_example(); break;
        case 8: string_example(); break;
        case 9: memory_example(); break;
        case 10: preprocessor_example(); break;
        case 11: pointer_example(); break;
        case 12: lamda_example(); break;
        case 13: lrvalue_example(); break;
        case 14: pointer_example(); break;
        case 15: inherance_example(); break;
        case 16: thread_example(); break;
        case 17: thread_sync_example(); break;
        default:
            std::cerr << "Invalid example name!" << std::endl;
            return -1;
        }
    }
    else
    {
        std::cerr << "Invalid example name!" << std::endl;
        return -1;
    }
}