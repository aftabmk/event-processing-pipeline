#include "workflow.hpp"

#include <iostream>

#include "process/process.hpp"

void workflow(const json& record)
{
    try {
        process(record);
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing record: " << e.what() << "\n";
    }
}
