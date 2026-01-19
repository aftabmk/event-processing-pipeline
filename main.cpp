#include "environment/lambda.hpp"        // Your lambda() handler
#include "aws/lambda-runtime/runtime.h"  // AWS Lambda C++ runtime

int main()
{
    // Run AWS Lambda runtime with your lambda() function
    aws::lambda_runtime::run_handler(lambda);
    return 0;
}
