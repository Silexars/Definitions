#include <Veritas/Definitions/Types/any_function.h>

using namespace Veritas;

any any_function::operator()(const any_args& args){ return any_f(args); }
