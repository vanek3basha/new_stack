#include "sh_stack.hpp"

int main()
{
    shablon_stack_t<double>* sh_stack_test = sh_stack_init<double>(1); 
    sh_stack_push(1.0, sh_stack_test);
    sh_stack_push(2.0, sh_stack_test);
    // ShStackError massive_of_errors[10] = {SH_STACK_NULL_ERROR};
    // sh_stack_dump(massive_of_errors, sh_stack_test, 1);
    // sh_stack_dump<int>(NULL, NULL, 0);
    sh_stack_check(sh_stack_test);
    double element = sh_stack_pop(sh_stack_test);
    element = sh_stack_pop(sh_stack_test);
    printf("znachenie pop -> %lf\n", element);
    if(sh_stack_test != NULL)
    {
    printf("znachenie left  -> %lf\n", sh_stack_test->sh_stack_massive[0]);
    printf("znachenie right -> %lf\n", sh_stack_test->sh_stack_massive[1]);
    }
    sh_stack_free(sh_stack_test);
    return 0;
}