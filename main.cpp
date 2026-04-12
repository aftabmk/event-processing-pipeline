// // local
// #include "namespace/env.hpp"
// #include "environment/local.hpp"
// // #include "environment/lambda.hpp"

// #include <iostream>
// #include <exception>

// int main()
// {
//     try
//     {
//         run_local();
//     }
//     catch (const std::exception& e)
//     {
//         std::cerr << "Standard Exception: " << e.what() << std::endl;
//     }
//     catch (...)
//     {
//         std::cerr << "Unknown Exception occurred!" << std::endl;
//     }

//     return 0;
// }

// aws lambda 
#include "environment/lambda.hpp"
#include <aws/lambda-runtime/runtime.h>

int main()
{
    aws::lambda_runtime::run_handler(lambda_handler);
    return 0;
}