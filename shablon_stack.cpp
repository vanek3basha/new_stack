#include <stdlib.h>
#include <stdio.h>

template <typename stk_T> struct shablon_stack_t
{
    stk_T* sh_stack_massive;
    size_t capacity_of_sh_stack;
    size_t size_of_sh_stack;
};

template <typename stk_T> shablon_stack_t<stk_T>* sh_stack_init(size_t capacity)
{
    shablon_stack_t<stk_T>* sh_stack = (shablon_stack_t<stk_T>*)calloc(1, sizeof(shablon_stack_t<stk_T>));
    if(sh_stack == NULL)
    {
        perror("SH_STACK == NULL\n");
        return NULL;
    }

    sh_stack->capacity_of_sh_stack = capacity;
    sh_stack->size_of_sh_stack = 0;

    sh_stack->sh_stack_massive = (stk_T*)calloc(capacity, sizeof(stk_T));
    if(sh_stack->sh_stack_massive == NULL)
    {
        perror("SH_STACK_MASSIVE ERROR\n");
        free(sh_stack);
        return NULL;
    }

    return sh_stack;
}

template <typename stk_T> size_t sh_stack_free(shablon_stack_t<stk_T>* sh_stack)
{
    free(sh_stack->sh_stack_massive);
    sh_stack->capacity_of_sh_stack = 0;
    sh_stack->size_of_sh_stack = 0;
    free(sh_stack);
    return 0;
}

template <typename stk_T> size_t sh_stack_push(stk_T value, shablon_stack_t<stk_T>* sh_stack)
{
    sh_stack->sh_stack_massive[sh_stack->size_of_sh_stack] = value;
    sh_stack->size_of_sh_stack += 1;
    return 0;
}

int main()
{
    shablon_stack_t<double>* sh_stack_test = sh_stack_init<double>(10); 
    sh_stack_push(20.0, sh_stack_test);
    printf("znachenie 1 -> %lf\n", sh_stack_test->sh_stack_massive[0]);
    sh_stack_free(sh_stack_test);
    return 0;
}