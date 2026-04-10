#include "workflow.hpp"

void Workflow::execute(const json& record) const
{
    try {
        json data = process(record);
        // log json
        // LOG_JSON(data);
        postJson(data);
    }
    catch (const std::exception& e) {
        LOG_ERR(e.what());
    }
}
