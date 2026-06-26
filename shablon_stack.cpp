#include "sh_stack.hpp"

int main()
{
    shablon_stack_t<const char*>* sh_stack_test = sh_stack_init<const char*>(1); 
    sh_stack_push("siski", sh_stack_test);
    sh_stack_push("siski_2", sh_stack_test);
    const char* element = sh_stack_pop(sh_stack_test);
    element = sh_stack_pop(sh_stack_test);
    printf("znachenie pop -> %s\n", element);
    printf("znachenie 1 -> %s\n", sh_stack_test->sh_stack_massive[0]);
    sh_stack_free(sh_stack_test);
    return 0;
}