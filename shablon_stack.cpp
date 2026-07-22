#include "sh_stack.hpp"

int main()
{
    shablon_stack_t<int>* sh_stack_test = SH_STACK_INIT(int, 10); 
    // sh_stack_test = NULL;
    uint32_t byte_flag = 4;
    SH_STACK_PUSH(1, sh_stack_test);
    // SH_STACK_DUMP(massive_of_errors, sh_stack_test, 1);
    SH_STACK_PUSH(2, sh_stack_test);
    // hash_counting(sh_stack_test);
    SH_STACK_DUMP(byte_flag, sh_stack_test);
    // SH_STACK_DUMP(byte_flag, sh_stack_test);
    // sh_stack_dump<int>(NULL, NULL, 0);

    // SH_STACK_CHECK(sh_stack_test);
    int element = SH_STACK_POP(sh_stack_test);
    printf("znachenie pop -> %d\n", element);
    element = SH_STACK_POP(sh_stack_test);
    printf("znachenie pop -> %d\n", element);
    if(sh_stack_test != NULL)
    {
    // printf("znachenie left  -> %s\n", sh_stack_test->sh_stack_massive[0]);
    // printf("znachenie right -> %s\n", sh_stack_test->sh_stack_massive[1]);
    }
    SH_STACK_FREE(sh_stack_test);
    return 0;
}

