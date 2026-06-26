#include "sh_stack.hpp"

int main()
{
    shablon_stack_t<int>* sh_stack_test = sh_stack_init<int>(2); 
    sh_stack_push(1, sh_stack_test);
    sh_stack_push(2, sh_stack_test);
    int element = sh_stack_pop(sh_stack_test);
    element = sh_stack_pop(sh_stack_test);
    printf("znachenie pop -> %d\n", element);
    printf("znachenie left  -> %d\n", sh_stack_test->sh_stack_massive[0]);
    printf("znachenie right -> %d\n", sh_stack_test->sh_stack_massive[5]);
    sh_stack_free(sh_stack_test);
    return 0;
}