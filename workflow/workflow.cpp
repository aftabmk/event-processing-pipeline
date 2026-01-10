#include "workflow.hpp"

void Workflow::execute(const json& record) const
{
    try {
        json data = process(record);
        postJson(data);
    }
    catch (const std::exception& e) {
        LOG_ERR(e.what());
    }
}
