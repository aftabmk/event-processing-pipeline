#include <iostream>

#include "workflow.hpp"
#include "post/post.hpp"
#include "process/process.hpp"

void Workflow::execute(const json& record) const
{
    try {
        json data = process(record);
        postJson(data);
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing record: " << e.what() << "\n";
    }
}
