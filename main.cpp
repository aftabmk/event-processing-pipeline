#include "namespace/env.hpp"
#include "environment/local.hpp"
#include "environment/lambda.hpp"

int main()
{
    switch (ENV::ISLAMBDA != nullptr)
    {
        case true:
            run_lambda();
            break;

        case false:
            run_local();
            break;
    }

    return 0;
}


// #include <aws/lambda-runtime/runtime.h>

// #include "environment/lambda.hpp"

// int main()
// {
//     aws::lambda_runtime::run_handler(lambda_handler);
//     return 0;
// }